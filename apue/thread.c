/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  thread.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(02/27/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "02/27/2020 09:12:26 PM"
 *                 
 ********************************************************************************/
#ifndef __THREAD_H
#define __THREAD_H 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
typedef struct worker_ctx_s
{
    int              shar_var;
    pthread_mutex_t  lock;
}worker_ctx_t;
void  * p_worker1(void *arg);
void  * p_worker2(void *arg);


#endif

int main(int argc, char *argv[])
{
    worker_ctx_t  worker_ctx;
    pthread_attr_t   attr;
    pthread_t        tid;

    worker_ctx.shar_var = 1000;
    pthread_mutex_init(&worker_ctx.lock, NULL);

    if (pthread_attr_init(&attr) < 0)
    {
        printf("Pthread_init error:%s\n", strerror(errno));

        return -1;
    }

    if (pthread_attr_setstacksize(&attr, 120*1024) < 0)
    {
        printf("pthread_setstacksize error:%s\n", strerror(errno));
        return -1;
    }
    if ( pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) < 0)
    {
        printf("PTHREAD_CREATE_DEATCHED error%s\n", strerror(errno));
    }

    pthread_create(&tid, &attr, &p_worker1, &worker_ctx);
    printf("pthread 1[%ld] create ok \n", pthread_self());

    pthread_create(&tid, NULL, &p_worker2, &worker_ctx);
    printf("pthread 2[%ld] create ok \n", pthread_self());
    pthread_attr_destroy(&attr);

    pthread_join(tid, NULL);
    while (1)
    {
        printf("Main contral val = %d\n", worker_ctx.shar_var);
        sleep(3);
        
    }

    alarm(20);

    return 0;
}

void  * p_worker1(void *arg)
{
    if (!arg)
    {
        printf("ilegsl arg\n");
        pthread_exit(NULL);
    }


    printf("The worker1 star workering....\n");
    worker_ctx_t      *ctx = (worker_ctx_t *)arg;
    int     o_val = 10;
    while (1) 
    {
        pthread_mutex_lock(&ctx->lock);
        printf("Before worker1 ++ val = %d\n", ctx->shar_var);
        printf("Before worker1 ++ o_val = %d\n", o_val);
        ctx->shar_var += 1;
        o_val += 1;
        sleep(1);

        printf("After worker1 ++ val = %d\n", ctx->shar_var);

        printf("After worker1 ++ o_val = %d\n", o_val);
        pthread_mutex_unlock(&ctx->lock);
        sleep(2);

    }
}
void  * p_worker2(void *arg)
{
    if (!arg)
    {
        printf("ilegsl arg\n");
        pthread_exit(NULL);
    }

    printf("The worker2 star workering....\n");
    worker_ctx_t     *ctx = (worker_ctx_t *)arg;
    int      o_val = 20;
    while (1) 
    {

        if(0 !=  pthread_mutex_trylock(&ctx->lock))
        {
            continue;
        }
        printf("Before worker2 ++ val = %d\n", ctx->shar_var);
        printf("Before worker2 ++ o_val = %d\n", o_val);
        ctx->shar_var += 1;
        o_val += 1;
        sleep(2);

        printf("After worker2 ++ val = %d\n", ctx->shar_var);

        printf("After worker2 ++ o_val = %d\n", o_val);
        pthread_mutex_unlock(&ctx->lock);

        sleep(1);

    }
}


