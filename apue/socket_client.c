/*********************************************************************************
 *      Copyright:  (C) 2019 tianjincheng<473892093@qq.com>
 *                  All rights reserved.
 *
 *       Filename:  socket_client.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(11/26/2019)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "11/26/2019 07:03:35 PM"
 *                 
 ********************************************************************************/
#ifndef __SOCKET_CLIENT__
#define __SOCKET_CLIENT__
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
#define	MSG_STR  "Hello network word! I'm client!"
#define	BUF_SIZE  1024
void print_usage(char *paogname)
{
    printf("%s usage : \n", paogname);
    printf("-i(--ipaddr): sepcify server IP address.\n");
    printf("-p(--port): specify sever port.\n");
    printf("-h(--help): print this help information.\n");

    return  ;

}
int main (int argc, char **argv)
{

    int                      sockfd;
    int                      rv = -1;
    struct sockaddr_in       servaddr;
    char                     *servip = NULL;
    int                      port    = 0;
    char                     buf[BUF_SIZE];
    int                      ch;
    int                      temp;
    struct option        opts[] = {
        {"ipaddr", required_argument, NULL, 'i'},
        {"port", required_argument, NULL, 'p'},            
        {"help", no_argument, NULL, 'h'},          
        {NULL, 0, NULL, 0}

    };

    while((ch=getopt_long(argc, argv, "i:p:h", opts, NULL)) != -1 )    
    {
        switch(ch)
        {
            case 'i':   
                servip=optarg;
                break;
            case 'p':
                port=atoi(optarg);
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
        }           
     }

    if( !servip || !port )        
    {
                        print_usage(argv[0]);
                        return 0;        
    }
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd < 0)
    {
        printf("Cearte socket failure :%s\a\n",strerror(errno));
        return -1;
    }
    printf("Create socket[%d] sucessfully.\n",sockfd);


    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    rv  = inet_pton( AF_INET,servip,&servaddr.sin_addr);
    if ( rv < 0)
    {
        printf("inet_pton error：%s\a\n",strerror(errno));
    }

    rv = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if(rv <0)
    {
        printf("connect toserver[%s:%d] failure :%s\n\a",servip, port,strerror(errno));
        return -2;
    }
    printf("connect to server[%s:%d] successfully!\n",servip,port);


    while(1)
    {

        rv = write(sockfd,MSG_STR,sizeof(MSG_STR));
        if(rv <0)    
        {
            printf("Write to server failure by socket[%d] failure: %s\n",sockfd,strerror(errno));
            return -3;
        }

        memset(buf,0,sizeof(buf));
        rv = read(sockfd,buf,sizeof(buf));
        if(rv < 0)
        {
            printf("Read to server socket[%d] failure: %s\n",sockfd,strerror(errno));
            return -4;
            continue;
        }
        else if(rv == 0)
        {
        
            printf("socket[%d] get disconnected\n",sockfd);
            return -5;
            continue;
        }
        else if(rv >0)
        {
            printf("Read %d bytes data form Server: %s\n",rv,buf);
            break;
        }

    }


    close(sockfd);

    return 0;
} 
#endif
