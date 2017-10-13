#ifndef FLS_MAIN_API_H
#define FLS_MAIN_API_H

#include <unistd.h>

#include <string>
#include <assert.h>
#include <iostream>

#include <iod/json.hh>
#include <silicon/backends/mhd.hh>

#include "main_symbols.hh"

#include "analyzer.h"
#include "utils.h"

#include "preposition_utils.h"

using namespace s;
using namespace sl;
using namespace iod;
/**
 *  GET             /              - выдать информацию о программе (application/json, text/html, text/xml)
 *  GET, POST       /freeling      - провести морфологический разбор текста (application/json, text/html, text/xml)
 */
auto hello_api = http_api(
    POST / _freeling * post_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp, freeling_server::analyzer_pool& pool, auto p) {
        // получить строку для анализа
        const char* char_lang = req->get_header("Accept-Language");
        if(char_lang == nullptr)
			char_lang = "ru";
        std::string ac_lang = char_lang;
        std::string lang = freeling_server::parse_http_accept_lang(ac_lang);
        freeling_server::analyzer_proxy proxy(pool, lang);
        // проанализировать строку
		auto res = proxy->analyze(p.text);

        std::string result = iod::json_encode(res);
        resp->set_header("Content-Type", "application/json");
        return result;
    },
    GET / _freeling * get_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp, freeling_server::analyzer_pool& pool, auto p) {
        const char* char_lang = req->get_header("Accept-Language");
        if(char_lang == nullptr)
			char_lang = "ru";
        std::string ac_lang = char_lang;
        std::string lang = freeling_server::parse_http_accept_lang(ac_lang);
        freeling_server::analyzer_proxy proxy(pool, lang);
        // проанализировать строку
		auto res = proxy->analyze(p.text);

        std::string result = iod::json_encode(res);
        resp->set_header("Content-Type", "application/json");
        return result;
    },
    GET = [] (mhd_request* req, mhd_response* resp) {
        return iod::json_encode(freeling_server::config::get_about());	
    }
);

#endif
