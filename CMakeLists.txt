cmake_minimum_required (VERSION 2.6)
project (RhobanUtils)
find_package (Threads)

option (32BIT "Compilation 32 bit" OFF)
IF(32BIT)
	set (CMAKE_CXX_FLAGS "-m32" CACHE STRING "")
ENDIF(32BIT)

option(MSVC "MSVC: Build for Microsoft Visual Studio" OFF)

if (MSVC)
	option(MSVC_SHARED_RT "Used shared runtime libraries" OFF)

	IF(NOT MSVC_SHARED_RT)
	foreach(flag_var
        CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
		if(${flag_var} MATCHES "/MD")
      string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
	endif(${flag_var} MATCHES "/MD")
	endforeach(flag_var)
	ENDIF(NOT MSVC_SHARED_RT)

	add_definitions(-D_USE_MATH_DEFINES)
	add_definitions(-DMSVC)
	add_definitions(-D_WINSOCKAPI_)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)


else (MSVC) 
  IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
     set(CMAKE_CXX_FLAGS " -Wall -g -Wno-overloaded-virtual")
  ELSE (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")  
  ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")


#Check for c++11 support
if (NOT (${CMAKE_SYSTEM_NAME} MATCHES "Darwin"))	
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    execute_process(
        COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if (NOT (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7))
        message(FATAL_ERROR "${PROJECT_NAME} requires g++ 4.7 or greater (C++11 support)")
    endif ()
else ()
    message(FATAL_ERROR "Your C++ compiler is not g++ (unknown support for C++11)")
endif ()
endif ()

endif (MSVC)

#Enable C++11
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11")

option (HAVE_COLORS 
    "Have terminal colors" ON)

if (HAVE_COLORS)
    add_definitions (-DHAVE_COLORS)
endif (HAVE_COLORS)

option (ENABLE_ZMQ
    "Compile and use ZMQ?" OFF)

option (COMPILE_UTILS_TESTS
    "Compile utils tests?" OFF)

option (ENABLE_YAML
    "Enable the YAML support" ON)

IF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   # Mac OS X specific code
   SET(SYSTEM_OS "MACOSX")
   add_definitions(-DMACOSX)
   MESSAGE ("-- Running on Mac OS X platform")
ENDIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    # Linux specific code
   SET(SYSTEM_OS "LINUX")
   add_definitions(-DLINUX)
   MESSAGE ("-- Running on Linux platform")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(DEFINED WIN32)
    # Windows specific code
    SET(SYSTEM_OS "WINDOWS")
    add_definitions(-DWINDOWS)
    MESSAGE ("-- Running on Windows platform")
ENDIF(DEFINED WIN32)

# Options
option (RHOBANMATH
    "Enables RhobanMath support" ON)

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

if (ENABLE_YAML)
    message("-- Adding YAML support")
    option(YAML_CPP_BUILD_TOOLS "Enable testing and parse tools" OFF)
    add_subdirectory ("${PROJECT_SOURCE_DIR}/yaml-cpp")
    set (YAML_HEADERS "${PROJECT_SOURCE_DIR}/yaml-cpp/include"
        CACHE STRING "")
    include_directories ("${YAML_HEADERS}")
    set (EXTRA_LIBS ${EXTRA_LIBS} yaml-cpp)
endif ()

message("-- Adding Eigen support")
set (EIGEN_HEADERS "${PROJECT_SOURCE_DIR}/eigen-3.2" CACHE STRING "")
include_directories ("${EIGEN_HEADERS}")

message("-- Adding JSON support")
add_subdirectory ("${PROJECT_SOURCE_DIR}/jsoncpp")
set (JSON_HEADERS "${PROJECT_SOURCE_DIR}/jsoncpp/include"
    CACHE STRING "")
include_directories ("${JSON_HEADERS}")
set (EXTRA_LIBS ${EXTRA_LIBS} json)

# Sources
set(DIRECTORIES
    .
    args
    configfile
    json
    logging
    observer
    scoring
    serial
    sockets
    http
    tests
    threading
    timing
    xml
    )


if (COMPILE_UTILS_TESTS)
  include_directories ("test")
endif (COMPILE_UTILS_TESTS)

if (ENABLE_ZMQ)
	message("-- Adding ZMQ support")

    add_definitions (-DHAVE_ZMQ)
	set (ZMQ_VERSION "3.0" CACHE STRING  "ZMQ Version")

	if(${ZMQ_VERSION} MATCHES "2.2")
		message("Using ZMQ version 2.2")
		set(ZMQ_HEADERS "${PROJECT_SOURCE_DIR}/zmq2.2/include"
			CACHE STRING "ZMQ headers directory")
		add_subdirectory("${PROJECT_SOURCE_DIR}/zmq2.2")
        elseif(${ZMQ_VERSION} MATCHES "3.2")
		message("Using ZMQ version 3.2")
		set(ZMQ_HEADERS "${PROJECT_SOURCE_DIR}/zmq3.2/include"
			CACHE STRING "ZMQ headers directory")
		add_subdirectory("${PROJECT_SOURCE_DIR}/zmq3.2")
	else()
		message("Using ZMQ version ${ZMQ_VERSION}")
		set(ZMQ_HEADERS "${PROJECT_SOURCE_DIR}/zmq/include"
			CACHE STRING "ZMQ headers directory")
		add_subdirectory("${PROJECT_SOURCE_DIR}/zmq")
		message("Adding graph directory")
		set(DIRECTORIES ${DIRECTORIES} graph)
		set(DIRECTORIES ${DIRECTORIES} zmq)
	endif()


    include_directories ("${ZMQ_HEADERS}")
    set (EXTRA_LIBS ${EXTRA_LIBS} ZeroMQ)

    if(UNIX AND NOT APPLE)
        set (EXTRA_LIBS ${EXTRA_LIBS} rt)
    endif(UNIX AND NOT APPLE)
endif (ENABLE_ZMQ)

set (SOURCES)
set (ALL_SOURCES)
set (PREFIXED_SOURCES)
foreach (DIRECTORY ${DIRECTORIES})
    message("-- Utils: Adding ${DIRECTORY}/")
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/${DIRECTORY}")
    include (${DIRECTORY}/Sources.cmake)

    foreach (SOURCE ${SOURCES})
        set (PREFIXED_SOURCES ${PREFIXED_SOURCES} ${DIRECTORY}/${SOURCE})
    endforeach (SOURCE)

    set (ALL_SOURCES ${ALL_SOURCES} ${PREFIXED_SOURCES})
endforeach (DIRECTORY)


if (COMPILE_UTILS_TESTS)
  add_executable (scoringTest test/ScoringTest.cpp scoring/Score.cpp scoring/Mark.cpp tests/TestCase.cpp logging/term_display.cpp)
endif (COMPILE_UTILS_TESTS)

# Adding TinyXml
add_subdirectory (xml/TinyXml)
set (EXTRA_LIBS ${EXTRA_LIBS} TinyXml ${CMAKE_THREAD_LIBS_INIT})

set (ALL_HEADERS)
# ADD HEADERS FILES 
foreach (SOURCE ${ALL_SOURCES})
	set (FILENAME_PREFIX)
	set (FILENAME_PATH)
	GET_FILENAME_COMPONENT(FILENAME_PREFIX ${SOURCE} NAME_WE)
	GET_FILENAME_COMPONENT(FILENAME_PATH ${SOURCE} PATH)
	
	set (FILENAME ${FILENAME_PATH}/${FILENAME_PREFIX})

	if(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.h")
        set (ALL_HEADERS ${ALL_HEADERS} "${FILENAME}.h")
	endif(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.h")
	if(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.hpp")
        set (ALL_HEADERS ${ALL_HEADERS} "${FILENAME}.hpp")
	endif(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.hpp")
endforeach (SOURCE)

# Adding library and dependecy
if (NOT TARGET RhobanUtils)
	add_library (RhobanUtils ${ALL_SOURCES} ${ALL_HEADERS})
	target_link_libraries (RhobanUtils ${EXTRA_LIBS})
endif()
