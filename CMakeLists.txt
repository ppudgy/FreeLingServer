##
#
#
##

cmake_minimum_required(VERSION 3.0)

project(freelingserver)

set(CMAKE_CXX_STANDARD 14)
add_definitions( -std=c++14 -fpermissive) # For old cmake versions

include_directories(src)

set(SOURCE_FILES 
    src/main.cpp
    src/main_api.h
    src/main_symbols.hh
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

add_executable(freelingserver ${SOURCE_FILES})
target_link_libraries(freelingserver microhttpd pthread freeling boost_system)

##set(SIMPLE_TEST_FILES test/simple-test.cpp src/main_api.h src/main_symbols.hh)

##add_executable(simple-test test/simple-test.cpp src/main_api.h src/main_symbols.hh)
##target_link_libraries(simple-test  pthread boost_system curl)



