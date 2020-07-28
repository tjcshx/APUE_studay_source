/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  cpp_test.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/25/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "04/25/2020 10:49:23 AM"
 *                 
 ********************************************************************************/

#include "cpp_test.h"
#include <stdio.h>
 
#ifdef __cplusplus
extern "C"
{
#endif
     
    void cpp_fun()
    {
            printf("cpp_fun :%s\n","Hello Word C");
    }
     
#ifdef __cplusplus
}
#endif 
