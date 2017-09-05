

#include <string>

#include "html_util.h"



//std::map<std::string, std::string> html_lang_map;












std::string html_str = R"html(
<!DOCTYPE html>
<html lang="ru">
<head>
    <meta charset="utf-8">
	<title>FreeLingServer about page</title>
</head>
<body>
	<h1>FreeLingServer</h1> 
	<div> Version  0.1 </div>
</body>
</html>
)html";









std::string html::create_html(const std::string& lang){
	return html_str;
	
	
	
	
}
