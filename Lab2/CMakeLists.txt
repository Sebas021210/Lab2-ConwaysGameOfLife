cmake_minimum_required(VERSION 3.25)
project(Lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SDL2_INCLUDE_DIR "C:/Libs/SDL/include")
set(SDL2_LIB_DIR "C:/Libs/SDL/lib/x64")

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(Lab2 main.cpp)
target_link_libraries(Lab2 SDL2main SDL2)
