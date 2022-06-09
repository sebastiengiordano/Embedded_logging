cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project ("LibsTest-Assertion" LANGUAGES CXX C ASM)

SET(SOURCES
    ${LIBS_TESTS_DIR}/assertion/assertion.cpp
)

SET(INCLUDES
    ${LIBS_SOURCES_DIR}
    ${LIBS_TESTS_DIR}
    ${LIBS_DIR}/src/assertion/assertion.h
    ${LIBS_DIR}/src/logging/logging.h
)

include_directories (${INCLUDES})

add_executable (${PROJECT_NAME}_ut ${SOURCES})
target_link_libraries(${PROJECT_NAME}_ut PUBLIC
	CppUTest
	CppUTestExt
	plog
)

add_test(NAME ${PROJECT_NAME}_ut COMMAND ${PROJECT_NAME}_ut)
