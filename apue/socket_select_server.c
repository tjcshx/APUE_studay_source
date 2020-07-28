/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  socket_select_sever.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/06/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/06/2020 03:22:11 PM"
 *                 
 ********************************************************************************/
#ifndef __SOCKET_SELECT_SERVER_H__
#define __SOCKET_SELECT_SERVER_H__ 
#include "socket_select_server.h"

#endif 
int main(int argc, char *argv[])
{
    int       listenfd, connfd;
    int       ser_port;
    char      *progname = NULL;
    int       opt;
    fd_set    rdset;
    int       rv;
    int       i, j;
    int       found;
    int       maxfd = 0;
    char      buf[BUF_SIZE];
    int       fds_array[1024];



    get_opt(argc, argv,"p:dm:h");
    return 0;
}

int get_opt(int argc, char * const argv[],const char *optstring)
{
    int     port = 0;
    int     ch;
    char    *msg = NULL;

    struct option        opts[] = {
        {"port", required_argument, NULL, 'p'},
        {"write_msg", required_argument, NULL, 'm'},
        {"daemon", no_argument, NULL, 'd'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}

    };

    while((ch=getopt_long(argc, argv, "p:m:dh", opts, NULL)) != -1 )
    {
        switch(ch)
        {
            case 'p':
                port=atoi(optarg);
                break;
            case 'm':
                msg = optarg;
                break;
            case 'd':
                daemon(0,0);
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
        }
    }

    if( !port||!msg)
    {
        print_usage(argv[0]);

        return 0;
    }

    socket_server_init(port, msg);
}
int socket_server_init(int listen_port, char *msg)
{
    int                   lisfd = 0;
    int                   clifd = 0;
    int                   on = 1;
    int                   rv = 0;
    pid_t                 pid;
    char                  buf[BUF_SIZE];
    struct sockaddr_in    serv_addr, cli_addr;
    socklen_t             len = sizeof(serv_addr);

    if ((lisfd = socket(AF_INET,SOCK_STREAM, 0))< 0)
    {
        printf("Socket error:%s\n", strerror(errno));
        return -1;
    }

    printf("socket[%d] successfuly!\n", lisfd);

    setsockopt(lisfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(listen_port);

    if ((rv = bind(lisfd, (struct sockaddr *)&serv_addr, len)) < 0)
    {
        printf("Bind error %s\n", strerror(errno));
        goto EXIT;
    }

    puts("ok");
    if ((rv = listen(lisfd, 13)) < 0)
    {
        printf("Listen error:%s\n", strerror(errno));
        goto EXIT;
    }

    select_start(lisfd, msg);
    return clifd;
EXIT:
    close(lisfd );
    close(clifd );
    return -1;
}


void select_start(int   listenfd, char *msg)
{
    int       maxfd = 0;
    char      buf[BUF_SIZE];
    int       fds_array[1024];
    int       i, j;
    int       rv ;
    int       found;
    int       connfd;
    fd_set    rdset;


    for (i = 0; i < ARRAY_SIZE(fds_array); ++i) 
    {
        fds_array[i] = -1;
    }
    fds_array[0] = listenfd;
    printf("fds_array[0] = %d\n", fds_array[0]);

    for ( ; ; )
    {
        FD_ZERO(&rdset);
        for ( i = 0; i<ARRAY_SIZE(fds_array); i++)
        {
            if (fds_array[i] < 0)
            {
                continue;
            }

            maxfd = fds_array[i] > maxfd ?fds_array[i]:maxfd;
            FD_SET(fds_array[i], &rdset);
        }


        rv = select(maxfd + 1, &rdset, NULL, NULL, NULL);
        if (rv < 0)
        {
            printf("Select error:%s\n", strerror(errno));

            break;
        }
        else if (rv == 0)
        {
            printf("select get timeout.\n");
            continue;
        }

        if (FD_ISSET(listenfd, &rdset))
        {
            if ( ( connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0)
            {
                printf("Accept new client error: %s\n", strerror(errno));
                continue;
            }

            found = 0;

            for (i = 0; i <ARRAY_SIZE(fds_array); i++)
            {
                if (fds_array[i] < 0)
                {
                    printf("Accept new client[%d] and it into ayyar.\n", connfd);
                    fds_array[i] = connfd;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("Accept new client[%d] sueecssful but array is full, so refuse it.\n", connfd);
                close(connfd);
            }

        }
        else 
        {
            for (i = 0; i<ARRAY_SIZE(fds_array); i++)
            {
                if (fds_array[i] < 0 || !FD_ISSET(fds_array[i], &rdset))
                    continue;
                if ((rv = read(fds_array[i], buf, BUF_SIZE)) <= 0)
                {
                    printf("Socket[%d] read failure or get disconnected.\n", fds_array[i]);
                    close(fds_array[i]);
                    fds_array[i] = -1;
                }
                else 
                {
                    printf("socket[%d] read get %d bytes data\n", fds_array[i], rv);
                    dump_buf(buf,rv);

                    if (write(fds_array[i], msg, rv) < 0)
                    {
                        printf("socket[%d] write failure: %s\n", fds_array[i], strerror(errno));
                        close(fds_array[i]);
                        fds_array[i] = -1;
                    }
                }
            }
        }

    }

}
void dump_buf(char *data, int bytes)
{
    int  i = 0;
    for (i = 0; i< bytes; i++)
    {
        printf("0x%02x ", (unsigned char)data[i]);
    }
    puts(" ");
}
