#include <locale>
#include <codecvt>
#include <string>

#include "string_util.h"

/*

std::string string_util::parse_http_accept_lang(const std::string& str){ // TODO realise

	
	// Accept-Language:ru,en-US;q=0.8,en;q=0.6

	std::string lang [] = 

    return "ru";
}

std::wstring string_util::utf8_to_wchar_t(std::string &str){
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring result = converter.from_bytes(str);	
	return result;
}





std::vector<std::string>
string_util::resplit(const std::string & s, std::string rgx_str = "\\s+") {
    std::vector<std::string> elems;
    std::regex rgx (rgx_str);
    std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
    std::sregex_token_iterator end;
    while (iter != end)  {
        elems.push_back(*iter);
        ++iter;
    }
    return elems;
}







*/

