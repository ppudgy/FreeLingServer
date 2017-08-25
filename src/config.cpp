#include "config.h"
#include "string_util.h"


std::map<std::string, freeling_analyzer::config*> freeling_analyzer::config::_lang_config_map;

freeling_analyzer::config* freeling_analyzer::config::create_config(const std::string& lang){
	//DONE create std::map<std::string, freeling_analyzer::config> and return config from map
	config* result = nullptr;
	if(is_lang_supported(lang)){
		result = _lang_config_map[lang];
		if(result == nullptr){
			result = new config(lang);
			result->init();
			_lang_config_map[lang] = result;
		}
	}
	return result;
}

bool freeling_analyzer::config::is_lang_supported(const std::string& lang) { // TODO realize
	return true;
}


void freeling_analyzer::config::init(){
	if(_is_init) return;
	std::wstring path;
	std::wstring wlang = string_util::utf8_to_wchar_t(_lang);
	path = get_freeling_path();   // TODO realise
	fill_config_option(path, wlang);
	_is_init = true;
}


std::wstring freeling_analyzer::config::get_freeling_path() const{
	std::wstring result;
	char* env = getenv("FREELINGSHARE");
	if(!env){
		env = "/usr/local/share/freeling";   // FIXME  ISO C++ forbids converting a string constant to ‘char*’ [-Wwrite-strings]
	}
	std::string tmp(env);
	result = string_util::utf8_to_wchar_t(tmp);
	return result;
}



void freeling_analyzer::config::fill_config_option(const std::wstring &path, const std::wstring &lang) {
  /// Language of text to process
  //co.Lang = L"en";
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
  co.NEC_NECFile = lpath + L"nerc/nec/nec-ab-poor1.dat";
  /// Sense annotator and WSD config files
  co.SENSE_ConfigFile = lpath + L"senses.dat";
  co.UKB_ConfigFile = lpath + L"ukb.dat";
  /// Tagger options
  co.TAGGER_HMMFile = lpath + L"tagger.dat";
  co.TAGGER_ForceSelect=  freeling::RETOK;
  /// Chart parser config file
  co.PARSER_GrammarFile = lpath + L"chunker/grammar-chunk.dat";
  /// Dependency parsers config files
  co.DEP_TxalaFile = lpath + L"dep_txala/dependences.dat";   
  co.DEP_TreelerFile = lpath + L"dep_treeler/dependences.dat";   
  /// Coreference resolution config file
  co.COREF_CorefFile = lpath + L"coref/relaxcor/relaxcor.dat";
}


///////////////////////////////////////////////////
/// Load an ad-hoc set of invoke options

void freeling_analyzer::config::fill_invoke_option() {
  /// Level of analysis in input and output
  io.InputLevel = freeling::TEXT;
  io.OutputLevel = freeling::COREF;
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
  io.MACO_NERecognition = true;
  io.MACO_RetokContractions = false;
  
  io.NEC_NEClassification = true;
  io.PHON_Phonetics = false;
  
  io.SENSE_WSD_which = freeling::UKB;
  io.TAGGER_which = freeling::HMM;
  io.DEP_which = freeling::TREELER;
}
