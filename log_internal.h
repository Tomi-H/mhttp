#ifndef _LOG_INTERNAL_H_
#define _LOG_INTERNAL_H_
#include "log_internal.h"
struct _log_internal {
    int  (*open)  (const char * filename, int flags);
    void  (*close) (int fd);
    void (*error) (int fd, const char * format, ...);
    void (*info)  (int fd, const char * format, ...);
    void (*debug) (int fd, const char * format, ...);
};

typedef struct _log_internal log_internal;

log_internal * get_default_internal();
void free_default_log();

#endif /* _LOG_INTERNAL_H_ */
