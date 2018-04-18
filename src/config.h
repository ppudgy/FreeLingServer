#ifndef FLS_CONFIG_H
#define FLS_CONFIG_H

#include <string>
#include <map>
#include <chrono>
//#include <silicon/error.hh>
#include <freeling/morfo/analyzer.h>

//#include "main_symbols.hh"

namespace freeling_server{

//using namespace s;
//using namespace iod;

/*
typedef decltype(D(_name = std::string(),
                   _version_major = int(),
                   _version_minor = int(),
                   _uptime = long(),
                   _freeling = std::string()
                   )) about_type;
                   */
                   
struct about_type{
	std::string name;
	int version_major;
    int version_minor;
    long long uptime;
    std::string freeling;
};                   
                   

class config{
	config(const std::string& lang): _is_init(false), _lang(lang){};
	config(const config&) = delete;
	const config& operator=(const config&) = delete;

	void 				fill_config_option(const std::wstring &path, const std::wstring &lang);
	void 				fill_invoke_option();
	void 				init();
	std::wstring 		get_freeling_path() const;

	bool 				_is_init;
	std::string 		_lang;
	freeling::analyzer::config_options 				co;
	freeling::analyzer::invoke_options 				io;
	
	static bool 		find_freeling_data(const std::string& path);
	
	static std::string 								_freeling_path;
	static std::map<std::string, config*> 			_lang_config_map;
	static std::map<std::string, bool>    			_lang_suport_map;
	static std::chrono::system_clock::time_point 	_start;

public:
	static config* 		create_config(const std::string& lang);
	static bool 		initialize(const std::string& path);
	static bool 		is_lang_supported(const std::string& lang);
	//static std::string 	get_root_html(const std::string& lang, const about_type& about);
	static about_type 	get_about();
		
	freeling::analyzer::config_options& 			get_config_option(){return co;}; 
	freeling::analyzer::invoke_options& 			get_invoke_option(){return io;}; 
	
}; // class config

}; // namespace freeling_server

#endif
