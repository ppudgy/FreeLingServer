//#define IOD_PCL_WITH_EXCEPTIONS

/**
 * FreeLing http interface
 *
 *
 *
 *
 *
 * 
 */

#include <unistd.h>

#include <string>
#include <assert.h>
#include <iostream>


#include <iod/parse_command_line.hh>
#include <silicon/backends/mhd.hh>


iod_define_symbol(port);
iod_define_symbol(nodaemon);
iod_define_symbol(help);

iod_define_symbol(text);
iod_define_symbol(freeling);


using namespace s;
using namespace sl;
using namespace iod;



/**
 *  GET             /              - выдать информацию о программе (application/json, text/html, text/xml)
 *  GET, POST       /freeling      - провести морфологический разбор текста (application/json, text/html, text/xml)
 *  GET, POST       /cfg           - получить конфигурацию (application/json, text/html, text/xml)
 *
 *
 */

auto hello_api = http_api(
    POST / _freeling * get_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp,  auto p) {
    }
    GET / _freeling * get_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp,  auto p) {
        const char* ac_lang = req->get_header("Accept-Language");
        const char* ac_acc = req->get_header("Accept");
        std::string result = "freeling " + p.text;
        return result;
    },
        const char* ac_lang = req->get_header("Accept-Language");
        const char* ac_acc = req->get_header("Accept");
        std::string result = "freeling " + p.text;
        return result;
    },
        const char* ac_lang = req->get_header("Accept-Language");
        const char* ac_acc = req->get_header("Accept");
        std::string result = "freeling " + p.text;
        return result;
    },
        const char* ac_lang = req->get_header("Accept-Language");
        const char* ac_acc = req->get_header("Accept");
        std::string result = "freeling " + p.text;
        return result;
    },

    GET = [] ()
    {
        return "about";
    }

);

int main(const int argc, const char* argv[])
{
    auto opts = parse_command_line(argc, argv, _port = int(8585), _nodaemon = bool(false));

    if(!opts.nodaemon){
        if(0 != daemon(0, 0)){
            perror(argv[0]);
            exit(1);
        }
    }



    int port = opts.port;
    auto ctx = sl::mhd_json_serve(hello_api, port);

    return 0;
}
