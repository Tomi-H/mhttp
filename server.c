/*
 * server.c
 *
 *  Created on: Mar 30, 2014
 *      Author: hemiao
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <string.h>

#include "log.h"
#define MH_MAX_EVENTS 203

int setnonblocking(int fd)
{
    if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0) | O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}

int main(int argc, char ** argv)
{
    struct epoll_event ev, events[MH_MAX_EVENTS];
    struct sockaddr_in clientaddr;
    struct sockaddr_in serveraddr;
    int listen_fd;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    ev.data.fd = listen_fd;
    ev.events = EPOLLIN | EPOLLET | EPOLLOUT;

 //   epoll_ctl(
    setnonblocking(listen_fd);
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5678);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listen_fd, (struct sockaddr *)serveraddr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(listen_fd, 1) == -1) {
        perror("listen");
        exit(1);
    }




    return 0;
}

