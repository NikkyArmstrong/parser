add_library(src Parser.cpp State.cpp)

target_include_directories(src INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})