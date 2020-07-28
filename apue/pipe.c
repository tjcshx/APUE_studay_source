/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  pipe.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/13/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/13/2020 10:26:05 AM"
 *                 
 ********************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#define  BUF_SIZE   1024
#define  W_STR      "Hello child, I'am praent."
int main(int argc, char *argv[])
{
    int       pipe_fd[2];
    int       pid;
    char      buf[BUF_SIZE];
    int       wait_status;
    int       rv;

    if (pipe(pipe_fd) < 0) //使用管道
    {
        printf("Piep error: %s\n", strerror(errno));
        return -1;
    }

    pid = fork();  //fork 创建子进程
    if (pid <0)
    {
        printf("Fork error: %s\n", strerror(errno));
        return -2;
    }
    else if (pid > 0)  //父进程
    {
        close(pipe_fd[0]);  //关闭读端
        if ((rv =write(pipe_fd[1], W_STR, sizeof(W_STR)))< 0) //从管道写入数据
        {
            printf("The parent write by pipe_fd[%d] error: %s\n",pipe_fd[1], strerror(errno));
            return -3;
        }
        printf("The parent write %d bytes form pipe_fd[%d] to pipe_fd[%d].\n",rv, pipe_fd[1], pipe_fd[0]);
        wait(wait_status);  //等待子进程结束

        puts("The parent wait child exit and will exit.");
    }
    else if (0 == pid)  //子进程
    {
        close(pipe_fd[1]);  //关闭写端
        memset(buf, 0, BUF_SIZE);

        if ((rv =read(pipe_fd[0], buf, sizeof(buf))) <0)  //从管道读数据
        {
            printf("Read form pipe_fd[%d] error: %s\n", pipe_fd[0],strerror(errno));
            return -4;
        }
        printf("The child read %d bytes form pipe_fd[%d],there are:\n%s.\n", rv, pipe_fd[0],buf);

        puts("The child will go to exit...");
        sleep(1);
        return 0;
    }


    return 0;
}

