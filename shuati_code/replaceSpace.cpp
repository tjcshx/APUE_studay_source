/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  str_pleace.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(03/01/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "03/01/2020 10:24:44 PM"
 *                 
 ********************************************************************************/
/* 
 * 题目描述 str = "We Are Happy.",将其中的空格替换为%20, 输出为：We%20Are%20Happy.
 * 
 * 
 * */
#include <iostream>
#include <string.h>

using namespace std;
void replce_space(char* str, int length)
{
    if (NULL == str || length < 0) //参数合法性判断
    {
        return;
    }

    int    newlength = 0;
    int    snum = 0;
    for (int i = 0; i < length; i++)  //统计空格数目
    {
        if (' ' == str[i])
        {
            snum += 1;
        }

    }


    newlength = length + 2 * snum;  //统计空格数目后总长度

    while (length +1)
    {
        if (' ' == str[length])  //‘’ ’替换位%20‘
        {
            str[newlength--] = '0';
            str[newlength--] = '2';
            str[newlength] = '%';
        }
        else
        {
            str[newlength] = str[length];
        }
        length--;
        newlength--;
    }
}

int main()
{
    char str[100] = "We Are Happy";
    replce_space(str, strlen(str));
    cout << str << endl;

    return 0;
}

