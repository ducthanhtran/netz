cmake_minimum_required(VERSION 3.1)

project(netz LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(netz INTERFACE)
target_include_directories(netz INTERFACE include/)

file(GLOB_RECURSE test_src test/*.cpp)
add_executable(test ${test_src})
target_link_libraries(test netz)
