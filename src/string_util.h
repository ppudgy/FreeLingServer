#ifndef FLS_STRING_UTIL_H
#define FLS_STRING_UTIL_H




#include <string>
#include <regex>

#include <locale>
#include <codecvt>




namespace string_util{

inline std::vector<std::string> resplit(const std::string & s, std::string rgx_str = "\\s+") {
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



inline std::string parse_http_accept_lang(const std::string& str){ // TODO realise
	// Accept-Language:ru,en-US;q=0.8,en;q=0.6
	std::vector<std::string> lngs = resplit(str, ","); 
	lngs = resplit(lngs[0], ";"); 
	lngs = resplit(lngs[0], "-"); 
    return lngs[0];
}

    
    
inline std::wstring utf8_to_wchar_t(std::string &str){
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring result = converter.from_bytes(str);	
	return result;
}

    





}

#endif
