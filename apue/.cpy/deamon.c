/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  deamon.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(02/26/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "02/26/2020 08:45:46 PM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <libgen.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char         *progname = basename(argv[0]);

    daemon(0,0);

    openlog(progname, LOG_CONS,LOG_PID);
    syslog(LOG_EMERG, "emergency message\n");
    syslog(LOG_EMERG, "emergency message\n");
    syslog(LOG_EMERG, "emergency message\n");
    syslog(LOG_EMERG, "emergency message\n");

    while (1) 
    {
        ;   
    }
    closelog();
    
    return 0;
}
