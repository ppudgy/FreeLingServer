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
    src/sequence_processor.cpp
    src/sequence_processor.h
    src/utils.cpp
    src/utils.h
 )
target_link_libraries(freelingserver pthread freeling boost_system)



add_executable(utils.test
    test/utils.test.cpp
    src/utils.cpp
    src/utils.h
    )
target_link_libraries(utils.test freeling boost_system)


add_executable(sp.test
    test/sp.test.cpp
    src/sequence_processor.h
    src/sequence_processor.cpp
    src/utils.cpp
    src/utils.h
    )
target_link_libraries(sp.test freeling boost_system)
