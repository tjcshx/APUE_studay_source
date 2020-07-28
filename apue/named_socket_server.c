/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  socket_server_fork.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(02/23/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "02/23/2020 08:27:18 AM"
 *                 
 ********************************************************************************/
#include "socket_server.h"

void print_usage(char *prograname)
{
    printf("%s usage : \n", prograname);
    printf("-p(--parh): specify sever will go to run with path.\n");
    printf("-m(--msg): specify sever write msg to client.\n");
    printf("-d(--daemon): specify sever will go to run with daemon.\n");
    printf("-h(--help): print this help information.\n");

    return  ;

}
int main(int argc, char *argv[])
{
    get_opt(argc,argv,"p:dm:h");

    return 0;
}

int get_opt(int argc, char * const argv[],const char *optstring)
{
    char*    path;
    int            ch;
    char*    msg = NULL;


    struct option        opts[] = {
        {"path", required_argument, NULL, 'p'},
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
                path=optarg;
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

    if( !path||!msg)
    {
        print_usage(argv[0]);

        return 0;
    }

    if ((socket_start(AF_UNIX, SOCK_STREAM,0, path, msg))< 0)
    {
        printf("socket_start error:%s\n", strerror(errno));
        exit(0);
    }
}
int socket_start(int domain, int type, int protocol, char* path, char *msg)
{
    int                   lisfd = 0;
    int                   clifd = 0;
    int                   on = 1;
    int                   rv = 0;
    char                  buf[BUF_SIZE];
    struct sockaddr_un    serv_addr;
    struct sockaddr_un    cli_addr;
    socklen_t             len = sizeof(serv_addr);

    if ((lisfd = socket(domain,type, protocol))< 0)
    { 
        printf("Socket error:%s\a\n", strerror(errno));
        return -1;
    }

    printf("socket[%d] successfuly!\n", lisfd);

    if ( !access(path, F_OK))
    {
        unlink(path);
    }

    setsockopt(lisfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, path, sizeof(serv_addr.sun_path) - 1);

    if ((rv = bind(lisfd, (struct sockaddr *)&serv_addr, len)) < 0)
    {
        printf("Bind error %s\n", strerror(errno));
        goto EXIT;
    }

    if ((rv = listen(lisfd, 13)) < 0)
    {
        printf("Listen error:%s\n", strerror(errno));
        goto EXIT;
    }

    printf("Waiting clinet to connect.....\n");
    while(1)
    {
        if ((clifd = accept(lisfd, (struct sockaddr *)&cli_addr, &len))< 0)
        {
            printf("Accept error:%s\n", strerror(errno));
            goto EXIT;
        }


        if ((rv = rdwr_init(clifd, buf, msg)) < 0 )
        {
            printf("Write or read form client error:%s\n", strerror(errno));
            goto EXIT;
        }
    }

    return clifd;
EXIT:
    unlink(path);
    close(lisfd );
    close(clifd );
    return -1;
}

int  rdwr_init(int clinefd,char *buf, char * msg)
{
    int                   rv = 0;
    memset(buf,0,  BUF_SIZE);
    while(1)
    {
        if ((rv = read(clinefd, buf, BUF_SIZE)) < 0)
        {
            printf("Read by socket[%d] error:%s\n", clinefd, strerror(errno));
            goto STOP;
        }
        else if (0 == rv)
        {
            printf("The connect get disconneceted.\n");
            goto STOP;
        }
        else if (rv > 0)
        {
              printf("Read %d bytes data from client, there are :%s\n", rv, buf);
        }

        if ((rv =write(clinefd, msg, strlen(msg))) < 0)
        {
            printf("write to cilent by socket[%d] error:%s \n",clinefd, strerror(errno));
            goto STOP;
        }
        printf("Write[%s] to clinet successfuly.\n", msg);



    }
STOP:
    printf("The socket[%d] will eixt!\n", clinefd);
    exit(0);
}
