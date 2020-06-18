
include_directories(${CMAKE_SOURCE_DIR}/src/inc)


# TestLexer
add_executable(LexerTest SqlLexerTest.cpp)
target_link_libraries(LexerTest gtest)


# TestRelNode
add_executable(RelTest RelNodeTest.cpp)
target_link_libraries(RelTest gtest)

# Test Page
add_executable(PageTest PageTest.cpp)
target_link_libraries(PageTest gtest)

# Test BTree
add_executable(BTreeTest BTreeTest.cpp)
target_link_libraries(BTreeTest gtest)