cmake_minimum_required (VERSION 2.6)
project (ZeroMQ)

option (32BIT
    "Compile for a 32bit target" ON)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "")
endif ()
if (32BIT)
    set (CMAKE_SYSTEM_PROCESSOR "i386" CACHE STRING "arch")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32" CACHE STRING "c++ flags")
    set (CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} -m32" CACHE STRING "c flags")
endif ()

IF(DEFINED WIN32)
	SET(SYSTEM_OS "WINDOWS")
	SET(ZMQ_HAVE_WINDOWS 1)
	SET(ZMQ_HAVE_MINGW32 1)
        add_definitions(-DZMQ_HAVE_WINDOWS=1)
        add_definitions(-DZMQ_HAVE_MINGW32=1)
ELSE(DEFINED WIN32)
        add_definitions(-DZMQ_HAVE_LINUX=1)
        add_definitions(-DZMQ_HAVE_UIO=1)
ENDIF(DEFINED WIN32)

set (ALL_SOURCES
    src/address.cpp  src/err.cpp            src/lb.cpp            src/pgm_sender.cpp   src/push.cpp          src/socket_base.cpp    src/v1_decoder.cpp
    src/clock.cpp    src/fq.cpp             src/mailbox.cpp       src/pgm_socket.cpp   src/random.cpp        src/stream_engine.cpp  src/v1_encoder.cpp
    src/ctx.cpp      src/io_object.cpp      src/msg.cpp           src/pipe.cpp         src/reaper.cpp        src/sub.cpp            src/xpub.cpp
    src/dealer.cpp   src/io_thread.cpp      src/mtrie.cpp         src/poll.cpp         src/rep.cpp           src/tcp_address.cpp    src/xsub.cpp
    src/decoder.cpp  src/ipc_address.cpp    src/object.cpp        src/poller_base.cpp  src/req.cpp           src/tcp_connecter.cpp  src/zmq.cpp
    src/devpoll.cpp  src/ipc_connecter.cpp  src/options.cpp       src/precompiled.cpp  src/router.cpp        src/tcp.cpp            src/zmq_utils.cpp
    src/dist.cpp     src/ipc_listener.cpp   src/own.cpp           src/proxy.cpp        src/select.cpp        src/tcp_listener.cpp
    src/encoder.cpp  src/ip.cpp             src/pair.cpp          src/pub.cpp          src/session_base.cpp  src/thread.cpp
    src/epoll.cpp    src/kqueue.cpp         src/pgm_receiver.cpp  src/pull.cpp         src/signaler.cpp      src/trie.cpp
    )




set (ZMQ_HEADERS "${PROJECT_SOURCE_DIR}/include/"
    CACHE STRING "")


# ADD HEADERS FILES
foreach (SOURCE ${ALL_SOURCES})
	set (FILENAME_PREFIX)
	set (FILENAME_PATH)
	GET_FILENAME_COMPONENT(FILENAME_PREFIX ${SOURCE} NAME_WE)
	GET_FILENAME_COMPONENT(FILENAME_PATH ${SOURCE} PATH)

	if (FILENAME_PATH STREQUAL "")
		set (FILENAME ${FILENAME_PREFIX})
	else ()
		set (FILENAME ${FILENAME_PATH}/${FILENAME_PREFIX})
	endif()

	if(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.h")
        set (ALL_HEADERS ${ALL_HEADERS} "${FILENAME}.h")
	endif(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.h")
	if(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.hpp")
        set (ALL_HEADERS ${ALL_HEADERS} "${FILENAME}.hpp")
	endif(EXISTS "${PROJECT_SOURCE_DIR}/${FILENAME}.hpp")
endforeach (SOURCE)

add_library (ZeroMQ ${ALL_SOURCES})

if(MSVC)
	if(NOT BUILD_SHARED_LIBS)
		# correct library names
		set_target_properties(ZeroMQ PROPERTIES
			DEBUG_POSTFIX "${LIB_TARGET_SUFFIX}d"
			RELEASE_POSTFIX "${LIB_TARGET_SUFFIX}"
			MINSIZEREL_POSTFIX "${LIB_TARGET_SUFFIX}"
			RELWITHDEBINFO_POSTFIX "${LIB_TARGET_SUFFIX}"
		)
	endif()
endif()

if (DEFINED WIN32)
	target_link_libraries (ZeroMQ wsock32 ws2_32)
endif (DEFINED WIN32)
