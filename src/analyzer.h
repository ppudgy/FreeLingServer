#ifndef FLS_ANALYZER_H
#define FLS_ANALYZER_H

#include <string>
#include <list>
#include <mutex>
#include <memory>
#include <freeling/morfo/analyzer.h>

#include "config.h"

namespace freeling_server{

struct word_type{
	std::wstring word;
	std::wstring lemma;
	std::wstring tag;
};

typedef std::vector<word_type> sentence_type;
//---------------------------------------------------------- analyzer --
class analyzer{
public:
	analyzer( const std::string& lang, std::shared_ptr<config> cfg);
	~analyzer();

	std::vector<sentence_type> 	analyze(const std::string& text);
	bool 						is_lang(const std::string& lang){ return 0 == _lang.compare(lang); }
private:	
	std::unique_ptr<freeling::analyzer>			_anlz;
	std::shared_ptr<config>						_cfg;
	std::string 								_lang;
};

//----------------------------------------------------- analyzer pool --
class analyzer_pool{
	friend struct analyzer_proxy;
public:
	analyzer_pool(){}
private:
	std::unique_ptr<analyzer> get(const std::string& alang);
	void 					  store(std::unique_ptr<analyzer>);

	analyzer_pool(const analyzer_pool&) = delete;
	analyzer_pool(const analyzer_pool&&) = delete;
	const analyzer_pool& operator= (const analyzer_pool&) = delete;

	std::unique_ptr<analyzer>	create_new_analyzer(const std::string& alang);
	
	std::mutex 				_mutex;
	std::list<std::unique_ptr<analyzer>> 	pool;
};

//---------------------------------------------------- analyzer proxy --
struct analyzer_proxy{

	analyzer_proxy(std::weak_ptr<analyzer_pool> pool, const std::string &lang)
			:_pool(pool), _lang(lang)
	{
		_analyzer = _pool.lock()->get(_lang);
	}
	~analyzer_proxy(){
		_pool.lock()->store(std::move(_analyzer)); 
	}
	
	std::unique_ptr<analyzer>&  operator->(){ return _analyzer;	}
private:
	std::unique_ptr<analyzer>    _analyzer;
	std::weak_ptr<analyzer_pool> _pool;
	std::string 			     _lang;
};

};
#endif
