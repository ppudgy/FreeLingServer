
#include "config.h"




freeling_analyzer::config* freeling_analyzer::config::create_config(const std::string& lang){

	config* result = new config(lang);
	

/*	
	result->co.Lang = util::string2wstring(language);
    result->co.TOK_TokenizerFile = util::string2wstring(tokFile);
    result->co.SPLIT_SplitterFile = util::string2wstring(splitFile);
    result->co.MACO_Decimal = util::string2wstring(macoDecimal);
    result->co.MACO_Thousand = util::string2wstring(macoThousand);
    result->co.MACO_UserMapFile = util::string2wstring(usermapFile);
    result->co.MACO_LocutionsFile = util::string2wstring(locutionsFile);
    result->co.MACO_QuantitiesFile = util::string2wstring(quantitiesFile);
    result->co.MACO_AffixFile = util::string2wstring(affixFile);
    result->co.MACO_ProbabilityFile = util::string2wstring(probabilityFile);
    result->co.MACO_DictionaryFile = util::string2wstring(dictionaryFile);
    result->co.MACO_NPDataFile = util::string2wstring(npDataFile);
    result->co.MACO_PunctuationFile = util::string2wstring(punctuationFile);
    result->co.MACO_CompoundFile = util::string2wstring(compoundFile);
    result->co.PHON_PhoneticsFile = util::string2wstring(phonFile);
    result->co.NEC_NECFile = util::string2wstring(necFile);
    result->co.SENSE_ConfigFile = util::string2wstring(senseFile);
    result->co.UKB_ConfigFile = util::string2wstring(ukbFile);
    result->co.TAGGER_HMMFile = util::string2wstring(hmmFile);
    result->co.TAGGER_RelaxFile = util::string2wstring(relaxFile);
    result->co.PARSER_GrammarFile = util::string2wstring(grammarFile);
    result->co.DEP_TxalaFile = util::string2wstring(txalaFile);
    result->co.DEP_TreelerFile = util::string2wstring(treelerFile);
    result->co.COREF_CorefFile = util::string2wstring(corefFile);
    result->co.SEMGRAPH_SemGraphFile = util::string2wstring(semgraphFile);
*/	
	
	return result;
}
