//#define IOD_PCL_WITH_EXCEPTIONS

/**
 * FreeLing http interface
 *
 *
 *
 *
 *
 *
 */

#include <unistd.h>
#include <string>
#include <assert.h>
#include <iostream>

#include <iod/parse_command_line.hh>

#include "analyzer.h"
#include "config.h"
#include "main_api.h"


int main(const int argc, const char* argv[])
{
	

    auto opts = parse_command_line(argc, argv, _port = int(8585), _nodaemon = bool(false), _freeling = std::string("/usr/local/share/freeling"));
    if(!opts.nodaemon){
        if(0 != daemon(0, 0)){
            perror(argv[0]);
            exit(1);
        }
    }
	std::string freeling_path = opts.freeling;
	if(!freeling_server::config::initialize(freeling_path))
	{
		std::cerr << "do not find freeling data path" << std::endl;
		exit(2);
	}

    int port = opts.port;
    auto ctx = sl::mhd_json_serve(hello_api, middleware_factories(freeling_server::analyzer_factory()),port);

    return 0;
}
