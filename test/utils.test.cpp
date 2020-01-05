


#define CATCH_CONFIG_MAIN
#include "catch.hpp"


#include "../src/utils.h"

TEST_CASE("Join empty list", "[utils]") {
	std::vector<freeling_server::word_type> empty;
	std::wstring delim = freeling::util::string2wstring(";");

	auto res = freeling_server::join(empty, delim);

	REQUIRE(res.size() == 0);
}


TEST_CASE("Join list with one element", "[utils]") {
	std::vector<freeling_server::word_type> empty;
	freeling_server::word_type one ("мама", "мама", "P");
	empty.push_back(one);
	std::wstring delim = freeling::util::string2wstring(";");
	auto res = freeling_server::join(empty, delim);

	REQUIRE(res.size() > 0);
	REQUIRE(res.find(';') == std::wstring::npos);

	REQUIRE(res.compare(freeling::util::string2wstring("мама")) == 0);

}

TEST_CASE("Join list with two element", "[utils]") {
	std::vector<freeling_server::word_type> empty;
	freeling_server::word_type one;
	empty.emplace_back("мама", "мама", "P");
	empty.emplace_back("мыла", "мыть", "P");

	std::wstring delim = freeling::util::string2wstring(";");
	auto res = freeling_server::join(empty, delim);

	REQUIRE(res.size() > 0);
	REQUIRE(res.find(';') > 0);

	REQUIRE(res.compare(freeling::util::string2wstring("мама;мыла")) == 0);

}


TEST_CASE("split empty string", "[utils]") {
	std::string empty = "";

	auto res = freeling_server::resplit(empty);

	REQUIRE(res.size() == 1);
	REQUIRE(res.at(0).size() == 0);
}

TEST_CASE("split  string", "[utils]") {
	std::string non_empty = "test   test   ";

	auto res = freeling_server::resplit(non_empty);

	REQUIRE(res.size() == 2);
	REQUIRE(res.at(0).compare("test") == 0);
	REQUIRE(res.at(1).compare("test") == 0);
}


TEST_CASE("split  string by ;", "[utils]") {
	std::string non_empty = " test ;  test   ";

	auto res = freeling_server::resplit(non_empty, ";");

	REQUIRE(res.size() == 2);
	//REQUIRE(res.at(0).compare("test") == 0);
	//REQUIRE(res.at(1).compare("test") == 0);
}


TEST_CASE("parse lang", "[utils]") {
	std::string accept_string = "ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3 ";

	auto res = freeling_server::parse_http_accept_lang(accept_string);

	REQUIRE(res.size() > 0);
	REQUIRE(res.compare("ru") == 0);
	//REQUIRE(res.at(1).compare("test") == 0);
}



