# $Id: $
#
# For a "How-To" please refer to the Portaudio documentation at:
# http://www.portaudio.com/trac/wiki/TutorialDir/Compile/CMake
#
PROJECT( portaudio )

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(CMAKE_CL_64)
SET(TARGET_POSTFIX x64)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/x64)
ELSE(CMAKE_CL_64)
SET(TARGET_POSTFIX x86)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin/Win32)
ENDIF(CMAKE_CL_64)

IF(WIN32 AND MSVC)
OPTION(PORTAUDIO_DLL_LINK_WITH_STATIC_RUNTIME "Link with static runtime libraries (minimizes runtime dependencies)" ON)
IF(PORTAUDIO_DLL_LINK_WITH_STATIC_RUNTIME)
  FOREACH(flag_var
		CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
		CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO
		CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    IF(${flag_var} MATCHES "/MD")
      STRING(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    ENDIF(${flag_var} MATCHES "/MD")
  ENDFOREACH(flag_var)
ENDIF(PORTAUDIO_DLL_LINK_WITH_STATIC_RUNTIME)

ENDIF(WIN32 AND MSVC)

IF(WIN32)
OPTION(PORTAUDIO_UNICODE_BUILD "Enable Portaudio Unicode build" ON)

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_support)
# Try to find DirectX SDK
FIND_PACKAGE(DXSDK)
# Try to find ASIO SDK (assumes that portaudio and asiosdk folders are side-by-side, see
# http://www.portaudio.com/trac/wiki/TutorialDir/Compile/WindowsASIOMSVC)
FIND_PACKAGE(ASIOSDK)

IF(ASIOSDK_FOUND)
OPTION(PORTAUDIO_ENABLE_ASIO "Enable support for ASIO" ON)
ELSE(ASIOSDK_FOUND)
OPTION(PORTAUDIO_ENABLE_ASIO "Enable support for ASIO" OFF)
ENDIF(ASIOSDK_FOUND)
IF(DXSDK_FOUND)
OPTION(PORTAUDIO_ENABLE_DSOUND "Enable support for DirectSound" ON)
ELSE(DXSDK_FOUND)
OPTION(PORTAUDIO_ENABLE_DSOUND "Enable support for DirectSound" OFF)
ENDIF(DXSDK_FOUND)
OPTION(PORTAUDIO_ENABLE_WMME "Enable support for MME" ON)
OPTION(PORTAUDIO_ENABLE_WASAPI "Enable support for WASAPI" ON)
OPTION(PORTAUDIO_ENABLE_WDMKS "Enable support for WDMKS" ON)
OPTION(PORTAUDIO_USE_WDMKS_DEVICE_INFO "Use WDM/KS API for device info" ON)
MARK_AS_ADVANCED(PORTAUDIO_USE_WDMKS_DEVICE_INFO)
IF(PORTAUDIO_ENABLE_DSOUND)
OPTION(PORTAUDIO_USE_DIRECTSOUNDFULLDUPLEXCREATE "Use DirectSound full duplex create" ON)
MARK_AS_ADVANCED(PORTAUDIO_USE_DIRECTSOUNDFULLDUPLEXCREATE)
ENDIF(PORTAUDIO_ENABLE_DSOUND)
ENDIF(WIN32)

MACRO(SET_HEADER_OPTION OPTION_NAME OPTION_VALUE)
  IF(${OPTION_NAME})
  SET(${OPTION_VALUE} "1")
  ELSE(${OPTION_NAME})
  SET(${OPTION_VALUE} "0")
  ENDIF(${OPTION_NAME})
ENDMACRO(SET_HEADER_OPTION)

SET_HEADER_OPTION(PORTAUDIO_ENABLE_ASIO   PA_ENABLE_ASIO)
SET_HEADER_OPTION(PORTAUDIO_ENABLE_DSOUND PA_ENABLE_DSOUND)
SET_HEADER_OPTION(PORTAUDIO_ENABLE_WMME   PA_ENABLE_WMME)
SET_HEADER_OPTION(PORTAUDIO_ENABLE_WASAPI PA_ENABLE_WASAPI)
SET_HEADER_OPTION(PORTAUDIO_ENABLE_WDMKS  PA_ENABLE_WDMKS)

# Set variables for DEF file expansion
IF(NOT PORTAUDIO_ENABLE_ASIO)
SET(DEF_EXCLUDE_ASIO_SYMBOLS ";")
ENDIF(NOT PORTAUDIO_ENABLE_ASIO)

IF(NOT PORTAUDIO_ENABLE_WASAPI)
SET(DEF_EXCLUDE_WASAPI_SYMBOLS ";")
ENDIF(NOT PORTAUDIO_ENABLE_WASAPI)

IF(PORTAUDIO_USE_WDMKS_DEVICE_INFO)
ADD_DEFINITIONS(-DPAWIN_USE_WDMKS_DEVICE_INFO)
ENDIF(PORTAUDIO_USE_WDMKS_DEVICE_INFO)

IF(PORTAUDIO_USE_DIRECTSOUNDFULLDUPLEXCREATE)
ADD_DEFINITIONS(-DPAWIN_USE_DIRECTSOUNDFULLDUPLEXCREATE)
ENDIF(PORTAUDIO_USE_DIRECTSOUNDFULLDUPLEXCREATE)

#######################################
IF(WIN32)
INCLUDE_DIRECTORIES(src/os/win)
ENDIF(WIN32)

IF(PORTAUDIO_ENABLE_ASIO)
INCLUDE_DIRECTORIES(${ASIOSDK_ROOT_DIR}/common)
INCLUDE_DIRECTORIES(${ASIOSDK_ROOT_DIR}/host)
INCLUDE_DIRECTORIES(${ASIOSDK_ROOT_DIR}/host/pc)

SET(PA_ASIO_SOURCES 
  src/hostapi/asio/pa_asio.cpp
)  

SET(PA_ASIOSDK_SOURCES
  ${ASIOSDK_ROOT_DIR}/common/asio.cpp
  ${ASIOSDK_ROOT_DIR}/host/pc/asiolist.cpp
  ${ASIOSDK_ROOT_DIR}/host/asiodrivers.cpp
)

SOURCE_GROUP("hostapi\\ASIO" FILES
  ${PA_ASIO_SOURCES}
)

SOURCE_GROUP("hostapi\\ASIO\\ASIOSDK" FILES
  ${PA_ASIOSDK_SOURCES}
)
ENDIF(PORTAUDIO_ENABLE_ASIO)

IF(PORTAUDIO_ENABLE_DSOUND)
INCLUDE_DIRECTORIES(${DXSDK_INCLUDE_DIR})
INCLUDE_DIRECTORIES(src/os/win)

SET(PA_DS_INCLUDES
  src/hostapi/dsound/pa_win_ds_dynlink.h
)

SET(PA_DS_SOURCES
  src/hostapi/dsound/pa_win_ds.c
  src/hostapi/dsound/pa_win_ds_dynlink.c
)

SOURCE_GROUP("hostapi\\dsound" FILES
  ${PA_DS_INCLUDES}
  ${PA_DS_SOURCES}
)
ENDIF(PORTAUDIO_ENABLE_DSOUND)

IF(PORTAUDIO_ENABLE_WMME)
SET(PA_WMME_SOURCES
  src/hostapi/wmme/pa_win_wmme.c
)

SOURCE_GROUP("hostapi\\wmme" FILES
  ${PA_WMME_SOURCES}
)
ENDIF(PORTAUDIO_ENABLE_WMME)

IF(PORTAUDIO_ENABLE_WASAPI)
SET(PA_WASAPI_SOURCES
  src/hostapi/wasapi/pa_win_wasapi.c
)

SOURCE_GROUP("hostapi\\wasapi" FILES
  ${PA_WASAPI_SOURCES}
)
ENDIF(PORTAUDIO_ENABLE_WASAPI)

IF(PORTAUDIO_ENABLE_WDMKS)
SET(PA_WDMKS_SOURCES
  src/hostapi/wdmks/pa_win_wdmks.c
)

SOURCE_GROUP("hostapi\\wdmks" FILES
  ${PA_WDMKS_SOURCES}
)
ENDIF(PORTAUDIO_ENABLE_WDMKS)

SET(PA_SKELETON_SOURCES
  src/hostapi/skeleton/pa_hostapi_skeleton.c
)

SOURCE_GROUP("hostapi\\skeleton" 
  ${PA_SKELETON_SOURCES})

#######################################
IF(WIN32)
SET(PA_INCLUDES 
  include/portaudio.h
  include/pa_asio.h
  include/pa_win_ds.h
  include/pa_win_wasapi.h
  include/pa_win_wmme.h
)
ENDIF(WIN32)

SOURCE_GROUP("include" FILES
  ${PA_INCLUDES}
)

SET(PA_COMMON_INCLUDES
  src/common/pa_allocation.h
  src/common/pa_converters.h
  src/common/pa_cpuload.h
  src/common/pa_debugprint.h
  src/common/pa_dither.h
  src/common/pa_endianness.h
  src/common/pa_hostapi.h
  src/common/pa_memorybarrier.h
  src/common/pa_process.h
  src/common/pa_ringbuffer.h
  src/common/pa_stream.h
  src/common/pa_trace.h
  src/common/pa_types.h
  src/common/pa_util.h
)

SET(PA_COMMON_SOURCES
  src/common/pa_allocation.c
  src/common/pa_converters.c
  src/common/pa_cpuload.c
  src/common/pa_debugprint.c
  src/common/pa_dither.c
  src/common/pa_front.c
  src/common/pa_process.c
  src/common/pa_ringbuffer.c
  src/common/pa_stream.c
  src/common/pa_trace.c
)

SOURCE_GROUP("common" FILES
  ${PA_COMMON_INCLUDES}
  ${PA_COMMON_SOURCES}
)

SOURCE_GROUP("cmake_generated" FILES
  ${CMAKE_CURRENT_BINARY_DIR}/portaudio_cmake.def
  ${CMAKE_CURRENT_BINARY_DIR}/options_cmake.h
)

IF(WIN32)
SET(PA_PLATFORM_SOURCES 
  src/os/win/pa_win_hostapis.c
  src/os/win/pa_win_util.c
  src/os/win/pa_win_waveformat.c
  src/os/win/pa_win_wdmks_utils.c
  src/os/win/pa_win_coinitialize.c
  src/os/win/pa_x86_plain_converters.c
)

SOURCE_GROUP("os\\win" FILES
  ${PA_PLATFORM_SOURCES}
)
ENDIF(WIN32)

INCLUDE_DIRECTORIES( include )
INCLUDE_DIRECTORIES( src/common )
INCLUDE_DIRECTORIES( src/hostapi/wasapi/mingw-include )

IF(WIN32 AND MSVC)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32 AND MSVC)

ADD_DEFINITIONS(-DPORTAUDIO_CMAKE_GENERATED)
INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_BINARY_DIR} )

SET(SOURCES_LESS_ASIO_SDK
  ${PA_COMMON_SOURCES}
  ${PA_ASIO_SOURCES}
  ${PA_DS_SOURCES}
  ${PA_WMME_SOURCES}
  ${PA_WASAPI_SOURCES}
  ${PA_WDMKS_SOURCES}
  ${PA_SKELETON_SOURCES}
  ${PA_PLATFORM_SOURCES}
)

IF(PORTAUDIO_UNICODE_BUILD)
SET_SOURCE_FILES_PROPERTIES(
  ${SOURCES_LESS_ASIO_SDK}
  PROPERTIES
  COMPILE_DEFINITIONS "UNICODE;_UNICODE"
)
ENDIF(PORTAUDIO_UNICODE_BUILD)

ADD_LIBRARY(portaudio SHARED
  ${PA_INCLUDES}
  ${PA_COMMON_INCLUDES}
  ${SOURCES_LESS_ASIO_SDK}
  ${PA_ASIOSDK_SOURCES}
  ${CMAKE_CURRENT_BINARY_DIR}/portaudio_cmake.def
  ${CMAKE_CURRENT_BINARY_DIR}/options_cmake.h
)

ADD_LIBRARY(portaudio_static STATIC
  ${PA_INCLUDES}
  ${PA_COMMON_INCLUDES}
  ${SOURCES_LESS_ASIO_SDK}
  ${PA_ASIOSDK_SOURCES}
  ${CMAKE_CURRENT_BINARY_DIR}/options_cmake.h
)

# Configure the exports file according to settings
SET(GENERATED_MESSAGE "CMake generated file, do NOT edit! Use CMake-GUI to change configuration instead.")
CONFIGURE_FILE( cmake_support/template_portaudio.def ${CMAKE_CURRENT_BINARY_DIR}/portaudio_cmake.def @ONLY )
# Configure header for options (PA_USE_xxx)
CONFIGURE_FILE( cmake_support/options_cmake.h.in ${CMAKE_CURRENT_BINARY_DIR}/options_cmake.h @ONLY )

IF(WIN32)
# If we use DirectSound, we need this for the library to be found (if not in VS project settings)
IF(PORTAUDIO_ENABLE_DSOUND AND DXSDK_FOUND)
TARGET_LINK_LIBRARIES(portaudio ${DXSDK_DSOUND_LIBRARY})
ENDIF(PORTAUDIO_ENABLE_DSOUND AND DXSDK_FOUND)

# If we use WDM/KS we need setupapi.lib
IF(PORTAUDIO_ENABLE_WDMKS)
TARGET_LINK_LIBRARIES(portaudio setupapi)
ENDIF(PORTAUDIO_ENABLE_WDMKS)

SET_TARGET_PROPERTIES(portaudio PROPERTIES OUTPUT_NAME portaudio_${TARGET_POSTFIX})
SET_TARGET_PROPERTIES(portaudio_static PROPERTIES OUTPUT_NAME portaudio_static_${TARGET_POSTFIX})
ENDIF(WIN32)

OPTION(PORTAUDIO_BUILD_TESTS "Include test projects" OFF)
MARK_AS_ADVANCED(PORTAUDIO_BUILD_TESTS)

# Prepared for inclusion of test files
IF(PORTAUDIO_BUILD_TESTS)
SUBDIRS(test)
ENDIF(PORTAUDIO_BUILD_TESTS)

#################################

