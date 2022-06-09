cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project("SuiteTest" LANGUAGES CXX C ASM)

SET(SOURCES
	Dummy.cpp
)

SET(INCLUDES
	${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(${PROJECT_NAME}_ut ${SOURCES})
target_link_libraries(${PROJECT_NAME}_ut PUBLIC
	CppUTest
	CppUTestExt
	TargetConfiguration
)

if(${BUILD_FOR_DEVICE})
	stm32_print_size_of_target(${PROJECT_NAME}_ut)
	stm32_generate_binary_file(${PROJECT_NAME}_ut)
endif()

add_test(NAME ${PROJECT_NAME}_ut COMMAND ${PROJECT_NAME}_ut)



