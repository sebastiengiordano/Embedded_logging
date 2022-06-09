cmake_minimum_required(VERSION 3.18.4 FATAL_ERROR)

project(libs LANGUAGES CXX C ASM)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src/)
