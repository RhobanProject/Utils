cmake_minimum_required (VERSION 2.6)
project (RhobanUtilsTest)

add_subdirectory (.. utils)
include_directories (..)
set (EXTRA_LIBS RhobanUtils)

# Test logging
add_executable (TestLogging test-logging.cpp)
target_link_libraries (TestLogging ${EXTRA_LIBS})

# Test timed thread
add_executable (TestTimedThread test-timed-thread.cpp)
target_link_libraries (TestTimedThread ${EXTRA_LIBS})
