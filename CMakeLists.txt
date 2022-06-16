cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)

set(APP_BUILD_APPLICATION "TESTS" CACHE STRING "Set the application to build")
set_property(CACHE APP_BUILD_APPLICATION PROPERTY STRINGS
    TESTS
    EMBEDDED_LOGGING
)

set(APP_BUILD_TARGET_BOARD "NONE" CACHE STRING "Target BOARD")
set_property(CACHE APP_BUILD_TARGET_BOARD PROPERTY STRINGS
    HOST
    CUSTOM-G0
)

set(TARGET_DEFINED OFF)

set(BUILD_FOR_HOST OFF)
set(BUILD_FOR_DEVICE ON)

if(${APP_BUILD_TARGET_BOARD} MATCHES "HOST")
    set(BUILD_FOR_HOST ON)
    set(BUILD_FOR_DEVICE OFF)

    set(TARGET_DEFINED ON)
endif()


if(${APP_BUILD_TARGET_BOARD} MATCHES "CUSTOM-G0")
    set(MCU_FAMILY "G0")
    set(MCU_TYPE "G0B1xx")
    set(MCU_CMSIS_DEVICE "G0B1KE")
    set(TARGET_DEFINED ON)
endif()

if(${APP_BUILD_TARGET_BOARD} MATCHES "EUROPRO-CIA1")
    set(MCU_FAMILY "G0")
    set(MCU_TYPE "G030xx")
    set(MCU_CMSIS_DEVICE "G030J6")
    set(TARGET_DEFINED ON)
endif()


if(NOT ${TARGET_DEFINED})
    message(FATAL_ERROR "Target ${APP_BUILD_TARGET_BOARD} is not supported")
endif()

if(${BUILD_FOR_DEVICE})

    if ("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
        set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/thirds/stm32-cmake/cmake/stm32_gcc.cmake)
        message(STATUS "No CMake toolchain defined using default: ${CMAKE_TOOLCHAIN_FILE}")
    else()
        message(STATUS "CMake toolchain file is ${CMAKE_TOOLCHAIN_FILE}")
    endif()

    if(NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
        message(FATAL_ERROR "Toolchain file doesn't exist : ${CMAKE_TOOLCHAIN_FILE}")
    endif()
endif()

if(${BUILD_FOR_HOST} AND NOT ${APP_BUILD_APPLICATION} MATCHES "TESTS")
    message(STATUS "APP_BUILD_APPLICATION: ${APP_BUILD_APPLICATION}")
    message(STATUS "APP_BUILD_TARGET: ${APP_BUILD_TARGET_BOARD}")
    message(FATAL_ERROR "Only 'TESTS' can be build on host, please change APP_BUILD_APPLICATION or APP_BUILD_TARGET_BOARD")
endif()


# https://stackoverflow.com/questions/53633705/cmake-the-c-compiler-is-not-able-to-compile-a-simple-test-program/53635241
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

project(firmware VERSION 1.0 LANGUAGES C CXX ASM)

# set(IDF_PATH ${PROJECT_SOURCE_DIR}/thirds/esp-idf)
# set($ENV{IDF_PATH} ${PROJECT_SOURCE_DIR}/thirds/esp-idf)
# include(${PROJECT_SOURCE_DIR}/thirds/esp-idf/tools/cmake/project.cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/thirds/plog)
add_compile_definitions(_GNU_SOURCE)
# link_libraries(esp-idf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${BUILD_FOR_DEVICE})
    #LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirds/stm32-cmake/cmake)
    set(STM32_CUBE_G0_PATH ${CMAKE_CURRENT_SOURCE_DIR}/thirds/STM32CubeG0)
    message(STATUS "${STM32_CUBE_G0_PATH}" )
    #set(STM32_CUBE_L4_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules/STM32CubeL4)
    #list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Src/Boards)

    # Search all HAL and CMSIS components requiered by all application
    set(STM32_FAMILY_LIST STM32G0)
    set(HAL_COMP_LIST
        CORTEX DMA GPIO PCD PWR RCC TIM UART
        STM32G0
    )
    find_package(CMSIS COMPONENTS "${STM32_FAMILY_LIST}" REQUIRED)
    find_package(HAL COMPONENTS "${HAL_COMP_LIST}" REQUIRED)

    link_libraries(CMSIS::STM32::${MCU_TYPE})

    #add_subdirectory(${CMAKE_SOURCE_DIR}/Src/Boards)
endif()

#message(STATUS "Configure for ${APP_BUILD_APPLICATION}")
add_subdirectory(${PROJECT_SOURCE_DIR}/src/libs)
if(${APP_BUILD_APPLICATION} MATCHES "EMBEDDED_LOGGING")
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/apps)
endif()

if(${APP_BUILD_APPLICATION} MATCHES "TESTS")
    enable_testing()
    add_subdirectory(${PROJECT_SOURCE_DIR}/src/tests)
endif()
