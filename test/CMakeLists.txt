
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(LexerTest SqlLexerTest.cpp)
add_executable(RelTest RelNodeTest.cpp)

target_link_libraries(LexerTest gtest)
target_link_libraries(RelTest gtest)