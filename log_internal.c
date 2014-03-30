#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdarg.h>
#include "log_internal.h"

#define MAX_MESSAGE_LENGTH 1024

static char msg[MAX_MESSAGE_LENGTH] = {0};
log_internal * default_log = NULL;
//int default_log_count = 0;

#define TIME_STRING_LEN 30
static char * current_time()
{
    time_t tt;
    struct tm * t;
    struct timeval tv;
    static char now[TIME_STRING_LEN] = {0};

    time(&tt);
    t = localtime(&tt);
    gettimeofday(&tv, NULL);
    snprintf(now, TIME_STRING_LEN, "%d-%d-%d %d:%d:%d:%ld", t->tm_year + 1970,
             t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec,
             tv.tv_usec/1000);
    return now;
}

void file_error(int fd, const char * format, ...)
{
    va_list ap;

    va_start(ap, format);
    snprintf(msg, MAX_MESSAGE_LENGTH, format, ap);
    va_end(ap);

    write(fd, msg, strlen(msg));
    write(fd, "\n", 1);
}


void file_info(int fd, const char * format, ...)
{
    va_list ap;

    va_start(ap, format);
    snprintf(msg, MAX_MESSAGE_LENGTH, format, ap);
    va_end(ap);
    write(fd, msg, strlen(msg));
    write(fd, "\n", 1);
}


void file_debug(int fd, const char * format, ...)
{
    va_list ap;

    va_start(ap, format);
    snprintf(msg, MAX_MESSAGE_LENGTH, format, ap);
    va_end(ap);
    write(fd, msg, strlen(msg));
    write(fd, "\n", 1);
}


int file_open(const char *filename, int flags)
{
   // log_internal * li = get_default_log();
   return open(filename, flags, S_IRUSR | S_IWUSR
               | S_IRGRP | S_IROTH);
}

void file_close(int fd)
{
    close(fd);
}

log_internal * get_default_internal()
{
    if (default_log == NULL) {
        default_log = (log_internal *)malloc(sizeof(log_internal));
        default_log->error = file_error;
        default_log->info = file_info;
        default_log->debug = file_debug;
        default_log->open = file_open;
        default_log->close = file_close;
    }

    return default_log;
}

void free_default_log()
{
    free(default_log);
}

