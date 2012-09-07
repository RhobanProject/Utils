cmake_minimum_required (VERSION 2.6)
project (RhobanUtils)
find_package (Threads)

# Options
option (RHOBANMATH
    "Enables RhobanMath support" OFF)

set (RHOBAN_UTILS_DIRECTORY "${PROJECT_SOURCE_DIR}")

if (NOT RHOBANMATH)
    add_definitions(-DNO_RHOBANMATH)
endif (NOT RHOBANMATH)

if (RHOBANMATH)
    set(RHOBAN_MATH_DIRECTORY "${BASE}/Math"
        CACHE STRING "RhobanMath directory")

    include_directories ("${RHOBAN_MATH_DIRECTORY}")
    set (EXTRA_LIBS ${EXTRA_LIBS} RhobanMath)
endif (RHOBANMATH)

# Adding sockets for Win32
if (WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} ws2_32)
endif (WIN32)

# Adding YAML support
option(YAML_CPP_BUILD_TOOLS "Enable testing and parse tools" OFF)
add_subdirectory ("${PROJECT_SOURCE_DIR}/yaml-cpp")
set (YAML_HEADERS "${PROJECT_SOURCE_DIR}/yaml-cpp/include"
    CACHE STRING "")
include_directories ("${YAML_HEADERS}")
set (EXTRA_LIBS ${EXTRA_LIBS} yaml-cpp)

# Sources
set(DIRECTORIES
    .
    tests
    timing
    threading
    xml
    serial
    sockets
    )

foreach (DIRECTORY ${DIRECTORIES})
    message("-- Utils: Adding ${DIRECTORY}/")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}")
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
