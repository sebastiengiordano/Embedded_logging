cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project("LibsTests" VERSION 1.0 LANGUAGES CXX C ASM)

set(LIBS_DIR ${CMAKE_SOURCE_DIR}/src/libs)
set(LIBS_SOURCES_DIR ${LIBS_DIR}/src)
set(LIBS_TESTS_DIR ${LIBS_DIR}/tests)

add_subdirectory(${LIBS_TESTS_DIR}/assertion ${CMAKE_BINARY_DIR}/tests/libs/assertion)
add_subdirectory(${LIBS_TESTS_DIR}/assertion-disabled ${CMAKE_BINARY_DIR}/tests/libs/assertion-disabled)
# add_subdirectory(${LIBS_TESTS_DIR}/logging ${CMAKE_BINARY_DIR}/tests/libs/logging)
