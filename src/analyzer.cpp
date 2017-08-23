



#include "analyzer.h"


//--------------------------------------------------  analyzer




freeling_analyzer::analyzer::analyzer( const std::string& lang, config* cfg):_lang(lang), _cfg(cfg){
	_anlz = new freeling::analyzer(_cfg->get_config_option());
	
	_anlz->set_current_invoke_options(_cfg->get_invoke_option());
	
	
}

freeling_analyzer::analyzer::~analyzer(){
		
		delete _anlz;
		delete _cfg;
}


std::string freeling_analyzer::analyzer::analyze(const std::string& text){
	
	
	
	
	
	return text + " is analyzed.";
}

//--------------------------------------------------  analyzer_pool

//freeling_analyzer::analyzer_pool _pool;

//freeling_analyzer::analyzer_pool& get_static_pool(){
	//	return _pool;
//}

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
