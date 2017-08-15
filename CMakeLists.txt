##
#
#
##

cmake_minimum_required(VERSION 3.0)

project(freelingserver)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_EXE_LINKER_FLAGS "-static")

find_library(MICROHTTPD libmicrohttpd)



add_definitions(-std=c++14 -fpermissive) # For old cmake versions

###include_directories(include)

set(SOURCE_FILES 
    src/main.cpp
    src/symbols.hh
    src/string_util.cpp
    src/string_util.h
    src/analyzer.cpp
    src/analyzer.h
    )

add_executable(freelingserver ${SOURCE_FILES})
target_link_libraries(freelingserver microhttpd pthread)
