cmake_minimum_required(VERSION 3.16)
set(NAME MiniDB)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(test)

include_directories(src)

add_executable(${NAME} main.cpp)

TARGET_LINK_LIBRARIES(${NAME} mini_db)
