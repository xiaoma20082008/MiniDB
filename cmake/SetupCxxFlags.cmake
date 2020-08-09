include(CheckCXXCompilerFlag)

set(CXX_COMMON_FLAGS "-Wall -Werror -Wno-c++98-compat -Wno-c++98-compat-pedantic")
if (APPLE)
    set(CXX_COMMON_FLAGS "${CXX_COMMON_FLAGS} -Wno-braced-scalar-init") # AppleClang needs this while upstream Clang and GCC are reasonable
endif()
set(CXX_ONLY_FLAGS "-std=c++17 -fPIC -mcx16 -march=native -fvisibility=hidden")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif (NOT CMAKE_BUILD_TYPE)
