#include "sequence_processor.h"
#include "utils.h"



class Map : public std::map<std::wstring, Map* >{};

class sequence_processor_impl: public freeling_server::sequence_processor {
	public:
		sequence_processor_impl(const std::vector<std::string> &templates, const std::string atag);
		freeling_server::sentence_type process(const freeling_server::sentence_type& sent) const ;

	private:
		freeling_server::sentence_type find_union(const freeling_server::sentence_type &words, const Map* s_tree) const;
		void build_search_tree(const std::vector<std::string> &qwe);
		Map search_tree;
		std::wstring tag;
};

void sequence_processor_impl::build_search_tree(const std::vector<std::string> &qwe){
	//for(auto it = qwe.begin(); it != qwe.end(); it++){
	for(auto s : qwe){
		//std::string temp = *it;
		auto words = freeling_server::resplit(s);
		if(words.size() == 1) continue;
		Map* _search_tree = & search_tree;
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


sequence_processor_impl::sequence_processor_impl(const std::vector<std::string> &templates, const std::string atag): search_tree(), tag(freeling::util::string2wstring(atag)) {
	build_search_tree(templates);
}


freeling_server::sentence_type sequence_processor_impl::find_union(const freeling_server::sentence_type &words, const Map* s_tree) const {
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
freeling_server::sentence_type sequence_processor_impl::process(const freeling_server::sentence_type& sent) const {
	freeling_server::sentence_type result;

	auto words_begin = sent.begin();
	auto words_end = sent.end();
	for(auto it = words_begin; it != words_end; it++){
		freeling_server::sentence_type tail(it, words_end);
		auto new_word = tail[0];
		auto f = find_union(tail, &search_tree);
		if(f.size() > 1){
			std::wstring w = join(f, DELIM);
			new_word.word = w;
			new_word.lemma = w;
			new_word.tag = tag;
			it += f.size()-1;
		}
		result.push_back(new_word);	
	}
	return result;
}

// союзы
const std::vector<std::string> rUnion = {
        "так как", "как будто", "так что", "для того чтобы", "тогда как", "то есть", "потому что", "оттого что",
        "не только", "так и", "но и", "не только", "столько и", "то ли", "не то", "однако же", "все же", "не столько",
        "не то чтобы", "да и", "а именно", "до такой степени", "до того", "как будто", "потому что", "если бы",
        "несмотря на то", "с тем чтобы", "так что"
    };

std::unique_ptr<freeling_server::sequence_processor> freeling_server::build_union_processor() {
	return std::make_unique<sequence_processor_impl>(rUnion, "C0");
}

// предлоги родительского падежа
std::vector<std::string> rPreposition = {
	"без", "без ведома", "безо", "близ", "близко от", "в виде", "в зависимости от", "в качестве", "в лице",
	"в отличие от", "в отношении", "в пандан", "в преддверии", "в продолжение", "в результате", "в роли",
	"в силу", "в течение", "в целях", "вблизи", "ввиду", "вглубь", "вдоль", "взамен", "вместо", "вне", "внизу",
	"внутри", "внутрь", "во благо", "вовнутрь", "возле", "вокруг", "впереди", "впредь до", "вроде", "вследствие",
	"для", "до", "за вычетом", "за исключением", "за счёт", "заместо", "из", "из-за", "из-под", "изнутри", "изо",
	"исходя из", "кроме", "кругом", "меж", "между", "мимо", "на благо", "на виду у", "на глазах у", "на предмет",
	"наверху", "накануне", "наподобие", "напротив", "насупротив", "насчёт", "начиная с", "не без", "не считая",
	"недалеко от", "независимо от""", "ниже", "обок", "около", "окромя", "округ", "от", "от имени", "от лица",
	"относительно", "ото", "по линии", "по мере", "по поводу", "по причине", "по случаю", "поблизости от",
	"поверх", "под видом", "под эгидой", "подле", "позади", "помимо", "поперёк", "посередине", "посередь",
	"после", "посреди", "посредине", "посредством", "прежде", "при помощи", "против", "путём", "ради", "с",
	"с ведома", "с помощью", "с точки зрения", "с целью", "сверх", "свыше", "сзади", "снизу", "со", "среди",
	"средь", "супротив", "у"
};

// предлоги дательного падежа
std::vector<std::string>  dPreposition = {
	"благодаря", "в пандан", "вдоль по", "во благо", "вопреки", "вслед", "к", "ко", "лицом к", "на благо",
	"навстречу", "наперекор", "наперерез", "по", "по направлению к", "по отношению к", "подобно",
	"применительно к", "смотря по", "согласно", "сродни", "судя по"
};

// предлоги винительного падежа
std::vector<std::string>  vPreposition = {
	"в", "включая", "во", "за", "на", "невзирая на", "несмотря на", "о", "об", "обо", "по", "по-за", "под",
	"подо", "про", "с", "с прицелом на", "сквозь", "со", "спустя", "через", "чрез"
};

// предлоги предложного падежа
std::vector<std::string>  pPreposition = {"в", "во", "на", "о", "об", "обо", "по", "при"};

// предлоги творительного падежа
std::vector<std::string>  tPreposition = {
	"в связи с", "в соответствии с", "вслед за", "за", "лицом к лицу с", "меж", "между", "над", "надо",
	"наряду с", "перед", "передо", "по сравнению с", "по-над", "под", "подо", "пред", "предо", "рядом с", "с", "следом за", "со"
};

// предлоги творительного падежа
std::vector<std::string>  preposition = {
	"а-ля", "без", "без ведома", "безо", "благодаря", "близ", "близко от", "в", "в виде", "в зависимости от",
	"в качестве", "в лице", "в отличие от", "в отношении", "в пандан", "в преддверии", "в продолжение",
	"в результате", "в роли", "в связи с", "в силу", "в соответствии с", "в течение", "в целях", "вблизи",
	"ввиду", "вглубь", "вдогон", "вдоль", "вдоль по", "взамен", "включая", "вкруг", "вместо", "вне", "внизу",
	"внутри", "внутрь", "во", "вовнутрь", "возле", "вокруг", "вопреки", "вослед", "впереди", "вплоть до",
	"впредь до", "вразрез", "вроде", "вслед", "вслед за", "вследствие", "для", "для-ради", "до", "за",
	"за вычетом", "за исключением", "за счёт", "заместо", "из", "из-за", "из-под", "изнутри", "изо", "исключая",
	"исходя из", "к", "касательно", "ко", "кроме", "кругом", "лицом к лицу с", "меж", "между", "мимо", "на",
	"на виду у", "на глазах у", "на предмет", "наверху", "навроде", "навстречу", "над", "надо", "назад", "назади",
	"накануне", "наместо", "наперекор", "наперерез", "наподобие", "напротив", "наряду с", "насупротив", "насчёт",
	"начиная с", "не без", "не считая", "невзирая на", "недалеко от", "независимо от", "несмотря", "несмотря на",
	"ниже", "о", "об", "обо", "обок", "около", "окрест", "окромя", "округ", "опосля", "опричь", "от", "от … до",
	"от имени", "от лица", "относительно", "ото", "перед", "передо", "по", "по линии", "по мере",
	"по направлению к", "по отношению к", "по поводу", "по причине", "по случаю", "по сравнению с", "по-за",
	"по-над", "по-под", "поблизости от", "поверх", "под", "под видом", "под эгидой", "подле", "подо", "подобно",
	"позади", "позднее", "помимо", "поперёд", "поперёк", "порядка", "посверху", "посередине", "посередь", "после",
	"посреди", "посредине", "посредством", "пред", "предо", "прежде", "при", "при помощи", "применительно к",
	"про", "промеж", "против", "противно", "противу", "путём", "ради", "рядом с", "с", "с ведома", "с помощью",
	"с прицелом на", "с точки зрения", "с целью", "сверх", "сверху", "свыше", "середи", "середь", "сзади",
	"скрозь", "следом за", "смотря по", "снизу", "со", "согласно", "спустя", "среди", "средь", "сродни",
	"судя по", "супротив", "у", "через", "черезо", "чрез"
};


std::unique_ptr<freeling_server::sequence_processor> freeling_server::build_preposition_processor() {
	std::vector<std::string> data;
	data.insert(data.end(), rPreposition.begin(), rPreposition.end());
	data.insert(data.end(), dPreposition.begin(), dPreposition.end());
	data.insert(data.end(), vPreposition.begin(), vPreposition.end());
	data.insert(data.end(), pPreposition.begin(), pPreposition.end());
	data.insert(data.end(), tPreposition.begin(), tPreposition.end());
	data.insert(data.end(),  preposition.begin(),  preposition.end());

	return std::make_unique<sequence_processor_impl>(data, "B0");
}


freeling_server::ru_processor* freeling_server::ru_processor::inst = nullptr;

// TODO add lock
freeling_server::ru_processor* freeling_server::ru_processor::instance() {
	if (inst == nullptr) {
		inst = new ru_processor();
	}
	return inst;
}

freeling_server::sentence_type freeling_server::ru_processor::process(const sentence_type& sent) const {
	
	freeling_server::sentence_type res1 = union_processor->process(sent);
	freeling_server::sentence_type result = preposition_processor->process(res1);
	return std::move(result);
}
