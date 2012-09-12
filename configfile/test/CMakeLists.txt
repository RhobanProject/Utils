cmake_minimum_required (VERSION 2.6)
project (ConfigTest)

# Rhoban utils
set (RHOBAN_UTILS_DIRECTORY
    "${PROJECT_SOURCE_DIR}/../../" CACHE STRING "")

add_subdirectory ("${RHOBAN_UTILS_DIR}" utils)
set (EXTRA_LIBS RhobanUtils)
include_directories ("${RHOBAN_UTILS_DIR}")

# Config file
include ("${RHOBAN_UTILS_DIR}/configfile/ConfigFile.cmake")
config_file (config/ConfigFile
    "something/Something.h"
    )

# Sources
set (ALL_SOURCES ${ALL_SOURCES}
    something/Something.cpp
    main.cpp
    )

include_directories ("${PROJECT_SOURCE_DIR}")

add_executable (ConfigTest ${ALL_SOURCES})
target_link_libraries (ConfigTest ${EXTRA_LIBS})
