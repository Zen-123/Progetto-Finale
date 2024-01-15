cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)

project(Monopoly)

include_directories(include gameLib playerLib squareLib )
add_executable(Monopoly "src/monopoly.cpp")

target_include_directories(Monopoly PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(Monopoly  ${Monopoly})
set(CMAKE_CXX_FLAGS_RELEASE "-O2")