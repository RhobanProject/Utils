cmake_minimum_required (VERSION 2.6)
project (RhobanUtils)
find_package(Threads)

# Options
option(RHOBANMATH
    "Enables RhobanMath support" OFF)

if (NOT RHOBANMATH)
    add_definitions(-DNO_RHOBANMATH)
endif (NOT RHOBANMATH)

if(CMAKE_BUILD_TYPE EQUAL "Release")
    add_definitions(-DNDEBUG)
endif(CMAKE_BUILD_TYPE EQUAL "Release")

# Sources
set(DIRECTORIES
    .
    tests
    timing
    threading
    xml
    sockets
    )

foreach (DIRECTORY ${DIRECTORIES})
    message("* Adding ${DIRECTORY}/")
    include_directories("${CMAKE_SOURCE_DIR}/${DIRECTORY}")
    include (${DIRECTORY}/Sources.cmake)

    set (PREFIXED_SOURCES)
    foreach (SOURCE ${SOURCES})
        set (PREFIXED_SOURCES ${PREFIXED_SOURCES} ${DIRECTORY}/${SOURCE})
    endforeach (SOURCE)

    set (ALL_SOURCES ${ALL_SOURCES} ${PREFIXED_SOURCES})
endforeach (DIRECTORY)

# Adding TinyXml
add_subdirectory (xml/TinyXml)
set (EXTRA_LIBS ${EXTRA_LIBS} TinyXml ${CMAKE_THREAD_LIBS_INIT})

# Adding library and dependecy
add_library (RhobanUtils ${ALL_SOURCES})
target_link_libraries (RhobanUtils ${EXTRA_LIBS})

add_executable (TestLog ${ALL_SOURCES} exes/test_log.cpp)
target_link_libraries (TestLog ${EXTRA_LIBS})
