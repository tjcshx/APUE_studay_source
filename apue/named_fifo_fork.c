/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  named_fifo.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/13/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/13/2020 01:38:37 PM"
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
#define FIFO_FILE1      ".fifo1"
#define FIFO_FILE2      ".fifo2"
#define BUF_SIZE        1024
int        g_stop = 0;
void signal_pipe(int   signum)  //捕捉SIGPIPE信号
{
    if (SIGPIPE == signum)
    {
        printf("Get pipe broken signal and let porgrame exit...\n");
        g_stop = 1;
    }

}
int main(int argc, char *argv[])
{
    int        fdr_fifo = -1;
    int        fdw_fifo = -1;
    int        rv = -1;
    fd_set     rdset;
    char       buf[BUF_SIZE];
    int        flag  = -1;
    if (argc != 2)
    {
        printf("Usage: %s[0/1]\n", basename(argv[0]));
        printf("This program need run twice, first time is running with[0] and the second time is runing with[1]...\n");

        return -1;
    }
    flag = atoi(argv[1]); 

    if (access(FIFO_FILE1, F_OK)) //判断FIFO_FILE1 是否存在
    {
        printf("Fifo file \"%s\" not exist and will create it now.\n", FIFO_FILE1);
        mkfifo(FIFO_FILE1, 06666);
    }

    if (access(FIFO_FILE2, F_OK))
    {
        printf("Fifo file \"%s\" not exist and will create it now.\n", FIFO_FILE2);
        mkfifo(FIFO_FILE2, 06666);
    }

    signal(SIGPIPE, signal_pipe);  ///注册信号函数

    if (0 == flag)
    {
        /*
         *   在这里打开的命名管道FIFO_FILE1默认是阻塞模式，
         *   如果命名管道的写端不打开open会一直阻塞在这里;
         *   
         *   如果在这里打开FIFO_FILE1的读端，则另一个程序必须打开FIFO_FILE1的写端，
         *   否则会出现死锁，反之亦然
         *
         * */
        printf("Start open '%s'for read and it will bolcked here untill write pipe opened...\n", FIFO_FILE1);
        if ( (fdr_fifo = open(FIFO_FILE1, O_RDONLY)) < 0) //以只读的形式打开FIFO_FILE1的读端
        {
            printf("Open fifo[%s] for read error: %s\n", FIFO_FILE1, strerror(errno));
            return -1;

        }

        printf("Start open '%s' for write ...\n", FIFO_FILE2);
        if ( (fdw_fifo = open(FIFO_FILE2, O_WRONLY)) < 0)//以只写的形式打开FIFO_FILE2的写端
        {
            printf("Open fifo[%s] for write error: %s\n", FIFO_FILE2, strerror(errno));
            return -1;

        }
    }
    else 
    {
        printf("Start open '%s'for write and it will bolcked here untill write pipe opened...\n", FIFO_FILE1);
        if ( (fdw_fifo = open(FIFO_FILE1, O_WRONLY)) < 0) //以只写的形式打开FIFO_FILE1的写端
        {
            printf("Open fifo[%s] for write error: %s\n", FIFO_FILE1, strerror(errno));
            return -1;

        }

        printf("Start open '%s' for read ...\n", FIFO_FILE2);
        if ( (fdr_fifo = open(FIFO_FILE2, O_RDONLY)) < 0)//以只读的形式打开FIFO_FILE2的读端
        {
            printf("Open fifo[%s] for read error: %s\n", FIFO_FILE2, strerror(errno));
            return -1;
        }
    }

    printf("Start chating with another program now, enter the messsage you want to send:\n");
    while(!g_stop)
    {
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset); //标准输入加入道select的监听列表
        FD_SET(fdr_fifo, &rdset);     //命名管道的读端加入道select的监听列表

        rv = select(fdr_fifo + 1, &rdset, NULL, NULL, NULL);//使用select的多路复用分别监听标准输入和命名管道的读端
        if (rv <= 0)
        {
            printf("Select get timeout or error: %s\n", strerror(errno));

            continue;
        }

        if (FD_ISSET(fdr_fifo, &rdset)) //如果是fdr_fifo事件到来，则进行命名管道的读操作
        {
            memset(buf, 0, BUF_SIZE);
            rv  = read(fdr_fifo, buf,sizeof(buf));
            if (  rv< 0)
            {
                printf("Read form fifo get error: %s\n", strerror(errno));
                break;
            }
            else if (0 == rv)
            {
                printf("Another side of fifo get closed and program will exit now.\n");
                break;
            }

            printf("<---------%s\n", buf);
        }
        if (FD_ISSET(STDIN_FILENO, &rdset)) //如果是标准输入的事件发生，则进行写操作
        {
            memset(buf, 0, BUF_SIZE);
            fgets(buf, BUF_SIZE, stdin);
            write(fdw_fifo, buf, strlen(buf));

        }
    }

    printf("The fifo file will delete\n");
    system("rm -r .fifo*");//删除产生的fifo文件
    return 0;
}

