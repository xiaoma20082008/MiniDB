cmake_minimum_required(VERSION 3.16)
set(NAME MiniDB)
project(${NAME})

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib" )

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third-party)

include_directories(src)

add_executable(${NAME} main.cpp)

TARGET_LINK_LIBRARIES(${NAME} mini_db)
target_link_libraries(${NAME} spdlog)
