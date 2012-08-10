cmake_minimum_required (VERSION 2.6)
project (RhobanUtils)
find_package(Threads)

# Options
option(RHOBANMATH
    "Enables RhobanMath support" OFF)

if(NOT RHOBANMATH)
    add_definitions(-DNO_RHOBANMATH)
endif(NOT RHOBANMATH)

if(CMAKE_BUILD_TYPE EQUAL "Release")
    add_definitions(-DNDEBUG)
endif(CMAKE_BUILD_TYPE EQUAL "Release")

# Source files
include_directories ("${PROJECT_SOURCE_DIR}")
set(SOURCES anyoption.cpp chrono.cpp config_file.cpp
    fifo.cpp  file_mngt.cpp  state_machine.cpp
    ticks.cpp  util.cpp)

include_directories ("${PROJECT_SOURCE_DIR}/tests")
set(TESTS_SOURCES tests/TestCase.cpp)

include_directories ("${PROJECT_SOURCE_DIR}/timing")
set(TIMING_SOURCES timing/Playable.cpp  timing/Player.cpp
    timing/TickMachine.cpp  timing/TickTimer.cpp)

include_directories ("${PROJECT_SOURCE_DIR}/threading")
set(THREADING_SOURCES threading/Condition.cpp  threading/Mutex.cpp 
    threading/Thread.cpp  threading/TimedThread.cpp)

include_directories ("${PROJECT_SOURCE_DIR}/xml")
set(XML_SOURCES xml/XMLTools.cpp)

include_directories ("${PROJECT_SOURCE_DIR}/sockets")
set(SOCKETS_SOURCES sockets/TCPClientBase.cpp  sockets/TCPClient.cpp  sockets/TCPServerClient.cpp)

set(ALL_SOURCES ${SOURCES} ${TESTS_SOURCES} ${TIMING_SOURCES}
    ${THREADING_SOURCES} ${XML_SOURCES} ${SOCKETS_SOURCES})

# Adding TinyXml
add_subdirectory(xml/TinyXml)
set(EXTRA_LIBS ${EXTRA_LIBS} TinyXml ${CMAKE_THREAD_LIBS_INIT})

# Adding library and dependecy
add_library(RhobanUtils ${ALL_SOURCES})
target_link_libraries(RhobanUtils ${EXTRA_LIBS})
