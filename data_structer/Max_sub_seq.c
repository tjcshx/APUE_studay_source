/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  Max_sub_seq.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/22/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "04/22/2020 08:45:38 PM"
 *                 
 ********************************************************************************/
/*
 * 功能描述：求给定一个具体的数组的最大子序列之和
 * 参数描述：int  *arr：给定的具体数组， int len 给定数组的大小
 *
 */

#include <stdio.h>
#define  ARR_SIZE(x)     ((sizeof(x))/(sizeof(x[0])))    //求数组的大小
#define  MAX(num1, num2) (((num1)>(num2)?(num1):(num2))) //求两数中最大的一个

int max_sub_seq1(int *arr, int len);
int max_sub_seq2(int *arr, int len);
int max_sub_seq3(int *arr, int len);
int DivideandRule(int *arr, int left,int right);
int maxcross(int *arr, int left, int mid, int right);
inline int max_three_num(int num1, int num2, int num3);
void test()
{

    int       max_num1 = 0;
    int       max_num2 = 0;
    int       max_num3 = 0;
    int       max_num4 = 0;
    int  arr[10] ={-1,3,4,5,-8,-6,-9,-52-89,-56,-98};
    max_num1 = max_sub_seq1(arr, ARR_SIZE(arr));
    max_num2 = max_sub_seq2(arr, ARR_SIZE(arr));
    max_num3 = max_sub_seq3(arr, ARR_SIZE(arr));
    max_num4 = DivideandRule(arr, 0, ARR_SIZE(arr) -1);
    puts("暴力算法:");
    printf("max_num1 = %d ARR_SIZE = %d\n", max_num1, (int)ARR_SIZE(arr));
    puts("优化后的暴力算法:");
    printf("max_num2 = %d ARR_SIZE = %d\n", max_num2, (int)ARR_SIZE(arr));
    puts("在线算法:");
    printf("max_num3 = %d ARR_SIZE = %d\n", max_num3, (int)ARR_SIZE(arr));
    puts("分而治之:");
    printf("max_num4 = %d ARR_SIZE = %d\n", max_num4, (int)ARR_SIZE(arr));
}
int main(int argc, char *argv[])
{
    test();
    return 0;
}

int max_sub_seq1(int *arr, int len) //初始版本 时间复杂度为O(n^3)
{
    int   cur_num; 
    int   max_num;
    if (!arr || len < 0)
    {
        printf("Error input arguements\n");
        return -1;
    }
    int i, j ,k;
    for (i = 0; i < len; ++i) 
    {
        for (j = i; j < len; j++)
        {
            cur_num = 0;
            for (k = i; k <= j; ++k)
                cur_num += arr[k];
            max_num = MAX(cur_num, max_num);

        }

    }
    return max_num;
}
int max_sub_seq2(int *arr, int len)  //稍加优化 时间复杂度为O(n^2)
{
    int   cur_num = 0; 
    int   max_num = 0;
    int i, j;
    if (!arr || len < 0)
    {
        printf("Error input arguements\n");
        return -1;
    }
    for (i = 0; i < len; i++) 
    {
        cur_num = 0;
        for (j = i; j < len; j++)
        {
            cur_num += arr[j];
            max_num = MAX(cur_num, max_num);
        }

    }
    return max_num;
}
int max_sub_seq3(int *arr, int len)  //在线处理的思想来优化代码 时间复杂度为n,但是对于数据元素全为负数的序列求值为（0）会出错
{
    int i, j;
    int   cur_num; 
    int   max_num;
    if (!arr || len < 0)
    {
        printf("Error input arguements\n");
        return -1;
    }
    cur_num = max_num = 0;
    for (i = 0; i < len; i++) 
    {
        cur_num += arr[i];
        max_num = MAX(cur_num, max_num);
        if(cur_num < 0) 
        {
            cur_num = 0;
        }

    }
    return max_num;
}
/* 分而治之的思想来实现求最大子序列的问题， 时间复杂度为 nlog(n) */
inline int max_three_num(int num1, int num2, int num3)
{

    int max = 0;
    max = num1 > num2 ? num1:num2;
    max = num3 > max ?  num3:max;
    return max;
}
int maxcross(int *arr, int left, int mid, int right)
{
    int i;
    int sum = 0;
    int leftSum = 0;
    int rightSum = 0;
    for (i = mid; i >=left; i--)
    {
        sum += arr[i];
        if (sum > leftSum)
            leftSum = sum;
    }
    sum = 0;
    for (i = mid + 1; i <= right; i++)
    {
        sum += arr[i];
        if (sum > rightSum)
            rightSum = sum;
    }
    return leftSum + rightSum;
}

int DivideandRule(int *arr, int left,int right)
{
    int mid=0;
    int maxLeft=0, maxRight=0, maxMiddle=0;
    if (left == right) //只有一个数据元素
    {
        if (arr[left] > 0)
            return arr[left];
        else 
            return 0;
    }

    mid = (left + right) / 2;//分

    maxLeft = DivideandRule(arr, left, mid);         /*左序列递归求和*/

    maxRight = DivideandRule(arr, mid + 1, right);  /*右序列递归求和0*/
    maxMiddle = maxcross(arr,left,mid,right);        /* 有交集的左右序列求和 */
    return max_three_num(maxLeft, maxRight, maxMiddle);
}
