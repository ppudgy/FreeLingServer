#define IOD_PCL_WITH_EXCEPTIONS

/**
 * FreeLing http interface
 *
 *
 *
 *
 *
 * 
 */
#include <string>
#include <assert.h>
#include <iostream>



using namespace s;
using namespace sl;
using namespace iod;


auto hello_api = http_api(
    GET / _freeling * get_parameters(_text = std::string()) = [] (mhd_request* req, mhd_response* resp,  auto p) {

        const char* ac_lang = req->get_header("Accept-Language");
        const char* ac_acc = req->get_header("Accept");


        std::string result = "freeling " + p.text;
        return result;
    },

    GET = [] ()
    {
        return "about";
    }

);

