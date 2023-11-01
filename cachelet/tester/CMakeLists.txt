file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(tester ${SRC_FILES})
set_target_properties(
	tester PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
target_link_libraries(tester PRIVATE cachelet)
target_include_directories(tester PRIVATE include)

option(GEN_EXTRA "Enables additional testing" OFF)
if (GEN_EXTRA)
        if (NOT DEFINED GEN_EXTRA_NUM)
                set(GEN_EXTRA_NUM 1)
        endif()
else()
        set(GEN_EXTRA_NUM 0)
endif()

# configure_file(${CNF}/auto_conf.hpp.in auto_conf.hpp @ONLY)
target_include_directories(tester PRIVATE ${CMAKE_CURRENT_BINARY_DIR})