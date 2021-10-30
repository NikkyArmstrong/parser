add_library(3rdparty catch.hpp)

list(APPEND EXTRA_LIBS 3rdparty)
target_link_libraries(3rdparty PUBLIC ${EXTRA_LIBS})

target_include_directories(3rdparty PUBLIC "${PROJECT_BINARY_DIR}")