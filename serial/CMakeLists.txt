cmake_minimum_required (VERSION 2.6)
project (SerialTest)

include (Sources.cmake)
set (ALL_SOURCES ${SOURCES} test/main.cpp)

include_directories ("${CMAKE_SOURCE_DIR}")
add_executable (SerialTest ${ALL_SOURCES})
