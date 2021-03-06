#include <silicon/clients/libcurl_client.hh>
#include <silicon/api.hh>
#include <silicon/api_description.hh>


#include <main_api.h>





#define CATCH_CONFIG_MAIN
#include <catch.hpp>

// TODO   add to silicon Content-type specifire in http client
// DODO   add to silicon inline HTML template processing


TEST_CASE("first test", "[simple-test]"){
	
	auto client = libcurl_json_client(hello_api, "127.0.0.1", 8585);
	std::cout << api_description(hello_api) << std::endl;
	auto rest = client.http_get();
		
	
	REQUIRE(rest.response.version_major == 0);
	REQUIRE(rest.response.version_minor == 1);
	
	auto name = rest.response.name;
	
	REQUIRE(name == std::string("freelingserver"));
	
	std::cout << iod::json_encode(rest) << std::endl;
	
	
	
//	auto rest = client.http_get.freeling(_text = "Мама мыла раму.");

//	std::cout << iod::json_encode(rest) << std::endl;


	//auto resp = client.http_get();
	//std::cout << "-->"<< resp.status << " | " << resp.error << std::endl;
	//REQUIRE(resp.status == 200);
	//std::cout << "-->"<< resp.response << std::endl;
	//auto respf = client.http_get.freeling(_text = "Мама мыла раму");
	//REQUIRE(respf.status == 200);
	//std::cout << respf.response << std::endl;
	//auto resp_p = client.http_post.freeling(_text = "Мама мыла раму");
	//int a = 0;
}
























