cmake_minimum_required (VERSION 2.6)
project (RhobanUtilsTest)

add_subdirectory (.. utils)
include_directories (..)
set (EXTRA_LIBS RhobanUtils)

# Test logging
add_executable (Tests main.cpp)
target_link_libraries (Tests ${EXTRA_LIBS})
