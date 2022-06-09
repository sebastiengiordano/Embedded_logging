cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)
project("tests" VERSION 1.0 LANGUAGES CXX C ASM )

message(STATUS "Compiling tests for ${APP_BUILD_TARGET_BOARD}")

option(VERBOSE_BUILD "Have a verbose build process" OFF)
option(CONTINUOUS_INTEGRATION_OPTION "Configure test for continuous integration" OFF)

if(VERBOSE_BUILD)
    set(CMAKE_VERBOSE_MAKEFILE ON)
endif()

SET(CppUTestRootDirectory ${CMAKE_SOURCE_DIR}/thirds/cpputest)
SET(CppUTestLibName CppUTest)
SET(CppUTestExtLibName CppUTestExt)

if(${BUILD_FOR_HOST})
	if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
		SET(CPP_PLATFORM VisualCpp)
	elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
		SET(CPP_PLATFORM Gcc)
	else()
		message( FATAL_ERROR "Platform ${CPP_PLATFORM} is not supported.")
	endif()
endif()

add_subdirectory(${CppUTestRootDirectory}/src/CppUTest ${CMAKE_BINARY_DIR}/CppUTest)
add_subdirectory(${CppUTestRootDirectory}/src/CppUTestExt ${CMAKE_BINARY_DIR}/CppUTestExt)


if( ${BUILD_FOR_DEVICE} )
	target_compile_definitions(CppUTest PUBLIC
		CPPUTEST_STD_CPP_LIB_DISABLED
		CPPUTEST_MEM_LEAK_DETECTION_DISABLED
	)
	target_compile_definitions(CppUTestExt PUBLIC
		CPPUTEST_STD_CPP_LIB_DISABLED
		CPPUTEST_MEM_LEAK_DETECTION_DISABLED
	)
	target_sources(CppUTest	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/UtestPlatform.cpp

	)
	target_sources(CppUTestExt PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/UtestPlatform.cpp
	)

endif()

add_library(TargetConfiguration INTERFACE)	# This is mainly usefull for hardware target, it allow to pass specific link, source and compile options

if(CONTINUOUS_INTEGRATION_OPTION)
	message("Format test output for teamcity")
	target_compile_definitions(TargetConfiguration INTERFACE TEAMCITY_FORMAT)
	message("Mark as continuous integration")
	target_compile_definitions(TargetConfiguration INTERFACE CONTINOUS_INTEGRATION_PLATFORM)	# Used to ignore some test during on continuous integration
endif()


# TODO Handle this part from board module
if(${BUILD_FOR_DEVICE})
	target_sources(CppUTest	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DeviceAllTest.cpp
	)
	target_sources(TargetConfiguration INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/syscalls.c)
	target_link_libraries(TargetConfiguration INTERFACE
    HAL::STM32::${MCU_FAMILY}::CORTEX
    HAL::STM32::${MCU_FAMILY}::GPIO
    HAL::STM32::${MCU_FAMILY}::PWREx
    HAL::STM32::${MCU_FAMILY}::RCC
    HAL::STM32::${MCU_FAMILY}::RCCEx
    HAL::STM32::${MCU_FAMILY}::UART
    HAL::STM32::${MCU_FAMILY}::UARTEx
    CMSIS::STM32::${MCU_CMSIS_DEVICE}
		STM32::Nano
        "-Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map"
	)
	target_include_directories(TargetConfiguration INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}
	)
endif()

if(${BUILD_FOR_HOST})

	target_compile_definitions(CppUTest PUBLIC
		CPPUTEST_MEM_LEAK_DETECTION_DISABLED
	)

	target_compile_definitions(CppUTestExt PUBLIC
	    CPPUTEST_MEM_LEAK_DETECTION_DISABLED
	)
	target_sources(CppUTest	PRIVATE
		./HostAllTest.cpp
	)
endif()
add_subdirectory(SuiteTestFramework ${CMAKE_BINARY_DIR}/tests/SuiteTestFramework)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/libs/tests ${CMAKE_BINARY_DIR}/tests/libs)

# Test Suite to run only on hardware
if(${BUILD_FOR_DEVICE} )
#add_subdirectory(SystemSuite)
endif()