cmake_minimum_required(VERSION 2.4)

project(netz LANGUAGES CXX)

add_library(netz INTERFACE)
target_include_directories(netz INTERFACE include/)

file(GLOB_RECURSE test_src test/*.cpp)
add_executable(test ${test_src})
target_link_libraries(test netz)
