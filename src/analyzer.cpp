



#include "analyzer.h"


//--------------------------------------------------  analyzer

freeling_analyzer::analyzer::analyzer( const std::string& lang){
	
	freeling::analyzer::config_options co;
	
	
	
	
	
	
	
	anlz = new freeling::analyzer(co);
}

freeling_analyzer::analyzer::~analyzer(){
	
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
			result = new analyzer(alang);
		}
		return result;
	}


void freeling_analyzer::analyzer_pool::store(analyzer* analyzer){
	std::lock_guard<std::mutex> locker(_mutex);
	
	pool.insert(pool.begin(), analyzer);
}

