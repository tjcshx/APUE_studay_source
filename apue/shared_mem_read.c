/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  shared_mem_read.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/14/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/14/2020 04:38:36 PM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define FTOK_PATH            "/dev/null" 
#define FTOK_PROJID          0x28
typedef struct st_person
{
    char            name[64];  
    int             age;
} t_person;
int main(int argc, char **argv) 
{
    key_t          key;
    int            shmid;  
    int            i;
    t_person     *person;

    if( (key=ftok(FTOK_PATH, FTOK_PROJID)) < 0 )  
    {
        printf("ftok() get IPC token failure: %s\n", strerror(errno));
        return -1;
    }   

    shmid = shmget(key, sizeof(t_person), IPC_CREAT|0666);   
    if( shmid < 0)
    {
        printf("shmget() create shared memroy failure: %s\n", strerror(errno));    
        return -2; 
    }   

    person = shmat(shmid, NULL, 0);    
    if( (void *)-1  == person )

    {
        printf("shmat() alloc shared memroy failure: %s\n", strerror(errno)); 
        return -2;  
    }   

    for(i=0; i<4; i++)
    {
        printf("Person '%s' age [%d]\n", person->name, person->age);     
        sleep(1);
    }   

    shmctl(shmid, IPC_RMID, NULL);

    return 0; 
}

