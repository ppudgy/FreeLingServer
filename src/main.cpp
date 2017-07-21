#define IOD_PCL_WITH_EXCEPTIONS

/**
 * FreeLing http interface
 *
 *
 *
 *
 *
 * 
 */
#include <string>
#include <assert.h>
#include <iostream>


#include <iod/parse_command_line.hh>
#include <silicon/backends/mhd.hh>


iod_define_symbol(port);
iod_define_symbol(help);

iod_define_symbol(text);
iod_define_symbol(freeling);


using namespace s;
using namespace sl;
using namespace iod;

std::string usage(const int argc, const char* argv[]){
    std::string name = argv[0];
    std::string result =  name + " [--port=<number>] [--help]\n --help\t\t- print help string\n--port=<munder>\t- listen port\n ";
    return result;
}

auto hello_api = http_api(
    GET / _freeling * get_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp,  auto p) {

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
    auto opts = parse_command_line(argc, argv, _port = int(8585), _help = bool(false) );
    if(opts.help){
        std::string s = usage(argc, argv);
        std::cout << s;
        return 0;
    }
    int port = opts.port;
    auto ctx = sl::mhd_json_serve(hello_api, port);

    return 0;
}
