add_library(3rdparty catch.hpp)

set_target_properties(3rdparty PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(3rdparty PUBLIC "${PROJECT_BINARY_DIR}")