#include <locale>
#include <codecvt>
#include <string>

#include "string_util.h"



std::string string_util::parse_http_accept_lang(const std::string& str){ // TODO realise

    return "ru";
}

std::wstring string_util::utf8_to_wchar_t(std::string &str){
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring result = converter.from_bytes(str);	
	return result;
}














