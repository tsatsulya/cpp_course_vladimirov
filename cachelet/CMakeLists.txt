# # add_subdirectory(include/cache_tester)
# cmake_minimum_required(VERSION 3.14)
# project(cachelet)
# add_library(cachelet INTERFACE)
# target_include_directories(cachelet INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_compile_features(cachelet INTERFACE cxx_std_17)


# get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
# if (NOT IS_SUBPROJECT)
#     add_subdirectory(tester)
# endif()


cmake_minimum_required(VERSION 3.10)

project(
        cache
        DESCRIPTION "LFU and perfect caching algorithm implementation"
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

set(library_compile_options -O2)

add_library(cachelet INTERFACE)
target_include_directories(cachelet INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_features(cachelet INTERFACE cxx_std_17)

target_compile_options(
        cachelet INTERFACE 
        $<BUILD_INTERFACE:${library_compile_options}>
        )

install(DIRECTORY include DESTINATION include)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)
if (NOT IS_SUBPROJECT)
        add_subdirectory(tester)
endif()