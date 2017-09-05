

#include <string>


#include <stringhelper.h>
#include <Jinja2CppLight.h>


#include "html_util.h"



// TODO choose a same languige text variant            
//  std::map<std::string, std::string> html_lang_map;


std::string html_str = R"html(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="utf-8">
	<title>FreeLingServer about page</title>
</head>
<body>
	<h1>{{name}}</h1> 
	<div> Version:  {{version_major}}.{{version_minor}} </div>
	<div> FreeLing:  {{freeling}} </div>
	<div> Uptime:  {{uptime}} </div>
</body>
</html>
)html";



std::string html::create_html(const std::string& lang, const freeling_analyzer::about_type& about){

	Jinja2CppLight::Template mytemplate( html_str );
    mytemplate.setValue( "name", about.name );
    mytemplate.setValue( "version_major", about.version_major);
    mytemplate.setValue( "version_minor", about.version_minor );
    mytemplate.setValue( "uptime", std::to_string(about.uptime) );
    mytemplate.setValue( "freeling", about.freeling );
    
    string result = mytemplate.render();
	return result;
}
