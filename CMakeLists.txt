##
#
#
##

cmake_minimum_required(VERSION 3.0)

project(freelingserver)

set(CMAKE_CXX_STANDARD 14)

##set(CMAKE_EXE_LINKER_FLAGS "-static")

#find_library(MICROHTTPD libmicrohttpd)
#set (Boost_USE_MULTITHREADED ON)
#find_package (Boost)


add_definitions(-std=c++14 -fpermissive) # For old cmake versions

###include_directories(include)

set(SOURCE_FILES 
    src/main.cpp
    src/symbols.hh
    src/string_util.cpp
    src/string_util.h
    src/analyzer.cpp
    src/analyzer.h
    src/config.cpp
    src/config.h
    src/html_util.cpp
    src/html_util.h
    )

add_executable(freelingserver ${SOURCE_FILES})
#target_link_libraries(freelingserver microhttpd pthread ${Boost_LIBRARIES})
#target_link_libraries(freelingserver 
#		microhttpd pthread freeling foma treeler z 
#		icui18n icuuc icudata icule icuio iculx icutu icutest
#		${Boost_LIBRARIES}
#		gnutls
#		)


target_link_libraries(freelingserver microhttpd pthread freeling boost_system Jinja2CppLight)

