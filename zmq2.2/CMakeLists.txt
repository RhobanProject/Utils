cmake_minimum_required (VERSION 2.6)
project (ZeroMQ)

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

set (
ALL_SOURCES
src/clock.cpp
src/command.cpp
src/connect_session.cpp
src/ctx.cpp
src/decoder.cpp
src/device.cpp
src/devpoll.cpp
src/dist.cpp
src/encoder.cpp
src/epoll.cpp
src/err.cpp
src/fq.cpp
src/io_object.cpp
src/io_thread.cpp
src/ip.cpp
src/kqueue.cpp
src/lb.cpp
src/mailbox.cpp
src/named_session.cpp
src/object.cpp
src/options.cpp
src/own.cpp
src/pair.cpp
src/pgm_receiver.cpp
src/pgm_sender.cpp
src/pgm_socket.cpp
src/pipe.cpp
src/poll.cpp
src/poller_base.cpp
src/pub.cpp
src/pull.cpp
src/push.cpp
src/reaper.cpp
src/rep.cpp
src/req.cpp
src/select.cpp
src/session.cpp
src/signaler.cpp
src/socket_base.cpp
src/sub.cpp
src/swap.cpp
src/tcp_connecter.cpp
src/tcp_listener.cpp
src/tcp_socket.cpp
src/thread.cpp
src/transient_session.cpp
src/trie.cpp
src/uuid.cpp
src/xpub.cpp
src/xrep.cpp
src/xreq.cpp
src/xsub.cpp
src/zmq.cpp
src/zmq_connecter.cpp
src/zmq_engine.cpp
src/zmq_init.cpp
src/zmq_listener.cpp
    )

set (ZMQ_HEADERS "${PROJECT_SOURCE_DIR}/include/"
    CACHE STRING "")

add_library (ZeroMQ ${ALL_SOURCES})

if (DEFINED WIN32)
	target_link_libraries (ZeroMQ wsock32 ws2_32)
endif (DEFINED WIN32)