/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  signal.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/13/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/13/2020 09:28:22 AM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/wait.h>
int      g_pa_run  = 0;
int      g_ch_stop  = 0;

void child_handle(int signum);
void parent_handle(int signum);
int main(int argc, char *argv[])
{
    pid_t     pid;
    int       child_status;
    signal(SIGUSR2, child_handle); //注册信号函数
    signal(SIGUSR1, parent_handle); //注册信号函数
    pid = fork();  //创建子进程
    if (pid < 0)
    {
        printf("Fork error: %s\n", strerror(errno));
        return -1;
    }
    if (pid > 0)   //父进程
    {
        printf("The parent start running, but is bolck here,wait the child to sned a signal...\n");
        while (!g_pa_run)  //父进程阻塞在此处等待子进程发送信号
        {
            sleep(3);
            
        }

        printf("The parent will go to  run, and send a signal to child...\n");

        kill(pid, SIGUSR1);  //发送SIGUSR1的信号

        wait(&child_status);  //父进程等待子进程结束
        printf("The parnet will wait child exit and will exit now...\n");
    }


    if (0==pid)  //子进程
    {
        printf("The child will go to run, and send a signal to parent...\n");


        kill(getppid(), SIGUSR2);  //发送SIGUSR2信号使得父进程阻塞
        while (!g_ch_stop) 
        {
            sleep(1);
            
        }


        printf("The child reseve parent signal,and will  go to exit...\n");
        return 0;
    }


    return 0;
}

void  parent_handle(int signum) //父进程的信号处理函数
{
    if (signum == SIGUSR1)
        g_ch_stop = 1;

}
void child_handle(int signum)  //子进程的信号处理函数
{
    if (signum == SIGUSR2)
        g_pa_run = 1;
}
