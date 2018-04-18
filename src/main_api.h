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


typedef decltype(D(_name = std::string(),
                   _version_major = int(),
                   _version_minor = int(),
                   _uptime = long(),
                   _freeling = std::string()
                   )) about_type;


typedef decltype(D(_word = std::string(),
                   _lemma = std::string(),
                   _tag = std::string()))     word_type;

typedef std::vector<word_type> sentence_type;


sentence_type 	trunslate(const freeling_server::sentence_type& sent){
	sentence_type result;
	
	for(auto wit = sent.begin(); wit != sent.end(); wit++){
		word_type w;
		w.word = freeling::util::wstring2string(wit->word);
		w.lemma = freeling::util::wstring2string(wit->lemma);
		w.tag = freeling::util::wstring2string(wit->tag);
		result.push_back(w);
	}
	return result;
}


std::vector<sentence_type> 	trunslate( const std::vector<freeling_server::sentence_type>& sents){
	std::vector<sentence_type> result;
	
	for(auto wit = sents.begin(); wit != sents.end(); wit++){
		result.push_back(trunslate(*wit));
	}
	return result;
}


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
	
	std::cout << p.text << std::endl;
		auto res = proxy->analyze(p.text);

        std::string result = iod::json_encode(trunslate(res));
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

	std::cout << p.text << std::endl;

        // проанализировать строку
		auto res = proxy->analyze(p.text);

        std::string result = iod::json_encode(trunslate(res));
        resp->set_header("Content-Type", "application/json");
        return result;
    },
    GET = [] (mhd_request* req, mhd_response* resp) {
		about_type result;
		
		auto res = freeling_server::config::get_about();
		
		result.name = res.name;
		result.version_major = res.version_major;
		result.version_minor = res.version_minor;
		result.uptime = res.uptime;
		result.freeling = res.freeling;

        return iod::json_encode(result);	
    }
);

#endif
