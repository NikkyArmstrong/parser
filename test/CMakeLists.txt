add_executable(test test_main.cpp state_tests.cpp)

list(APPEND EXTRA_LIBS src)
target_link_libraries(test PUBLIC ${EXTRA_LIBS})

list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/src)
list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/3rdparty)
list(APPEND EXTRA_INCLUDES ${PROJECT_BINARY_DIR})

target_include_directories(test PUBLIC ${EXTRA_INCLUDES})