cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 11)

project(Monopoly)
include_directories(include)
add_executable(Monopoly "src/monopoly.cpp")
target_include_directories(Monopoly PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(Monopoly PRIVATE ${Monopoly})