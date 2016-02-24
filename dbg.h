// Zed Shaw's Debug macros. Pretty fancy, that.
// Comments by Ben Davenport-Ray.
#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>


// If debugging is enabled, print something to STDERR.
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

// Say something if errno is flagged. 
#define clean_errno() (errno == 0 ? "None" : strerror(errno))

// Send an error to STDERR.
#define log_err(M, ...) fprintf(stderr, "error ( %s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
// Send a warning to STDERR.
#define log_warn(M, ...) fprintf(stderr, "warning ( %s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)
// Send information to STDERR.
#define log_info(M, ...) fprintf(stderr, "info ( %s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// Check if the expression A is true. If not, say something and go to the error label.
#define check(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

// Place the sentinel somewhere that the program should not go.
#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

// Check if memory allocation was good.
#define check_mem(A) check((A), "Out of memory.")

// Check if something messed up, if so, use the debugging facility to tell the user.
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
