#ifndef FLS_CONFIG_H
#define FLS_CONFIG_H


#include <freeling/morfo/analyzer.h>


namespace freeling_analyzer{



class config{
	
	config(const std::string& lang): _is_init(false), _lang(lang){};
	config(const config&) = delete;
	const config& operator=(const config&) = delete;
	
	bool is_lang_supported(const std::string& lang) const;
	void fill_config_option(const std::string &path, const std::string &lang);
	void fill_invoke_option();
	
	bool _is_init;
	std::string _lang;
	freeling::analyzer::config_options co;
	freeling::analyzer::invoke_options io;
	
	public:
		static config* create_config(const std::string& lang);
		
		
		void init();
		
		
		
		freeling::analyzer::config_options& get_config_option(){return co;}; 
		freeling::analyzer::invoke_options& get_invoke_option(){return io;}; 
	
};


};

#endif
