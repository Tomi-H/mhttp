#ifndef _LOG_H_
#define _LOG_H_

#include "log_internal.h"

struct _log {
    int fd;
    char * filename;
    log_internal * internal;

    int  (*open)  (const char * filename, int flags);
    void  (*close) ();

    void (*error) (const char * format, ...);
    void (*info)  (const char * format, ...);
    void (*debug) (const char * format, ...);
};
typedef struct _log logtool;

logtool * get_log();

#endif /* _LOG_H_ */
