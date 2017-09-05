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
#include <iod/json.hh>
#include <silicon/backends/mhd.hh>


#include "analyzer.h"
#include "symbols.hh"
#include "string_util.h"


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
    POST / _freeling * post_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp, freeling_analyzer::analyzer_pool& pool, auto p) {
        // получить строку для анализа
        std::string ac_lang = req->get_header("Accept-Language");
        std::string lang = string_util::parse_http_accept_lang(ac_lang);

        freeling_analyzer::analyzer_proxy proxy(pool, lang);
        // проанализировать строку
		auto at = proxy->analyze(p.text);
        std::string result = iod::json_encode(at);

        // TODO add result encoding
        resp->set_header("Content-Type", "application/json");
        return result;
    },
    GET / _freeling * get_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp, freeling_analyzer::analyzer_pool& pool, auto p) {
        std::string ac_lang = req->get_header("Accept-Language");
        std::string lang = string_util::parse_http_accept_lang(ac_lang);

        freeling_analyzer::analyzer_proxy proxy(pool, lang);
        // проанализировать строку
		auto at = proxy->analyze(p.text);
        std::string result = iod::json_encode(at);
        resp->set_header("Content-Type", "application/json");
        return result;
    },
    GET /   _cfg = [](){  
        // если HTML - вернуть форму с конфигурацией и возможностью ее редактироать
        // если json, xml - вернуть данные
    },
    POST / _cfg = [](mhd_request* req, mhd_response* resp){  // TODO delete
        // если json, xml - установить конфигурацию и вернуть новую конфигурацию
        // если параметры формы - установить конфигурацию и вернуть форму с кофигурацией и возможностью ее редактировать
    },
    GET = [] (mhd_request* req, mhd_response* resp) {
        // получить информацию о программе
        //  name:string
        //  major:string
        //  minor:string
        //  uptime: int; // in second
        //
        // создать структуру ответа
		std::string result = "about";
        const char* ac_acc = req->get_header("Accept");
        std::string acc_str (ac_acc);
        if(acc_str.find("/json") != std::string::npos){
			
		}else if (acc_str.find("/html") != std::string::npos){
			std::string ac_lang = req->get_header("Accept-Language");
			std::string lang = string_util::parse_http_accept_lang(ac_lang);
			result = freeling_analyzer::config::get_root_html(lang);
		}else
			throw sl::error::bad_request(" content type is not suported");
        return result;
    }

);

int main(const int argc, const char* argv[])
{
	freeling::util::init_locale(L"ru_RU.UTF-8");



    auto opts = parse_command_line(argc, argv, _port = int(8585), _nodaemon = bool(false), _freeling = std::string("/usr/local/share/freeling"));

    if(!opts.nodaemon){
        if(0 != daemon(0, 0)){
            perror(argv[0]);
            exit(1);
        }
    }
	
	std::string freeling_path = opts.freeling;
	
	if(!freeling_analyzer::config::set_freeling_path(freeling_path))
	{
		std::cerr << "do not find freeling data path" << std::endl;
		exit(2);
	}


    int port = opts.port;
    auto ctx = sl::mhd_json_serve(hello_api, middleware_factories(freeling_analyzer::analyzer_factory()),port);

    return 0;
}
