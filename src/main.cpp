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
        //
        // 
		std::string at = proxy->analyze(p.text);

        std::string result = "freeling POST : " + at;
        return result;
    },
    GET / _freeling * get_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp, freeling_analyzer::analyzer_pool& pool, auto p) {
        std::string ac_lang = req->get_header("Accept-Language");
        std::string lang = string_util::parse_http_accept_lang(ac_lang);
        
        freeling_analyzer::analyzer_proxy proxy(pool, lang);
        // проанализировать строку
        //
        // 

		std::string at = proxy->analyze( p.text );
        
        std::string result = "freeling GET: " + at;
        return result;
    },
    GET /   _cfg = [](){
        // если HTML - вернуть форму с конфигурацией и возможностью ее редактироать
        // если json, xml - вернуть данные
    },
    POST / _cfg = [](mhd_request* req, mhd_response* resp){
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
        
        // если запрашиваемый формат HTML, сформировать и вернуть
        // если запрашиваемый формат XML, сформировать и вернуть
        // 

        const char* ac_acc = req->get_header("Accept");

//        if(sting_utils::contain(ac_acc, "text/html")){

//        }else if(sting_utils::contain(ac_acc, "text/xml")){

//        }else if(sting_utils::contain(ac_acc, "application/json")){
            
//        }

        return "about";
    }

);

int main(const int argc, const char* argv[])
{
	freeling::util::init_locale(L"ru_RU.UTF-8");
	
	
	
    auto opts = parse_command_line(argc, argv, _port = int(8585), _nodaemon = bool(false));

    if(!opts.nodaemon){
        if(0 != daemon(0, 0)){
            perror(argv[0]);
            exit(1);
        }
    }



    int port = opts.port;
    auto ctx = sl::mhd_json_serve(hello_api, middleware_factories(freeling_analyzer::analyzer_factory()),port);

    return 0;
}
