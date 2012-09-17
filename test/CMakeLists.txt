cmake_minimum_required (VERSION 2.6)
project (RhobanUtilsTest)

add_subdirectory (.. utils)
include_directories (..)
set (EXTRA_LIBS RhobanUtils)

set (ROBOARD_IP "192.168.16.51"
        CACHE STRING "IP of the destination Roboard")

# Test logging
add_executable (Tests main.cpp)
target_link_libraries (Tests ${EXTRA_LIBS})

add_custom_target (send 
    ${PROJECT_SOURCE_DIR}/send.sh ${ROBOARD_IP})
