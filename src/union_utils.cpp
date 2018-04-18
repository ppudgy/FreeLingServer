#include <string>
#include <map>
#include <sstream>
#include <regex>

#include <iostream>

#include "utils.h"
#include "union_utils.h"
#include "analyzer.h"

std::vector<std::string> rUnion = {
        "так как", "как будто", "так что", "для того чтобы", "тогда как", "то есть", "потому что", "оттого что",
        "не только", "так и", "но и", "не только", "столько и", "то ли", "не то", "однако же", "все же", "не столько",
        "не то чтобы", "да и", "а именно", "до такой степени", "до того", "как будто", "потому что", "если бы",
        "несмотря на то", "с тем чтобы", "так что"
    };

class Map : public std::map<std::wstring, Map* >{};
Map union_search_tree;

void union_build_search_tree(const std::vector<std::string> &qwe){
	for(auto it = qwe.begin(); it != qwe.end(); it++){
		std::string temp = *it;
		auto words = freeling_server::resplit(temp);
		Map* _search_tree = & union_search_tree;
		if(words.size() == 1) continue;
		for(auto ot = words.begin(); ot != words.end(); ot++){
			std::wstring key = freeling::util::string2wstring(*ot);
			if(_search_tree->count(key) != 0){
				auto l_search_tree = _search_tree->find(key);
				_search_tree = (l_search_tree != _search_tree->end() ? l_search_tree->second :  new Map());
			}else{
				Map* l_search_tree = new Map();
				_search_tree->emplace(key, l_search_tree); 
				_search_tree = l_search_tree;
			}
		}
	}
}

void union_build_search_tree(){
	union_build_search_tree(rUnion);
}

freeling_server::sentence_type find_union(const freeling_server::sentence_type &words, const Map* s_tree){
	freeling_server::sentence_type result;
		
	if(words.size() != 0){
		auto w = words[0];
		freeling_server::sentence_type tail(words.begin() + 1, words.end());
		auto m = s_tree->find(freeling::util::lowercase(w.word));
		if(m != s_tree->end()){
			auto res = find_union(tail, m->second);
			result.insert(result.end(), w);
			if(res.size() > 0){
				for(auto it = res.begin(); it != res.end(); it++)
					result.insert(result.end(),*it);
			}
		}
	}
	return result;
}

const std::wstring DELIM = L" ";
freeling_server::sentence_type replace_complex_union(const freeling_server::sentence_type& words){
	freeling_server::sentence_type result;

	auto words_begin = words.begin();
	auto words_end = words.end();
	for(auto it = words_begin; it != words_end; it++){
		freeling_server::sentence_type tail(it, words_end);
		auto new_word = tail[0];
		auto f = find_union(tail, &union_search_tree);
		if(f.size() > 1){
			std::wstring w = join(f, DELIM);
			new_word.word = w;
			new_word.lemma = w;
			new_word.tag = L"C0";
			it += f.size()-1;
		}
		result.push_back(new_word);	
	}
	return result;
}

freeling_server::sentence_type freeling_server::check_and_translate_union(freeling_server::sentence_type& sent){
		return replace_complex_union(sent);
}

void freeling_server::init_union_util(){
	union_build_search_tree();
}

