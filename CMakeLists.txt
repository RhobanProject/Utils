cmake_minimum_required (VERSION 2.6)
project (RhobanUtils)
find_package (Threads)

option(MSVC "MSVC: Build for Microsoft Visual Studio" OFF)

if (MSVC)
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
set(CMAKE_CXX_FLAGS 
    "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -fPIC")

endif (MSVC)


option (HAVE_COLORS 
    "Have terminal colors" ON)

if (HAVE_COLORS)
    add_definitions (-DHAVE_COLORS)
endif (HAVE_COLORS)

option(ENABLE_JSON "Compile and enable JSON" ON)
if(ENABLE_JSON)
    add_definitions (-DUSE_JSON)
endif()

option (UTILS_USES_ZMQ
    "Utils includes ZMQ?" ON)

option (UTILS_USES_XML
    "Utils includes XML features" ON)

option (USE_SYSTEM_TINYXML
    "Utils uses the system version of tinyXML" ON)

option (COMPILE_UTILS_TESTS
    "Compile utils tests?" OFF)

option (UTILS_USES_YAML
    "Utils includes YAML" ON)

option (ENABLE_JSON
    "Enable the JSON support" ON)

if(MSVC)
option (ENABLE_XML
    "Enable the XML support" ON)
endif(MSVC)

option (UTILS_USES_CONFIG
    "Utils uses Compile and use args and config" ON)

option (UTILS_USES_SOCKETS
    "UTils includes sockets and http" ON)

# Disabling it by default to avoid screwing all the users
option (UTILS_USES_VIEWER
    "Utils includes viewer (based on SFML)" OFF)

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

if (UTILS_USES_VIEWER)
    set(EXTRA_LIBS ${EXTRA_LIBS} 
        sfml-graphics
        sfml-window
        sfml-system
        GL
        GLU
    )
endif (UTILS_USES_VIEWER)

# Adding sockets for Win32
if (WIN32)
    set (EXTRA_LIBS ${EXTRA_LIBS} ws2_32)
endif (WIN32)

if (UTILS_USES_YAML)
    message("-- Adding YAML support")
    option(YAML_CPP_BUILD_TOOLS "Enable testing and parse tools" OFF)
    add_subdirectory ("${PROJECT_SOURCE_DIR}/yaml-cpp")
    set (YAML_HEADERS "${PROJECT_SOURCE_DIR}/yaml-cpp/include"
        CACHE STRING "")
    include_directories ("${YAML_HEADERS}")
    set (EXTRA_LIBS ${EXTRA_LIBS} yaml-cpp)
endif ()

if (DEFINED ENABLE_XML)
    message("-- Adding XML support")
    add_subdirectory ("${PROJECT_SOURCE_DIR}/xml/TinyXml")
    include_directories ("${PROJECT_SOURCE_DIR}/xml/TinyXml")
    set (EXTRA_LIBS ${EXTRA_LIBS} TinyXml)
endif ()

message("-- Adding Eigen support")
set (EIGEN_HEADERS "${PROJECT_SOURCE_DIR}/eigen-3.2" CACHE STRING "")
include_directories ("${EIGEN_HEADERS}")

if(ENABLE_JSON)
	message("-- Adding JSON support")
	add_subdirectory ("${PROJECT_SOURCE_DIR}/jsoncpp")
	set (JSON_HEADERS "${PROJECT_SOURCE_DIR}/jsoncpp/include"
	    CACHE STRING "")
	include_directories ("${JSON_HEADERS}")
	set (EXTRA_LIBS ${EXTRA_LIBS} json)
endif()

# Sources
set(DIRECTORIES
    .
    logging
    observer
    serial
    tests
	scoring
    threading
    timing
    spline
    )

if(ENABLE_JSON)
 set(DIRECTORIES ${DIRECTORIES} configfile json)
endif()
if(UTILS_USES_XML)
 set(DIRECTORIES ${DIRECTORIES} xml)
endif()
if(UTILS_USES_SOCKETS)
 set(DIRECTORIES ${DIRECTORIES} sockets http)
endif()
if(UTILS_USES_CONFIG)
 set(DIRECTORIES ${DIRECTORIES}  args configfile)
endif()
if(UTILS_USES_VIEWER)
 set(DIRECTORIES ${DIRECTORIES}  viewer)
endif()


if (COMPILE_UTILS_TESTS)
  include_directories ("test")
endif (COMPILE_UTILS_TESTS)

if (UTILS_USES_ZMQ)
	message("-- Adding ZMQ support")

	set(DIRECTORIES ${DIRECTORIES} zmq)

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
	endif()

	set(DIRECTORIES ${DIRECTORIES} zmq)
    include_directories ("${ZMQ_HEADERS}")
    set (EXTRA_LIBS ${EXTRA_LIBS} ZeroMQ)

    if(UNIX AND NOT APPLE)
        set (EXTRA_LIBS ${EXTRA_LIBS} rt)
    endif(UNIX AND NOT APPLE)
endif (UTILS_USES_ZMQ)

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
  add_executable (timeStampTest test/TimeStampTest.cpp timing/TimeStamp.cpp tests/TestCase.cpp )
  add_executable (splineTest test/SplineTest.cpp)
  target_link_libraries (splineTest RhobanUtils)
  # viewerTest
  add_executable (viewerTest test/ViewerTest.cpp)
  target_link_libraries (viewerTest RhobanUtils)
  # benchmarkTest
  add_executable (benchmarkTest test/BenchmarkTest.cpp)
  target_link_libraries (benchmarkTest RhobanUtils)
endif (COMPILE_UTILS_TESTS)

if(NOT MSVC)
  if (USE_SYSTEM_TINYXML)
    set (EXTRA_LIBS ${EXTRA_LIBS} tinyxml ${CMAKE_THREAD_LIBS_INIT})
  else()
    add_subdirectory (xml/TinyXml)
    include_directories ("${PROJECT_SOURCE_DIR}/xml/TinyXml")
    set (EXTRA_LIBS ${EXTRA_LIBS} TinyXml ${CMAKE_THREAD_LIBS_INIT})
  endif()
endif()

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
