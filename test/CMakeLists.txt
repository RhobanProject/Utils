option (ROBOARD
    "Compile for Roboard" OFF)

if (ROBOARD)
    set (CMAKE_CXX_FLAGS "-m32 -mtune=i586 -march=i586"
        CACHE STRING "")
    set (CMAKE_CXX_COMPILER "g++-4.4"
        CACHE STRING "")
endif (ROBOARD)

option (ENABLE_ZMQ
    "Compile and use ZMQ?" ON)

option (RHOBANMATH "RhobanMath support" OFF)

cmake_minimum_required (VERSION 2.6)
project (RhobanUtilsTest)

add_subdirectory (.. utils)
include_directories (.. ${YAML_HEADERS})
set (EXTRA_LIBS RhobanUtils)

set (ROBOARD_IP "192.168.16.51"
        CACHE STRING "IP of the destination Roboard")

# Test logging
add_executable (Tests main.cpp)
target_link_libraries (Tests ${EXTRA_LIBS})

# Copy the config.yml to the binary dir
execute_process (COMMAND cp "${PROJECT_SOURCE_DIR}/config.yml" ${PROJECT_BINARY_DIR})

add_custom_target (send 
    ${PROJECT_SOURCE_DIR}/send.sh ${ROBOARD_IP})

add_executable(TestSerial serial.cpp)
target_link_libraries (TestSerial ${EXTRA_LIBS})

add_executable(TestHTTP http.cpp)
target_link_libraries (TestHTTP ${EXTRA_LIBS})
