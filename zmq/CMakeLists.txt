cmake_minimum_required (VERSION 2.6)
project (ZeroMQ)
option (32BIT "Compilation 32 bit" OFF)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "")
endif ()

IF(32BIT)
	set (CMAKE_CXX_FLAGS "-m32" CACHE STRING "")
ENDIF(32BIT)


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
    src/address.cpp  src/epoll.cpp          src/kqueue.cpp   src/pgm_receiver.cpp  src/push.cpp          src/socket_base.cpp    src/xsub.cpp
    src/clock.cpp    src/err.cpp            src/lb.cpp       src/pgm_sender.cpp    src/random.cpp        src/stream_engine.cpp  src/zmq.cpp
    src/ctx.cpp      src/fq.cpp             src/mailbox.cpp  src/pgm_socket.cpp    src/reaper.cpp        src/sub.cpp            src/zmq_utils.cpp
    src/dealer.cpp   src/io_object.cpp      src/msg.cpp      src/pipe.cpp          src/rep.cpp           src/tcp_address.cpp
    src/decoder.cpp  src/io_thread.cpp      src/mtrie.cpp    src/poll.cpp          src/req.cpp           src/tcp_connecter.cpp
    src/device.cpp   src/ipc_address.cpp    src/object.cpp   src/poller_base.cpp   src/router.cpp        src/tcp_listener.cpp
    src/devpoll.cpp  src/ipc_connecter.cpp  src/options.cpp  src/precompiled.cpp   src/select.cpp        src/thread.cpp
    src/dist.cpp     src/ipc_listener.cpp   src/own.cpp      src/pub.cpp           src/session_base.cpp  src/trie.cpp
    src/encoder.cpp  src/ip.cpp             src/pair.cpp     src/pull.cpp          src/signaler.cpp      src/xpub.cpp
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

option(MSVC "MSVC: Build for Microsoft Visual Studio" OFF)

if (DEFINED WIN32)
	target_link_libraries (ZeroMQ wsock32 ws2_32)
endif (DEFINED WIN32)
