##
#
#
##

cmake_minimum_required(VERSION 3.0)

project(freelingserver)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)


add_executable(freelingserver
	src/main.cpp

    src/analyzer.cpp
    src/analyzer.h
    src/config.cpp
    src/config.h
    src/preposition_utils.cpp
    src/preposition_utils.h
    src/union_utils.cpp
    src/union_utils.h
    src/utils.cpp
    src/utils.h
 )
target_link_libraries(freelingserver pthread freeling boost_system )
