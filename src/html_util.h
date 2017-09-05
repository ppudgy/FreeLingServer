#ifndef FLS_HTML_UTIL_H
#define FLS_HTML_UTIL_H

#include <string>

#include "config.h"


namespace html{
		std::string create_html(const std::string&lang, const freeling_analyzer::about_type& about);
};

#endif
