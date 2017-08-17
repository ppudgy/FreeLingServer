#ifndef FLS_ANALYZER_H
#define FLS_ANALYZER_H


#include <string>


namespace freeling_analyzer{




class analyzer{
	
public:	
		std::string analyze(const std::string& text);

};



class analyzer_pool{
friend struct analyzer_proxy;


	analyzer* get(const std::string& );
	void store(analyzer*);


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
    analyzer_factory(){}
    void initialize(analyzer_pool& a){

    }

    analyzer_pool instantiate(){
        return analyzer_pool();

    }
};




};



#endif
