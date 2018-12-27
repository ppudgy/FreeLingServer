#include <sys/stat.h>

#include <string>
#include <regex>
#include <locale>
//#include <codecvt>
#include <stdexcept>

//#include <stringhelper.h>

#include "utils.h"
#include "config.h"

char DEFAULT_FREELING_PATH[] = "/usr/local/share/freeling";

std::string freeling_server::config::_freeling_path = "";
std::map<std::string, std::shared_ptr<freeling_server::config>> freeling_server::config::_lang_config_map;
std::map<std::string, bool> freeling_server::config::_lang_suport_map = {{"ru", true}, {"en", true}};
std::chrono::system_clock::time_point 	freeling_server::config::_start;



bool freeling_server::config::is_lang_supported(const std::string lang) {
	bool result = _lang_suport_map[lang];
	return result;
}

std::shared_ptr<freeling_server::config> freeling_server::config::create_config(const std::string& lang){
	if(is_lang_supported(lang)){
		if(_lang_config_map.find(lang) == _lang_config_map.end()){
			//auto& [iterator, created] = _lang_config_map.emplace({ lang, make_shared<config>(lang)});
			
			auto ptr = make_shared<config>(lang);
			ptr->init();
			
			_lang_config_map[lang] = ptr;
			
			//auto& res = _lang_config_map.emplace( {lang, ptr});
			//if(res.second)
			//{
			//	auto iterator = res.first;
			//	(*iterator).init();
			//}
			return ptr;
		}else{
			return _lang_config_map[lang];
		}
		//auto result = _lang_config_map[lang];
		//if(result == nullptr){
		//	result = new config(lang);
		//	result->init();
		//	_lang_config_map[lang] = result;
		//}
		//return iterator.second;
	}
	throw std::invalid_argument( lang + " is not suported language");
}

bool freeling_server::config::initialize(const std::string path){
	freeling::util::init_locale(L"ru_RU.UTF-8");
// init start time	
	_start = std::chrono::system_clock::now();
// init freeling path	
	if(path.size() > 0)
		_freeling_path = path;
	if(!find_freeling_data(_freeling_path)){
		char* env = getenv("FREELINGSHARE");
		if(!env){
			env = DEFAULT_FREELING_PATH;
		}
		std::string tmp(env);
		_freeling_path = tmp;
		if(!find_freeling_data(_freeling_path)){
			env = DEFAULT_FREELING_PATH;
			std::string tmp(env);
			_freeling_path = tmp;
			if(!find_freeling_data(_freeling_path)){
				return false;
			}
		}
	}
	_freeling_path = path;
	return true;
}


void freeling_server::config::init(){
	if(_is_init) return;
	std::wstring path;
	std::wstring wlang = freeling::util::string2wstring(_lang);
	path = get_freeling_path();
	fill_config_option(path, wlang);
	fill_invoke_option();
	_is_init = true;
}

std::wstring freeling_server::config::get_freeling_path() const{
	std::wstring result;
	result = freeling::util::string2wstring(_freeling_path);
	return result;
}

void freeling_server::config::fill_config_option(const std::wstring &path, const std::wstring &lang) {
  /// Language of text to process
  co.Lang = lang;
  // path to language specific data
  std::wstring lpath = path + L"/" + co.Lang + L"/";
  /// Tokenizer configuration file
  co.TOK_TokenizerFile = lpath + L"tokenizer.dat";
  /// Splitter configuration file
  co.SPLIT_SplitterFile = lpath + L"splitter.dat";
  /// Morphological analyzer options
  co.MACO_Decimal = L".";
  co.MACO_Thousand = L",";
  co.MACO_LocutionsFile = lpath + L"locucions.dat";
  co.MACO_QuantitiesFile = lpath + L"quantities.dat";
  co.MACO_AffixFile = lpath + L"afixos.dat";
  co.MACO_ProbabilityFile = lpath + L"probabilitats.dat";
  co.MACO_DictionaryFile = lpath + L"dicc.src";
  co.MACO_NPDataFile = lpath + L"np.dat";
  co.MACO_PunctuationFile = path + L"/common/punct.dat";
  co.MACO_ProbabilityThreshold = 0.001;
  /// NEC config file
//  co.NEC_NECFile = lpath + L"nerc/nec/nec-ab-poor1.dat";
  /// Sense annotator and WSD config files
  co.SENSE_ConfigFile = lpath + L"senses.dat";
  co.UKB_ConfigFile = lpath + L"ukb.dat";
  /// Tagger options
  co.TAGGER_HMMFile = lpath + L"tagger.dat";
  
  
  co.TAGGER_ForceSelect=  freeling::RETOK;
  /// Chart parser config file
	//  co.PARSER_GrammarFile = lpath + L"chunker/grammar-chunk.dat";
  /// Dependency parsers config files
	//  co.DEP_TxalaFile = lpath + L"dep_txala/dependences.dat";   
	//  co.DEP_TreelerFile = lpath + L"dep_treeler/dependences.dat";   
  /// Coreference resolution config file
	//  co.COREF_CorefFile = lpath + L"coref/relaxcor/relaxcor.dat";
}

///////////////////////////////////////////////////
/// Load an ad-hoc set of invoke options

void freeling_server::config::fill_invoke_option() {
  /// Level of analysis in input and output
  io.InputLevel = freeling::TEXT;
  io.OutputLevel = freeling::DEP;
  /// activate/deactivate morphological analyzer modules
  io.MACO_UserMap = false;
  io.MACO_AffixAnalysis = true;
  io.MACO_MultiwordsDetection = true;
  io.MACO_NumbersDetection = true;
  io.MACO_PunctuationDetection = true;
  io.MACO_DatesDetection = true;
  io.MACO_QuantitiesDetection  = true;
  io.MACO_DictionarySearch = true;
  io.MACO_ProbabilityAssignment = true;
  io.MACO_CompoundAnalysis = false;
  io.MACO_NERecognition = false;
  io.MACO_RetokContractions = false;
  
  io.NEC_NEClassification = false;
  io.PHON_Phonetics = false;
  
  io.SENSE_WSD_which = freeling::UKB;
  io.TAGGER_which = freeling::HMM;
  io.DEP_which = freeling::TREELER;
}

bool freeling_server::config::find_freeling_data(const std::string& path){
	struct stat  buf;
	std::string freeling_en (path + "/en");
	std::string freeling_ru (path + "/ru");
	
	if(stat(freeling_en.c_str(), &buf) == 0 && stat(freeling_ru.c_str(), &buf) == 0){
		std::string freeling_en_tock (freeling_en + "/tokenizer.dat");
		std::string freeling_ru_tock (freeling_ru + "/tokenizer.dat");
		if(stat(freeling_en_tock.c_str(), &buf) == 0  && stat(freeling_ru_tock.c_str(), &buf) == 0){
			return true;
		}
	}
	return false;
}

freeling_server::about_type freeling_server::config::get_about(){
	about_type result;
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	result.name = "freelingserver";
	result.version_major = 0;
	result.version_minor = 1;
	result.uptime = std::chrono::duration_cast<std::chrono::milliseconds>(now - _start).count();
	result.freeling = _freeling_path;
	return result;
}



