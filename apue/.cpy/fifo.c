/*********************************************************************************
 *      Copyright:  (C) 2020 panghu<panghu@gmail.com>
 *                  All rights reserved.
 *
 *       Filename:  fifo.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(2020年03月12日)
 *         Author:  panghu <panghu@gmail.com>
 *      ChangeLog:  1, Release initial version on "2020年03月12日 19时38分21秒"
 *                 
 ********************************************************************************/
#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <libgen.h> 
#include <stdlib.h>

#define FIFO_FILE1          ".fifo_chat1"
#define FIFO_FILE2          ".fifo_chat2"
int g_stop = 0;

void sig_pipe(int signum)
{
    if(SIGPIPE == signum)
    {
        printf("get pipe broken signal and let programe exit\n");
        g_stop = 1;
    }
}

int main(int argc, char **argv)
{
    int            fdr_fifo;
    int            fdw_fifo;
    int            rv;
    fd_set         rdset;
    char           buf[1024];
    int            mode = 0;

    if( argc != 2 )
    {
        printf("Usage: %s [0/1]\n", basename(argv[0]));
        printf("This chat program need run twice, 1st time run with [0] and 2nd time with [1]\n"); 
        return -1;
    }

    mode = atoi(argv[1]);

    //管道为半双工通信，如果双向通信则需要两个管道
    
    if( access(FIFO_FILE1 , F_OK) )
    {
        printf("FIFO file \"%s\" not exist and create it now\n", FIFO_FILE1);
        mkfifo(FIFO_FILE1, 0666);
    }

    if( access(FIFO_FILE2 , F_OK) )
    {
        printf("FIFO file \"%s\" not exist and create it now\n", FIFO_FILE2);
        mkfifo(FIFO_FILE2, 0666);
    }
    signal(SIGPIPE, sig_pipe);

    if( 0 == mode )  
    {
        // 以只读方式打开管道1的读端，默认阻塞，如果该管道写端不被打开则会一直阻塞
        printf("start open '%s' for read and it will blocked untill write endpoint opened...\n", FIFO_FILE1);
        if( (fdr_fifo=open(FIFO_FILE1, O_RDONLY)) < 0 )
        {
             printf("Open fifo[%s] for chat read endpoint failure: %s\n", FIFO_FILE1, strerror(errno)); 
             return -1;
        }

        printf("start open '%s' for write...\n", FIFO_FILE2);
        if( (fdw_fifo=open(FIFO_FILE2, O_WRONLY)) < 0 )
        {
            printf("Open fifo[%s] for chat write endpoint failure: %s\n", FIFO_FILE2, strerror(errno)); 
            return -1;
        }

    }
    else 
    {
        //以只写方式打开管道2的写端，默认阻塞，如果该管道读端不被打开则会一直阻塞
        printf("start open '%s' for write and it will blocked untill read endpoint opened...\n", FIFO_FILE1);
         if( (fdw_fifo=open(FIFO_FILE1, O_WRONLY)) < 0 )
         {
              printf("Open fifo[%s] for chat write endpoint failure: %s\n", FIFO_FILE1, strerror(errno)); 
              return-1;
         }
         printf("start open '%s' for read...\n", FIFO_FILE2);
         if( (fdr_fifo=open(FIFO_FILE2, O_RDONLY)) < 0 )
         {
             printf("Open fifo[%s] for chat read endpoint failure: %s\n", FIFO_FILE2, strerror(errno));
             return-1;
         }
    }

    printf("start chating with another program now, please input message now: \n"); 
    while( !g_stop )
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr_fifo, &rdset);

        //select 多路复用监听标准输入和作为输入的命名管道读端
        rv = select(fdr_fifo+1, &rdset, NULL, NULL, NULL);
        if(  rv <= 0 )
        {
            printf("Select get timeout or error: %s\n", strerror(errno));
            continue;
        }
        //输入的命名管道上有数据到来则从管道上读入数据并打印到标准输出
        if( FD_ISSET(fdr_fifo, &rdset) )
        {
            memset(buf, 0, sizeof(buf));
            rv=read(fdr_fifo, buf, sizeof(buf));
            if( rv < 0 )
            {
                printf("read data from FIFO get errorr: %s\n", strerror(errno));
                break;
            }
            else if( 0 == rv )  //写端关闭
            {
                printf("Another side of FIFO get closed and program will exit now\n");
                break;
            }
            printf("<-- %s", buf);
        }

        //标准输入有数据到来，从标准输入上读完后写入到作为输出的管道的另一个进程
        if( FD_ISSET(STDIN_FILENO, &rdset) )  //接收键盘输入
        {
            memset(buf, 0, sizeof(buf));
            fgets(buf, sizeof(buf), stdin);
            write(fdw_fifo, buf, strlen(buf));
        }

    }
}



