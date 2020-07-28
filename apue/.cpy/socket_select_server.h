/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  socket_select_sever.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/06/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/06/2020 03:20:23 PM"
 *                 
 ********************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h> 
#include <ctype.h>
#include <time.h>
#include <pthread.h> 
#include <getopt.h>
#include <libgen.h>
#include <sys/types.h>   
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#define ARRAY_SIZE(x)       (sizeof(x)/sizeof(x[0]))
#define BUF_SIZE            1024

int get_opt(int argc, char * const argv[],const char *optstring);
int socket_server_init(int listen_port, char *msg);
void select_start(int   listenfd, char *msg);
void print_usage(char *prograname)
{
    printf("%s usage : \n", prograname);
    printf("-p(--port): specify sever listen port.\n");
    printf("-m(--msg): specify sever write msg to client.\n");
    printf("-d(--daemon): specify sever will go to run with daemon.\n");
    printf("-h(--help): print this help information.\n");

    return  ;

}

