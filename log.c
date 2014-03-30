#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>

#include "log.h"
#include "log_internal.h"

static logtool * log = NULL;
unsigned int log_ref_cnt = 0;

static int log_open(const char * filename, int flags)
{
    log->filename = strdup(filename);
    log->fd = log->internal->open(filename, flags);

    return log->fd;
}

void log_close()
{
    if (--log_ref_cnt <= 0) {
        free_default_log();
        if (log) {
            if (log->filename)
                free(log->filename);
            free(log);
        }
    }
}

void log_error(const char * fmt, ...)
{
    log->internal->error(log->fd, fmt);
}

void log_info(const char * fmt, ...)
{
    log->internal->info(log->fd, fmt);
}

void log_debug(const char * fmt, ...)
{
    log->internal->debug(log->fd, fmt);
}

logtool * get_log()
{
    if (log == NULL) {
        log = (logtool *)malloc(sizeof(logtool));
        log->fd = -1;
        log->internal = get_default_internal();
        log->error = log_error;
        log->info = log_info;
        log->debug = log_debug;
        log->open = log_open;
        log->close = log_close;
    }
    log_ref_cnt++;

    return log;
}

