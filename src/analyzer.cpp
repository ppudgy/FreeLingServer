



#include "analyzer.h"


std::string freeling_analyzer::analyzer::analyze(const std::string& text){
	
	return text + " is analyzed.";
}




freeling_analyzer::analyzer* freeling_analyzer::analyzer_pool::get(const std::string& lang){
	return nullptr;
}




void freeling_analyzer::analyzer_pool::store(analyzer* analyzer){

}








