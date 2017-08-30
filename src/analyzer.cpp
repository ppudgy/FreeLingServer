



#include "analyzer.h"


//--------------------------------------------------  analyzer




freeling_analyzer::analyzer::analyzer( const std::string& lang, config* cfg):_lang(lang), _cfg(cfg){

	if(_cfg){
		_anlz = new freeling::analyzer(_cfg->get_config_option());
		_anlz->set_current_invoke_options(_cfg->get_invoke_option());
	}


}

freeling_analyzer::analyzer::~analyzer(){
	if(_cfg){
		delete _anlz;
		delete _cfg;
	}
}






std::vector<freeling_analyzer::sentence_type>  freeling_analyzer::analyzer::analyze(const std::string& text){
    std::vector<freeling_analyzer::sentence_type> result;

	if(_cfg){
        std::list<freeling::sentence> sentenses;

        std::wstring lt = freeling::util::string2wstring(text);
        _anlz->analyze(lt, sentenses, true);
//        std::wcout << L"--------------------------------------------------------------------------"<<std::endl;
        for(auto sit = sentenses.begin(); sit != sentenses.end(); sit++){
            sentence_type sentence;
//            std::wcout << L"{" << std::endl;
            for(auto wit = sit->begin(); wit != sit->end(); wit++){
                word_type w;
                w.word = freeling::util::wstring2string(wit->get_form());
                w.lemma = freeling::util::wstring2string(wit->get_lemma());
                w.tag = freeling::util::wstring2string(wit->get_tag());

                sentence.push_back(w);

//                std::wstring word = wit->get_form();
//                std::wstring lemma = wit->get_lemma();
//                std::wstring tag = wit->get_tag();
//
//                std::wcout  << L"\t(" << word << L" : "<< lemma << L" : " << tag << L"";
//
//                for(auto lit = wit->begin(); lit!= wit->end(); lit++){
//                        std::wstring lemma = lit->get_lemma();
//                        std::wstring tag = lit->get_tag();
//
//                        std::wcout << L"[" << lemma << L" : " << tag << L"]";
//                }
//                std::wcout << L")" <<std::endl;
            }
            result.push_back(sentence);
//            std::wcout << L"}" << std::endl;
        }
	}
	return result;
}


//--------------------------------------------------  analyzer_pool

freeling_analyzer::analyzer* freeling_analyzer::analyzer_pool::get(const std::string& alang){

		std::lock_guard<std::mutex> locker(_mutex);
		analyzer* result = nullptr;

		for(auto it = pool.begin(); it != pool.end(); it++){
			result = *it;
			if(result != nullptr && result->is_lang(alang)){
				it = pool.erase(it);
				break;
			}
		}
		if(result == nullptr){
			result = create_new_analyzer(alang);
		}
		return result;
	}


void freeling_analyzer::analyzer_pool::store(analyzer* analyzer){
	std::lock_guard<std::mutex> locker(_mutex);

	pool.insert(pool.begin(), analyzer);
}

freeling_analyzer::analyzer* freeling_analyzer::analyzer_pool::create_new_analyzer(const std::string& alang){
	// создать/получить конфигурацию
	config* cfg = config::create_config(alang);

	return new analyzer(alang, cfg);
}
