#
#include(ExternalProject)
#
#
## Build googletest as an external project.
#set(GTEST_INSTALL_DIR ${CMAKE_BINARY_DIR}/third-party/googletest)
#set(GTEST_INCLUDE_DIR ${GTEST_INSTALL_DIR}/include)
#set(GTEST_LIB_DIR ${GTEST_INSTALL_DIR}/lib)
#ExternalProject_Add(gtest_external_project
#        SOURCE_DIR  ${CMAKE_SOURCE_DIR}/third-party/googletest
#        PREFIX      ${GTEST_INSTALL_DIR}
#        INSTALL_DIR ${GTEST_INSTALL_DIR}
#        CMAKE_ARGS  -DCMAKE_INSTALL_PREFIX:PATH=${GTEST_INSTALL_DIR}
#        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
#        -DCMAKE_CXX_FLAGS=${EXTERNAL_PROJECT_CMAKE_CXX_FLAGS}
#        )
#include_directories(BEFORE SYSTEM ${GTEST_INCLUDE_DIR})
#link_directories(${GTEST_LIB_DIR})

add_subdirectory(googletest)
add_subdirectory(spdlog)