cmake_minimum_required(VERSION 3.16)

set(MINI_DB_VERSION_MAJOR "1")
set(MINI_DB_VERSION_MINOR "0")
set(MINI_DB_VERSION_PATCH "0")
set(MINI_DB_VERSION "${MINI_DB_VERSION_MAJOR}.${MINI_DB_VERSION_MINOR}.${MINI_DB_VERSION_PATCH}")
set(MINI_DB_SO_VERSION "${MINI_DB_VERSION}")

project(MiniDB
        LANGUAGES C CXX
        VERSION ${MINI_DB_VERSION}
        )

message(STATUS "MiniDB version: ${MINI_DB_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake_modules")

include(CMakeParseArguments)
include(ExternalProject)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS  OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "${CXX_COMMON_FLAGS} ${CXX_ONLY_FLAGS}")

###################################################
# CMAKE OPTIONS
###################################################

option(MINI_DB_BUILD_STATIC
        "Build the libmini_db static libraries"
        ON)

option(MINI_DB_BUILD_SHARED
        "Build the libmini_db shared libraries"
        ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")


include_directories(${PROJECT_SOURCE_DIR}/src/inc)


add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(third-party)


add_executable(MiniDB main.cpp)

target_link_libraries(MiniDB mini_db_static)
