
#include "analyzer.h"
//#include "preposition_utils.h"
//#include "union_utils.h"
#include "sequence_processor.h"

//-------------------------------------------------------  analyzer ----

freeling_server::analyzer::analyzer( const std::string& lang, std::shared_ptr<config> cfg ):_lang(lang), _cfg(cfg){
		_anlz =  std::make_unique<freeling::analyzer>(_cfg->get_config_option());
		_anlz->set_current_invoke_options(_cfg->get_invoke_option());
}

freeling_server::analyzer::~analyzer(){
}

// TODO неправильно определяется лемма для слова "телевизор" - совпадает со словом.
std::vector<freeling_server::sentence_type>  freeling_server::analyzer::analyze(const std::string& text){
    std::vector<freeling_server::sentence_type> result;
    std::list<freeling::sentence> sentenses;
    std::wstring lt = freeling::util::string2wstring(text);
    _anlz->analyze(lt, sentenses, true);
	std::vector<word_type> res;
	for(auto sit = sentenses.begin(); sit != sentenses.end(); sit++){
		std::vector<word_type> sent;
        for(auto wit = sit->begin(); wit != sit->end(); wit++){
			//word_type w;
            //w.word = wit->get_form();
            //w.lemma = wit->get_lemma();
            //w.tag = wit->get_tag();
            //sent.push_back(w);
            sent.emplace_back(wit->get_form(), wit->get_lemma(), wit->get_tag());
        }
        if(_lang.compare("ru") == 0){
        	ru_processor* processor = ru_processor::instance();
        	res = processor->process(sent);
        } else {
        	res.insert(res.end(), sent.begin(), sent.end());
        }
		//auto sent_tr = check_and_translate(sent);
		//auto res = check_and_translate_union(sent_tr);
        result.push_back(res);
    }
	return result;
}
//--------------------------------------------------  analyzer_pool ----
std::unique_ptr<freeling_server::analyzer> freeling_server::analyzer_pool::get(const std::string& alang){
	std::lock_guard<std::mutex> locker(_mutex);
	for(auto it = pool.begin(); it != pool.end(); it++){
		if( (*it)->is_lang(alang)){
			auto result = std::move(*it);
			it = pool.erase(it);
			return std::move(result);
		}
	}
	return std::move(create_new_analyzer(alang));
}

void freeling_server::analyzer_pool::store(std::unique_ptr<analyzer> analyzer){
	std::lock_guard<std::mutex> locker(_mutex);

	pool.insert(pool.begin(), std::move(analyzer));
}

std::unique_ptr<freeling_server::analyzer> freeling_server::analyzer_pool::create_new_analyzer(const std::string& alang){
	std::shared_ptr<config> cfg = config::create_config(alang);
	return std::make_unique<analyzer>(alang, cfg);
}
