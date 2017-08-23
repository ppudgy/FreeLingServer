#ifndef FLS_CONFIG_H
#define FLS_CONFIG_H


#include <freeling/morfo/analyzer.h>


namespace freeling_analyzer{



class config{
	
	config(const std::string& lang){};
	config(const config&) = delete;
	const config& operator=(const config&) = delete;
	
	freeling::analyzer::config_options co;
	freeling::analyzer::invoke_options io;
	
	public:
		static config* create_config(const std::string& lang);
		
		
		
		freeling::analyzer::config_options& get_config_option(){return co;}; 
		freeling::analyzer::invoke_options& get_invoke_option(){return io;}; 
	
};


};

#endif
