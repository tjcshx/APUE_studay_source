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
void get_memroy(char * ptr, int size);
void test01();
int main(int argc, char *argv[])
{
    test01();
    return 0;
}


void get_memroy(char * ptr, int size)
{
    ptr = malloc(size);
    printf("malloc ptr add:%p\n", ptr);
}
void test01()
{

    char*   ptr = NULL;

    printf("before get_memroy func ptr add:%p\n", ptr);
    get_memroy(ptr, 100);
    printf("after get_memroy func ptr add:%p\n", ptr);
    strcpy(ptr, "Hello Word\n");
}


