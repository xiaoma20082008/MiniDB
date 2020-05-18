file(GLOB_RECURSE MINI_DB_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/inc/*.h)

if (MINI_DB_BUILD_STATIC)
    add_library(mini_db_static STATIC ${MINI_DB_SOURCES})
endif ()

if (MINI_DB_BUILD_SHARED)
    add_library(mini_db_shared SHARED ${MINI_DB_SOURCES})
endif ()

target_link_libraries(mini_db_static spdlog)
target_link_libraries(mini_db_shared spdlog)