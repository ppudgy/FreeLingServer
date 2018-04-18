#include <string>
#include <map>
#include <sstream>
#include <regex>

#include <iostream>

#include "utils.h"

std::wstring freeling_server::join(const std::vector<word_type> & vec, std::wstring delim){
    std::wstringstream ss;
    auto e = vec.begin();
    ss << e->word;
    e++;
    for (; e != vec.end(); ++e) {
        ss << delim << e->word;
    }
    return ss.str();
}

std::vector<std::string> freeling_server::resplit(const std::string &s, std::string rgx_str) {
        std::vector<std::string> elems;
        std::regex rgx(rgx_str);
        std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
        std::sregex_token_iterator end;
        while (iter != end) {
            elems.push_back(*iter);
            ++iter;
        }
        return elems;
}

std::string freeling_server::parse_http_accept_lang(const std::string& str){
	std::vector<std::string> lngs = resplit(str, ","); 
	lngs = resplit(lngs[0], ";"); 
	lngs = resplit(lngs[0], "-"); 
    return lngs[0];
}

