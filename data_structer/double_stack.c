/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  double_stack.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(04/25/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "04/25/2020 10:30:05 PM"
 *                 
 ********************************************************************************/
/* 
 *功能描述:用数组实现双向来链表的入栈与出栈
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#define   MAX_ARR_SIZE   64
#define   TAG_TOP1       1  /*表示数据从arr[0]开始入栈，否则从arr[MAX_ARR_SIZE]处开始入栈*/
#define   TAG_TOP2       2  /*表示数据从arr[0]开始入栈，否则从arr[MAX_ARR_SIZE]处开始入栈*/
#define   TAG_POP        1  /*表示从arr[0]开始出栈，否则从arr[MAX_ARR_SIZE]处开始出栈*/
#define   MALLOC         printf("malloc++\n");
#define   FREE_MALLOC    printf("malloc--\n");
typedef int ElementType;

typedef struct st_arr_stack
{
    ElementType  top1;
    ElementType  top2;
    ElementType  arr[MAX_ARR_SIZE];
}s_arr_stack;
s_arr_stack *  Init_arr_stack(s_arr_stack * parr)
{
    int  i = 0;
    parr = malloc(sizeof(s_arr_stack));
    if (NULL == parr)
        return;
    MALLOC;
    parr->top1 = 0;
    parr->top2 = MAX_ARR_SIZE - 1;
    for (i = 0; i< MAX_ARR_SIZE; i++)
        parr->arr[i] = -1;
    return parr;
}
/* 表示数据从arr[0]开始入栈，否则从arr[MAX_ARR_SIZE]处开始入栈 */
s_arr_stack* push_stack(s_arr_stack* parr, ElementType data, int tag)
{
    if (NULL == parr)
        return ;
    if (1 == tag)
    {
        if (1 == parr->top2 - parr->top1)
        {
            puts("栈满");
            return ;
        }
        else 
        {
            parr->arr[parr->top1] = data;
            parr->top1 ++;
        }
        return parr;
    }
    else 
    {
        if (1 == parr->top2 - parr->top1)
        {
            puts("栈满");
            return ;
        }
        else 
        {
            parr->arr[parr->top2] = data;    
            parr->top2 --;
        }
        return parr;
    }

}

void pop_stack(s_arr_stack* parr, int tag)
{
    int i = 0;

    if (NULL == parr)
        return ;
    if (1 == tag)
    {
        if (0 == parr->top1)
        {                    
            puts("top1栈空");    
            return ;         
        }   
        else 
        {
                printf("top2 pop :%d\n", parr->arr[parr->top1--]);
        }  

    }      
    else   
    {              
        if (MAX_ARR_SIZE - 1 == parr->top2)
        {        
            puts("top2栈空");
            return ;
        }        
        else     
        {   
                printf("top1 pop :%d\n", parr->arr[parr->top2++]);
        }        
    }       
}

int main(int argc, char *argv[])
{
    s_arr_stack arr;
    s_arr_stack *parr1;
    s_arr_stack *parr2;
    parr1 = Init_arr_stack(&arr);
    parr2 = push_stack(parr1, 5, TAG_TOP1);
    parr2 = push_stack(parr1, 5, TAG_TOP1);
    parr2 = push_stack(parr1, 5, TAG_TOP1);
//    parr2 = push_stack(parr1, 6, TAG_TOP2);
    pop_stack(parr2, TAG_TOP1);
  //  pop_stack(parr2, TAG_TOP2);


    return 0;
}
