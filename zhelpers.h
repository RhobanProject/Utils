#ifndef __ZHELPERS_H_INCLUDED__
#define __ZHELPERS_H_INCLUDED__

// Include a bunch of headers that we will need in the examples

#ifndef WIN32
#include <zmq.h>
#else
#include <zmq\include\zmq.h>
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#ifndef WIN32
#include <sys/time.h>
#include <unistd.h>
#endif
#include <time.h>
#include <assert.h>
#include <signal.h>

#include <timing/chrono.h>


// Version checking, and patch up missing constants to match 2.1
#if ZMQ_VERSION_MAJOR == 2
# error "Please upgrade to ZeroMQ/3.2 for these examples"
#endif

// Provide random number from 0..(num-1)
#ifdef WIN32
# define randof(num) (int) ((float) (num) * rand () / (RAND_MAX + 1.0))
#else
# define randof(num) (int) ((float) (num) * random () / (RAND_MAX + 1.0))
#endif

#ifdef __GNUC__
#define HIDE_UNUSED __attribute__((unused))
#else
#define HIDE_UNUSED
#endif

// Receive 0MQ string from socket and convert into C string
// Caller must free returned string. Returns NULL if the context
// is being terminated.
HIDE_UNUSED
static char *
s_recv_options (void *socket, int flags, char *more) {
    zmq_msg_t message;
    zmq_msg_init (&message);
    int size = zmq_msg_recv (&message, socket, flags);
    if (size == -1)
        return NULL;
    char *string = (char *)malloc (size + 1);
    memcpy (string, zmq_msg_data (&message), size);
    if (more != NULL) {
        int64_t multi;
        size_t more_size = sizeof (multi);
        zmq_getsockopt (socket, ZMQ_RCVMORE, &multi, &more_size);
        *more = multi;
    }
    zmq_msg_close (&message);
    string [size] = 0;
    return (string);
}

HIDE_UNUSED
static char *
s_recv (void *socket) {
    return s_recv_options(socket, 0, NULL);
}

// Convert C string to 0MQ string and send to socket
HIDE_UNUSED
static int
s_send (void *socket, const char *string)
{
    zmq_msg_t message;
    zmq_msg_init_size (&message, strlen (string));
    memcpy (zmq_msg_data (&message), string, strlen (string));
    int size = zmq_msg_send (&message, socket, 0);
    zmq_msg_close (&message);
    return (size);
}

// Sends string as 0MQ string, as multipart non-terminal
HIDE_UNUSED
static int
s_sendmore (void *socket, const char *string) {
    zmq_msg_t message;
    zmq_msg_init_size (&message, strlen (string));
    memcpy (zmq_msg_data (&message), string, strlen (string));
    int size = zmq_msg_send (&message, socket, ZMQ_SNDMORE);
    zmq_msg_close (&message);
    return (size);
}

// Receives all message parts from socket, prints neatly
//
HIDE_UNUSED
static void
s_dump (void *socket)
{
    puts ("----------------------------------------");
    while (1) {
        // Process all parts of the message
        zmq_msg_t message;
        zmq_msg_init (&message);
        int size = zmq_msg_recv (&message, socket, 0);

        // Dump the message as text or binary
        char *data = (char *)zmq_msg_data (&message);
        int is_text = 1;
        int char_nbr;
        for (char_nbr = 0; char_nbr < size; char_nbr++)
            if ((unsigned char) data [char_nbr] < 32
            || (unsigned char) data [char_nbr] > 127)
                is_text = 0;

        printf ("[%03d] ", size);
        for (char_nbr = 0; char_nbr < size; char_nbr++) {
            if (is_text)
                printf ("%c", data [char_nbr]);
            else
                printf ("%02X", (unsigned char) data [char_nbr]);
        }
        printf ("\n");

        int64_t more; // Multipart detection
        size_t more_size = sizeof (more);
        zmq_getsockopt (socket, ZMQ_RCVMORE, &more, &more_size);
        zmq_msg_close (&message);
        if (!more)
            break; // Last message part
    }
}

// Set simple random printable identity on socket
//
HIDE_UNUSED
static void
s_set_id (void *socket)
{
    char identity [10];
    sprintf (identity, "%04X-%04X", randof (0x10000), randof (0x10000));
    zmq_setsockopt (socket, ZMQ_IDENTITY, identity, strlen (identity));
}


// Sleep for a number of milliseconds
HIDE_UNUSED
static void
s_sleep (int msecs)
{
#ifdef WIN32
    Sleep (msecs);
#else
    struct timespec t;
    t.tv_sec = msecs / 1000;
    t.tv_nsec = (msecs % 1000) * 1000000;
    nanosleep (&t, NULL);
#endif
}

// Return current system clock as milliseconds
HIDE_UNUSED
static int64_t
s_clock (void)
{
#ifdef WIN32
    SYSTEMTIME st;
    GetSystemTime (&st);
    return (int64_t) st.wSecond * 1000 + st.wMilliseconds;
#else
    struct timeval tv;
    gettimeofday ( (chrono *) &tv, NULL);
    return (int64_t) (tv.tv_sec * 1000 + tv.tv_usec / 1000);
#endif
}

// Print formatted string to stdout, prefixed by date/time and
// terminated with a newline.

HIDE_UNUSED
static void
s_console (const char *format, ...)
{
    time_t curtime = time (NULL);
    struct tm *loctime = localtime (&curtime);
    char *formatted = (char *)malloc (20);
    strftime (formatted, 20, "%y-%m-%d %H:%M:%S ", loctime);
    printf ("%s", formatted);
    free (formatted);

    va_list argptr;
    va_start (argptr, format);
    vprintf (format, argptr);
    va_end (argptr);
    printf ("\n");
}

#endif // __ZHELPERS_H_INCLUDED__
