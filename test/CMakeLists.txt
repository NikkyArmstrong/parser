add_executable(test test_main.cpp)

list(APPEND EXTRA_LIBS src)
target_link_libraries(test PUBLIC ${EXTRA_LIBS})

target_include_directories(test PUBLIC "${PROJECT_BINARY_DIR}")