/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  prt.c
 *    Description:  This file Description gdb 调试段错误的。
 *                 
 *        Version:  1.0.0(04/08/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "04/08/2020 08:31:14 AM"
 *                 
 ********************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void  get_memroy(char ** ptr, int size);
char* get_memroy1(char * ptr, int size);

void test01();
int main(int argc, char *argv[])
{
    test01();
    return 0;
}

void get_memroy(char ** ptr, int size)
{
    *ptr = malloc(size);
}

char* get_memroy1(char * ptr, int size)
{
    ptr = malloc(size);
    return ptr;
}


void test01()
{

    char*   ptr = NULL;

    ptr = get_memroy1(ptr, 100);
    strcpy(ptr, "Hello Word\n");
    printf("%s", ptr);

    free(ptr);
}


