#ifndef FLS_UTILS_H
#define FLS_UTILS_H

#include "analyzer.h"

namespace freeling_server{
	
	std::wstring 				join(const std::vector<priv_word_type> & vec, std::wstring delim);
	std::vector<std::string> 	resplit(const std::string &s, std::string rgx_str = "\\s+");
	std::string 				parse_http_accept_lang(const std::string& str);
}
#endif
