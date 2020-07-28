/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  read_alarm.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/26/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/26/2020 11:19:32 AM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE    1024
static void       sig_alrm(int);
static jmp_buf    env_alrm;

int main(int argc, char *argv[])
{
    int      n;
    char     line[MAXLINE];
    if (SIG_ERR == signal(SIGALRM, sig_alrm))
        printf("signal(SIGALARM) error:%s\n", strerror(errno));
    if (setjmp(env_alrm) != 0)
        printf("Read timeouted.\n");
    alarm(10);
    if ((n= read(STDIN_FILENO, line, MAXLINE)) < 0)
        printf("Read error: %s\n", strerror(errno));
    alarm(0);

    write(STDOUT_FILENO, line, n);
    return 0;
}
static void sig_alrm(int signo)
{
    longjmp(env_alrm, 1);
}
