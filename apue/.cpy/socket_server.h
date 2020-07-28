/********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  socket_server.h
 *    Description:  This head file 
 *
 *        Version:  1.0.0(02/23/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "02/23/2020 08:31:04 AM"
 *                 
 ********************************************************************************/
#ifndef __SOCKET_SERVER_H
#define __SOCKET_SERVER_H 
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include<stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/un.h>

#define BUF_SIZE  1024
int   socket_start(int domain, int type, int protocol,char* path , char* msg);
int   rdwr_init(int clinefd,char *buf, char *msg);
int   get_opt(int argc, char * const argv[],const char *optstring);
#endif 

