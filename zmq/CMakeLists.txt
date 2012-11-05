cmake_minimum_required (VERSION 2.6)
project (ZeroMQ)

IF(DEFINED WIN32)
	SET(SYSTEM_OS "WINDOWS")
	SET(ZMQ_HAVE_WINDOWS 1)
	SET(ZMQ_HAVE_MINGW32 1)
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

add_library (ZeroMQ ${ALL_SOURCES})
