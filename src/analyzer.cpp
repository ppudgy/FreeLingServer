#include <silicon/error.hh>

#include "analyzer.h"
#include "preposition_utils.h"
#include "union_utils.h"

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
    
//	if(!_cfg) throw sl::error::bad_request( _lang + " is not suported language");

    std::list<freeling::sentence> sentenses;
    std::wstring lt = freeling::util::string2wstring(text);
    _anlz->analyze(lt, sentenses, true);
	std::vector<word_type> res;
	for(auto sit = sentenses.begin(); sit != sentenses.end(); sit++){
		std::vector<word_type> sent;
        for(auto wit = sit->begin(); wit != sit->end(); wit++){
			word_type w;
            w.word = wit->get_form();
            w.lemma = wit->get_lemma();
            w.tag = wit->get_tag();
            sent.push_back(w);
        }
        //auto sentence = trunslate(sent);
		auto sent_tr = check_and_translate(sent);
		auto res = check_and_translate_union(sent_tr);
        result.push_back(res);
    }
	return result;
}
/*
freeling_server::sentence_type 	freeling_server::analyzer::trunslate(freeling_server::priv_sentence_type sent){
	sentence_type result;
	
	for(auto wit = res.begin(); wit != res.end(); wit++){
		word_type w;
		w.word = freeling::util::wstring2string(wit->word);
		w.lemma = freeling::util::wstring2string(wit->lemma);
		w.tag = freeling::util::wstring2string(wit->tag);
		result.push_back(w);
	}
	return result;
}
*/
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
