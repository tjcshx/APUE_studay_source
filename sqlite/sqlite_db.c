/********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  sqlite_db.c
 *    Description:  This file sqlite studay saeple.
 *                 
 *        Version:  1.0.0(03/29/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/29/2020 12:09:07 PM"
 *                 
 ********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <unistd.h>
#define  HEAD   0x5A
#define  TAG    0xfd
#define  LENGTH 0x03 
static int   g_ito_db_num = 0;
#define  PATHNAME  "/tmp/stu.db"
/*
 * Description:     This func is to operation to the sqlite3 table.
 * char * pathname: Is the sqlite3 table position.
 */

int InsertInto_db( sqlite3* db);
int DeleteFrom_db( sqlite3* db);
int QueryFrom_db(  sqlite3* db);
int UpdateInto_db( sqlite3* db);
int callback(void* para, int f_num, char ** f_value,char** f_name);

int sqlite_create(char *pthaname)
{
    sqlite3*          db;
    const char*       sql_create = "create table stu (id Integer primary key autoincrement, name char, score integer)";
    printf("access ok ");
    int               cmd;

    if (access(PATHNAME, F_OK) != 0)
    {

        if (sqlite3_open(PATHNAME, &db) != SQLITE_OK)
        {
            printf("Open sqlite error:%s\n", sqlite3_errmsg(db));
            return -1;
        }
        else 
        {
            printf("Open sqlite success.\n");
        }       printf("access ok ");
        if (sqlite3_exec(db, sql_create, NULL, NULL, NULL)!= SQLITE_OK)
        {
            printf("Create table error:%s\n", sqlite3_errmsg(db));
            return -1;
        }
        else 
        {
            printf("Create table success.\n");
        }


    }

    if (sqlite3_open(PATHNAME, &db) != SQLITE_OK)
    {
        printf("Open sqlite error:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    else 
    {
        printf("Open sqlite success.\n");
    }
    while (1) 
    {
        puts("**************************************");
        printf("1: insert data, 2:delete data, 3: query data, 4: update data, 5: qiut. \n");
        puts("**************************************");

        scanf("%d", &cmd);

        switch (cmd) 
        {
            case 1:
                InsertInto_db(db);
                break;
            case 2:
                DeleteFrom_db(db);
                break; 
            case 3:
                QueryFrom_db(db);
                break;
            case 4:
                UpdateInto_db(db);
                break;
            case 5:
                sqlite3_close(db);
                exit(0);
            default:
                puts("Error cmd.");

        }

    }


}


int InsertInto_db(sqlite3* db)
{
    int     id;
    char    name[32] = {};
    int     score;
    char    sql_insert[128] = {};
    memset(sql_insert, 0, sizeof(sql_insert));

    puts("Please enter id:");
    scanf("%d", &id);
    getchar();
    puts("Please enter name:");
    scanf("%s", name);
    getchar();
    puts("Please enter score:");
    scanf("%d", &score);
    getchar();

    sprintf(sql_insert, "insert into stu values(%d,'%s', %d);",id,name, score);

    if (sqlite3_exec(db, sql_insert, NULL, NULL, NULL)!= SQLITE_OK)
    {
        printf("Insert data into table error:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    else
    {
        printf("Insernt data to table success.\n");
        g_ito_db_num ++;
        printf("g_ito_db_num = %d\n", g_ito_db_num);
    }
    

    return 0;
}

int DeleteFrom_db(sqlite3* db)
{
    char del_sql[128] = {};
    int           id  = 0;
    puts("Enter the id you want delete:");
    scanf("%d", &id);
    snprintf(del_sql, 128, "delete from stu where id = %d",id);
    if (sqlite3_exec(db, del_sql, NULL, NULL, NULL)!= SQLITE_OK)
    {
        printf("Delete data from table error:%s\n", sqlite3_errmsg(db));
        return -1;
    }       
    else
    {           
        printf("Delete data from table success.\n");       
        g_ito_db_num --;
        printf("g_ito_db_num = %d\n", g_ito_db_num);
    }  

    return 0;
}
int QueryFrom_db(sqlite3* db)
{
    char del_sql[128] = {};
    snprintf(del_sql, 128, "select * from stu");
    if (sqlite3_exec(db, del_sql, callback, NULL, NULL)!= SQLITE_OK)
    {
        printf("Delete data from table error:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    else
    {
        printf("Query  data from table success.\n");
    }

    return 0;
}
int callback(void* para, int f_num, char ** f_value,char** f_name)
{
    printf("f_num = %d", f_num);
    int  i =0;
    for (i = 0; i < f_num; ++i) 
    {
        printf("%-11s", f_value[i]);
    }
    putchar(10);

    return 0;

}
int UpdateInto_db(sqlite3* db)
{
    char del_sql[128] = {};
    int           id  = 0;
    int        score  = 0;  
    puts("Enter the id you want Update:");
    scanf("%d", &id);
    getchar();
    puts("Enter the data you want Update:");
    scanf("%d", &score);
    getchar();
    snprintf(del_sql, 128, "update stu set score = %d where id = %d",score, id);
    if (sqlite3_exec(db, del_sql, NULL, NULL, NULL)!= SQLITE_OK)
    {
        printf("Delete data from table error:%s\n", sqlite3_errmsg(db));
        return -1;
    }
    else
    {
        printf("Update data from table success.\n");
    }

    return 0;
}

void test()
{
    printf("access ok ");
    sqlite_create(PATHNAME);
}
int main(int argc, char *argv[])
{
    test();

    return 0;
}

