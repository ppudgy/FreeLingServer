#ifndef FLS_ANALYZER_H
#define FLS_ANALYZER_H

#include <string>
#include <list>
#include <mutex>
#include <memory>

#include <freeling/morfo/analyzer.h>

#include "config.h"


namespace freeling_analyzer{




class analyzer{
	

	freeling::analyzer *_anlz;
	config* _cfg;
	std::string _lang;
public:
	analyzer( const std::string& lang, config* cfg);
	~analyzer();
	
	
	
	
	std::string analyze(const std::string& text);
	
	bool is_lang(const std::string& lang){
		return 0 == _lang.compare(lang);
	}
};



class analyzer_pool{
	friend struct analyzer_proxy;

	analyzer* get(const std::string& alang);
	void store(analyzer*);
private:
	analyzer* create_new_analyzer(const std::string& alang);

	std::list<analyzer*> pool;
	std::mutex _mutex;
	
	std::string freeling_path;
	
};



struct analyzer_proxy{
	
	analyzer_proxy(analyzer_pool& pool, const std::string &lang):_pool(pool), _lang(lang){
		_analyzer = _pool.get(_lang);
	}

	~analyzer_proxy(){
		_pool.store(_analyzer);
	}

	analyzer* operator->(){
		return _analyzer;
	}	


private:
	analyzer* _analyzer;
	analyzer_pool& _pool;
	std::string _lang;
};



struct analyzer_factory{
    analyzer_factory(){
	}
//    void initialize(analyzer_pool& a){
//
//    }

    analyzer_pool& instantiate(){
        return *_pool;
    }
    std::shared_ptr<analyzer_pool> _pool;
};




};



#endif
