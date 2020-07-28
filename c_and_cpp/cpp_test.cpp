/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  test.cpp
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/25/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "04/25/2020 09:15:58 AM"
 *                 
 ********************************************************************************/
/*  
extern "C" {
#include "c_test.h"
}
*/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <stdio.h>
           void show();
#ifdef __cplusplus
}
#endif

int main(int argc, char *argv[])
{
    show();
    return 0;
}
