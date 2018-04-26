cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

project(tree)

add_library(tree STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/Tree.cpp)
add_library(tui STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/Tui.cpp)

target_include_directories(tree PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_include_directories(tui PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
if(BUILD_EXAMPLES)
  file(GLOB EXAMPLE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/examples/*.cpp")
  foreach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE_SOURCE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE_SOURCE})
    target_link_libraries(${EXAMPLE_NAME} tree tui)
    install(TARGETS ${EXAMPLE_NAME}
      RUNTIME DESTINATION bin
    )
  endforeach(EXAMPLE_SOURCE ${EXAMPLE_SOURCES})
endif()

install(TARGETS tree tui
    EXPORT tree-config
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION include)
install(EXPORT tree-config DESTINATION cmake)

if(BUILD_TESTS)
enable_testing()
file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
target_link_libraries(check tree tui ${DEPENDS_LIBRARIES})
add_test(NAME check COMMAND check "-s" "-r" "compact" "--use-colour" "yes")

	if (${CMAKE_BUILD_TYPE} MATCHES "Coverage")
	set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
	include(CodeCoverage)
	set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
	set(LCOV_REMOVE_EXTRA "'tests/*'")
        set(LCOV_REMOVE_EXTRA "'sources/Tui.cpp'") 
	add_executable(unit_tests ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_TEST_SOURCES})
	target_link_libraries(unit_tests tree tui ${DEPENDS_LIBRARIES})
	setup_target_for_coverage(unit_tests_coverage unit_tests coverage)
	else()
	add_test(NAME unit_tests COMMAND check "-s" "-r" "compact" "--use-colour" "yes")
	endif()
endif()
