#ifndef FLS_STRING_UTIL_H
#define FLS_STRING_UTIL_H


#include <string>



namespace string_util{
    std::string parse_http_accept_lang(const std::string& str);
    std::wstring utf8_to_wchar_t(std::string &str);
}

#endif
