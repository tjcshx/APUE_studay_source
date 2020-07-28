/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  time.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/17/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "04/17/2020 08:57:20 PM"
 *                 
 ********************************************************************************/


#include <stdio.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
     time_t   t;
     time_t   tm;

     tm = time(t);

     printf("%s\n", localtime(tm));
    return 0;
}
