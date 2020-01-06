#ifndef FLS_SEQUENCE_PROCESSOR_H
#define FLS_SEQUENCE_PROCESSOR_H

#include <memory>

#include "analyzer.h"

namespace freeling_server{

	class sequence_processor {
	public:
		virtual sentence_type process(const sentence_type& sent) const = 0;
	};

	std::unique_ptr<sequence_processor> build_union_processor();
	std::unique_ptr<sequence_processor> build_preposition_processor();
	//const sequence_processor *build_preposition_processor();  // TODO на каждый падеж



	class ru_processor : public sequence_processor {
		std::unique_ptr<sequence_processor> union_processor;
		std::unique_ptr<sequence_processor> preposition_processor;
		static ru_processor* inst;
		ru_processor():union_processor(build_union_processor()), preposition_processor(build_preposition_processor()){};
	public:
		static ru_processor* instance();
		virtual sentence_type process(const sentence_type& sent) const;
	};



}

#endif