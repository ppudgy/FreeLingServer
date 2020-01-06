/**
 * FreeLing http interface with crow
 
 */

 #include <crow.h>

#include "config.h"
#include "analyzer.h"
#include "utils.h"
 
//#include "preposition_utils.h"
//#include "union_utils.h"

 crow::json::wvalue translate(const std::vector<freeling_server::word_type>& from){
	 std::vector<crow::json::wvalue>res;
	 for(auto it = from.begin(); it != from.end(); it++){
		 crow::json::wvalue x;
		 x["word"] = freeling::util::wstring2string(it->word);
		 x["lemma"] = freeling::util::wstring2string(it->lemma);
		 x["tag"] = freeling::util::wstring2string(it->tag);
		 res.emplace_back(std::move(x));
	 }
	 crow::json::wvalue result;
	 
	 result = std::move(res);
	 return result;
 }
 
 crow::json::wvalue translate(std::vector<freeling_server::sentence_type>& from){
	 std::vector<crow::json::wvalue>res;
	 for(auto it = from.begin(); it != from.end(); it++){
		 res.push_back(translate(*it));
	 }
	 crow::json::wvalue result;
	 
	 result = std::move(res);
	 return result;

 }
  
int main()
{
	
	//freeling_server::init_preposition_util();
	//freeling_server::init_union_util();
	
	std::string freeling_path = "/usr/local/share/freeling";
	if(!freeling_server::config::initialize(freeling_path))
	{
		exit(2);
	}	
	
    crow::SimpleApp app;
 /**
 *  GET             /              - выдать информацию о программе (application/json, text/html, text/xml)
 *  GET, POST       /freeling      - провести морфологический разбор текста (application/json, text/html, text/xml)
 */


	std::shared_ptr<freeling_server::analyzer_pool> analyzer_pool = std::make_shared<freeling_server::analyzer_pool>();


	CROW_ROUTE(app, "/freeling")
        .methods("POST"_method)
    ([&analyzer_pool](const crow::request& req)
    {
        std::string ac_lang = "ru";
        auto it = req.headers.find("Accept-Language");
        if(it != req.headers.end())
			ac_lang = it->second;
        std::string lang = freeling_server::parse_http_accept_lang(ac_lang);
			
        CROW_LOG_INFO << "msg from client: " << req.body;
        auto x = crow::json::load(req.body);
        auto text = x["text"].s();



        freeling_server::analyzer_proxy proxy(analyzer_pool, lang);
        // проанализировать строку
		auto res = proxy->analyze(text);
        auto result = translate(res);
        return crow::response{result};
    });




	CROW_ROUTE(app, "/freeling")
        .methods("GET"_method)
    ([&analyzer_pool](const crow::request& req)
    {
        std::string ac_lang = "ru";
        auto it = req.headers.find("Accept-Language");
        if(it != req.headers.end())
			ac_lang = it->second;
        auto text = req.url_params.get("text");
        std::string lang = freeling_server::parse_http_accept_lang(ac_lang);
        freeling_server::analyzer_proxy proxy(analyzer_pool, lang);
        // проанализировать строку
		auto res = proxy->analyze(text);
        auto result = translate(res);
        return crow::response{result};
    });

	CROW_ROUTE(app, "/")
    ([]{
        CROW_LOG_INFO << "logs requested";
        auto about = freeling_server::config::get_about();
        crow::json::wvalue x;
        x["name"] = about.name;
        x["version_major"] = about.version_major;
        x["version_minor"] = about.version_minor;
        x["uptime"] = about.uptime;
        x["freeling"] = about.freeling;
        CROW_LOG_INFO << "logs completed";
        return x;
    });
    
    
    app.port(8585)
        .multithreaded()
        .run();    
}
