cmake_minimum_required(VERSION 3.16)

# We use the GoogleTest module if it is available (only in CMake 3.9+)
# It requires CMP0054 and CMP0057 to be enabled.
if (POLICY CMP0054)
    cmake_policy(SET CMP0054 NEW)
endif ()
if (POLICY CMP0057)
    cmake_policy(SET CMP0057 NEW)
endif ()

# CMP0075 Include file check macros honor CMAKE_REQUIRED_LIBRARIES
if (POLICY CMP0075)
    cmake_policy(SET CMP0075 NEW)
endif ()

set(PACKAGE_NAME     "minidb")
set(PACKAGE_VERSION  "0.0.1-dev")
set(PACKAGE_STRING   "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_TAR_NAME "${PACKAGE_NAME}-${PACKAGE_VERSION}")

project(${PACKAGE_NAME} C CXX)

set(INC_INSTALL_DIR inc CACHE STRING "The subdirectory where header files should be installed")
set(LIB_INSTALL_DIR lib CACHE STRING "The subdirectory where libraries should be installed")
set(BIN_INSTALL_DIR bin CACHE STRING "The subdirectory where binaries should be installed")

message(STATUS "${PACKAGE_NAME} version: ${PACKAGE_VERSION}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

include(CMakeParseArguments)
include(ExternalProject)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

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
