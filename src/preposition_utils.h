#ifndef FLS_PREPOSITION_UTILS_H
#define FLS_PREPOSITION_UTILS_H

#include "analyzer.h"

namespace freeling_server{
	void init_preposition_util();
	sentence_type check_and_translate(sentence_type& sent);
}

#endif
