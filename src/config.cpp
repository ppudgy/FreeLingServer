
#include "config.h"




freeling_analyzer::config* freeling_analyzer::config::create_config(const std::string& lang){
	config* result = nullptr;
	if(is_lang_supported(lang)){
		result = new config(lang);
		result->init();
	}
	return result;
}

bool is_lang_supported(const std::string& lang) const { // TODO realize
	return true;
}


void freeling_analyzer::config::init(){
	if(_is_init) return;
	std::string path;
	
	path = "";
	fill_config_option(path, _lang);
	
	
	_is_init = true;
}

void freeling_analyzer::config::fill_config_option(const std::string &path, const std::string &lang) {
  /// Language of text to process
  //co.Lang = L"en";
  co.Lang = lang;
 
  // path to language specific data
  wstring lpath = path + "/" + co.Lang + "/";

  /// Tokenizer configuration file
  co.TOK_TokenizerFile = lpath + "tokenizer.dat";
  /// Splitter configuration file
  co.SPLIT_SplitterFile = lpath + "splitter.dat";
  /// Morphological analyzer options
  co.MACO_Decimal = ".";
  co.MACO_Thousand = ",";
  co.MACO_LocutionsFile = lpath + "locucions.dat";
  co.MACO_QuantitiesFile = lpath + "quantities.dat";
  co.MACO_AffixFile = lpath + "afixos.dat";
  co.MACO_ProbabilityFile = lpath + "probabilitats.dat";
  co.MACO_DictionaryFile = lpath + "dicc.src";
  co.MACO_NPDataFile = lpath + "np.dat";
  co.MACO_PunctuationFile = path + "common/punct.dat";
  co.MACO_ProbabilityThreshold = 0.001;

  /// NEC config file
  co.NEC_NECFile = lpath + "nerc/nec/nec-ab-poor1.dat";
  /// Sense annotator and WSD config files
  co.SENSE_ConfigFile = lpath + "senses.dat";
  co.UKB_ConfigFile = lpath + "ukb.dat";
  /// Tagger options
  co.TAGGER_HMMFile = lpath + "tagger.dat";
  co.TAGGER_ForceSelect=  freeling::RETOK;
  /// Chart parser config file
  co.PARSER_GrammarFile = lpath + "chunker/grammar-chunk.dat";
  /// Dependency parsers config files
  co.DEP_TxalaFile = lpath + "dep_txala/dependences.dat";   
  co.DEP_TreelerFile = lpath + "dep_treeler/dependences.dat";   
  /// Coreference resolution config file
  co.COREF_CorefFile = lpath + "coref/relaxcor/relaxcor.dat";
}


///////////////////////////////////////////////////
/// Load an ad-hoc set of invoke options

void freeling_analyzer::config::fill_invoke_option() {

  //analyzer::invoke_options ivk;

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

  //return ivk;
}
