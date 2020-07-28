/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *       Filename:  link_list.c
 *    Description:  This file 
 *                 
 *        Version:  1.0.0(02/27/2020)
 *         Author:  tianjincheng <473892093@qq.com>
 *      ChangeLog:  1, Release initial version on "02/27/2020 09:35:12 AM"
 *                 
 ********************************************************************************/
#ifndef __LINK_LIST_H
#define __LINK_LIST_H 
#define TAIL  //#define HEAD 采用头插法创建链表，#define TAIL 采用尾插法创建链表
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
typedef struct Link_List 
{
    int                 data;
    struct Link_List    *next;
}L_list;

L_list * create_list(L_list * L, int data);
L_list * delete_data(L_list* L, int pose);
L_list * insert_data(L_list* L, int pose, int data);  
void foreach(L_list * L);

#endif
int main(int argc, char *argv[])
{
    L_list * L;
    L_list * head;
    L_list * tail;
    int data;
    tail = create_list(L, data);  //创建链表
    //head = insert_data(tail, 3, 50);  //按位插入元素
    puts("Before delete:");
    foreach(tail);         //遍历链表
    puts("ok");
    head = delete_data(tail, 3);  //按位删除元素
    puts("After delete:");
    foreach(head);  

    return 0;
}
#ifndef TAIL //#define TAIL 采用尾插法创建链表
L_list * create_list(L_list * L, int data)
{

    L_list * head; 
    head  = malloc(sizeof(L_list));
    head ->data = 20;
    head ->next = NULL;
    L = head;
    for (data = 20; data <30;data++)
    {
        L_list * newNode = malloc(sizeof(L_list));
        L -> next = newNode;
        L = newNode;
        newNode -> data = data;
        newNode -> next =NULL;

    }

    return head;

}
#endif 
#ifndef HEAD //#define HEAD 采用头插法创建链表
L_list * create_list(L_list * L, int data)
{

    L_list * tail;
    L  = malloc(sizeof(L_list));
    tail = L;
    L ->data = 20;
    L ->next = NULL;
    for (data = 20; data < 30 ;data++)
    {
        L_list * newNode = malloc(sizeof(L_list));
        if (L ->next == NULL)
        {
            L -> next = newNode;
            tail = newNode;
            tail -> data = data;
            tail -> next = NULL;
        }
        else 
        {
            newNode ->next = tail;
            L->next = newNode;
            newNode -> data = data;
            tail = newNode;
        }
    }

    return L;
}
#endif 
void foreach(L_list * head)
{
    while (NULL != head->next)
    {
        if (head -> next != NULL) 
        {
            head = head->next;
            printf("%d\n", head->data);
        }
    }

}

L_list * insert_data(L_list* L, int pose, int data)
{
    int   i = 0;
    L_list* tmp;
    L_list* l;
    l= L;
    tmp = L;
    if (NULL == L || 0 == pose)
    {
        printf("Illegal parameter\n");
        return;
    }
    for ( i = 0; i<pose; i++)
    {

        tmp = l->next;
        l = l->next;
    }
    L_list * newNode = malloc(sizeof(L_list)); 
    newNode ->data = data;
    newNode -> next = tmp ->next->next;
    tmp ->next = newNode;

    return L;
}
L_list * delete_data(L_list* L, int pose)
{ 
    L_list*    tmp;
    L_list*    l;
    l= L;
    tmp = L;
    int        i = 0;
    if (NULL == L || 0 == pose)
    {
        printf("Illegal parameter\n");
        return;    
    }
    for (i = 0; i< pose; i++)
    {
        tmp = l->next;
        l = l->next;
    }
    tmp = tmp ->next;
    l->next = tmp -> next;
    free(tmp);
    return L;

}
