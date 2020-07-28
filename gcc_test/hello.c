/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  hello.c
 *    Description:  This file is print hello word simple.
 *                 
 *        Version:  1.0.0(05/05/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "05/05/2020 12:53:16 PM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
int test (void);
int main (int argc, char *argv[])
{
#if 0
   printf("#if 0"); 
#endif 
#if 1
   printf("#if 1\n");
    test();
    printf("This program complied on %s:%s\n", __DATE__,__TIME__);
    printf("Hello Word!\n");
#endif 
    return 0;
} 

int test (void)
{
    printf("The func  is using into %s:%d%s()\n", __FILE__,__LINE__,__FUNCTION__);
    return 0;
} 

