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
#include <sys/un.h>
#define	MSG_STR  "Hello network word! I'm client!"
#define	BUF_SIZE  1024
#endif
void print_usage(char *paogname)
{
    printf("%s usage : \n", paogname);
    printf("-p(--path): sepcify connect path.\n");
    printf("-m(--message): The message you want to send.\n");
    printf("-h(--help): print this help information.\n");

    return  ;

}
int main (int argc, char **argv)
{

    int                      sockfd;
    int                      rv = -1;
    struct sockaddr_un       servaddr;
    char*                    path    = NULL;
    char*                    message = NULL;
    char                     buf[BUF_SIZE];
    int                      ch;
    int                      temp;
    struct option        opts[] = {
        {"path", required_argument, NULL, 'p'},
        {"message", required_argument, NULL, 'm'},            
        {"help", no_argument, NULL, 'h'},          
        {NULL, 0, NULL, 0}

    };

    while((ch=getopt_long(argc, argv, "p:m:h", opts, NULL)) != -1 )    
    {
        switch(ch)
        {
            case 'p':   
                path=optarg;
                break;
            case 'm':
                message=optarg;
                break;
            case 'h':
                print_usage(argv[0]);
                return 0;
        }           
    }

    if( !path || !message )        
    {
        print_usage(argv[0]);
        return 0;        
    }

    sockfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sockfd < 0)
    {
        printf("Cearte socket failure :%s\a\n",strerror(errno));
        return -1;
    }
    printf("Create socket[%d] sucessfully.\n",sockfd);


    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sun_family = AF_UNIX;
    strncpy(servaddr.sun_path, path, sizeof(servaddr.sun_path) - 1);

    rv = connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    if(rv <0)
    {
        printf("connect toserver[%s] failure :%s\n\a",path,strerror(errno));
        return -2;
    }
    printf("connect to server[%s] successfully!\n",path);


    rv = write(sockfd,message,strlen(message));
    if(rv <0)    
    {
        printf("Write to server failure by socket[%d] failure: %s\n",sockfd,strerror(errno));
        return -3;
    }
    else 
        printf("Write[%s] to server by socket[%d] successfuly!\n", message, sockfd);

    memset(buf,0,sizeof(buf));
    rv = read(sockfd,buf,BUF_SIZE);
    if(rv < 0)
    {
        printf("Read to server socket[%d] failure: %s\n",sockfd,strerror(errno));
        return -4;
    }
    else if(rv == 0)
    {

        printf("socket[%d] get disconnected\n",sockfd);
        return -4;
    }
    else if(rv >0)
    {
        printf("Read %d bytes data form Server: %s\n",rv,buf);
    }
    close(sockfd);
    unlink(path);

    return 0; 
}
