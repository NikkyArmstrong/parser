cmake_minimum_required(VERSION 3.10)
project(Parser VERSION 1.0)

option(BUILD_TEST "Build the tests" ON)

configure_file (
  "${PROJECT_SOURCE_DIR}/ParserConfig.h.in"
  "${PROJECT_BINARY_DIR}/ParserConfig.h"
  )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
list(APPEND EXTRA_LIBS src)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/src)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/3rdparty)
list(APPEND EXTRA_INCLUDES ${PROJECT_BINARY_DIR})

add_subdirectory(test)
add_subdirectory(3rdparty)

add_executable(Parser main.cpp)

target_link_libraries(Parser PUBLIC ${EXTRA_LIBS})

target_include_directories(Parser PUBLIC ${EXTRA_INCLUDES})