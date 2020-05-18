
include_directories(${CMAKE_SOURCE_DIR}/src/inc)


# TestLexer
add_executable(LexerTest SqlLexerTest.cpp)
target_link_libraries(LexerTest gtest)


# TestRelNode
add_executable(RelTest RelNodeTest.cpp)
target_link_libraries(RelTest gtest)