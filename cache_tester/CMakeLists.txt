cmake_minimum_required(VERSION 3.14)
project(cache_runner)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(tester ${SRC_FILES})
target_include_directories(tester PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(include/cachelet)

target_link_libraries(tester cachelet)