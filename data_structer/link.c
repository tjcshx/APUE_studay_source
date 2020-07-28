/*********************************************************************************
*      Copyright:  (C) 2020 shx
*                  All rights reserved.
*
*         Author:  tianjincheng <473892093@qq.com>
*
********************************************************************************/
#include "link.h"

static void Init_link(s_link* link, ElemType data)  //初始换数据元素
{
	link->data = data;
	link->next = NULL;
}

void Create_linkbytail(s_link* link, ElemType data) //尾插法
{

	s_link* L_newnode = malloc(sizeof(s_link));
	Init_link(L_newnode, data);
	s_link* cur = NULL;
	cur = link;
	if (NULL == link->next)
	{
		link->next = L_newnode;
		g_count++;
	}
	else
	{
		while (cur->next != NULL) //遍历找到最后一各节点
			cur = cur->next;
		cur->next = L_newnode;
		cur = L_newnode;
		g_count++;
	}
}

void Create_linkbyhead(s_link* link, ElemType data)  //头插法
{

	s_link* L_newnode = malloc(sizeof(s_link));
	Init_link(L_newnode, data);
	L_newnode->next = link->next;
	link->next = L_newnode;
	g_count++;
}
void Foreach_link(s_link* link)  //遍历
{
	int i = g_count;
	s_link* tmp = link;
	if (0 == g_count)
		return;
	for (i = g_count; i > 0; i--)
	{
		if (tmp->next != NULL)
		{
			printf("%d\n", tmp->next->data);
			tmp = tmp->next;
		}
		else
			return;

	}
}

/*
用双指针来实现按值来删除一个元素，即一个指向前驱，一个指向后继
*/

void delete_link_bydata(s_link* link, ElemType data)//按值删除元素
{
	int  flag = 0; //默认该元素不存在
	int i = 0;
	s_link* tmp = link;
	s_link* first = link->next; //跳过头节点,指向第一个节点
	s_link* second = first->next; //指向除头节点的第二个节点
	if (0 == g_count)
		printf("链表为空");

	for (i = 0; i < g_count; ++i)
	{
		if (link->next == first && first->data == data) //first 在头节点之后的第一个节点
		{
			link->next = first->next;
			tmp = first;
			first = first->next;
			if (second->next != NULL)
			{
				second = second->next;
			}

			free(tmp);
			flag = 1;
			g_count--;
		}
		else if (data == second->data && second->next != NULL)
		{
			tmp = second;
			first->next = second->next;
			second = second->next;

			free(tmp);
			g_count--;
			flag = 1;
		}
		else if (second->next == NULL && data == second->data)
		{
			first->next = NULL;
			free(second);
			flag = 1;
			g_count--;

		}
		else
		{
			first = first->next;
			if (second->next != NULL)
				second = second->next;
		}



	}
	if (!flag)
		printf("******Not have this data********\n");
}

void delete_linkbypose(s_link* link, int pose)  //按位删除元素
{
	if (pose > g_count || NULL == link)
		return;
	int i = 1;
	s_link* tmp   = NULL;
	s_link* front = NULL;
	tmp = link->next;
	for (i = 1; i < pose; ++i)
	{
		front = tmp;
		tmp = tmp->next;
	}
	front->next = tmp->next;
	free(tmp);

}

static void Isempty(s_link* link)
{
	if (NULL == link->next )
		printf("链表为空\n");
	else
		printf("链表不为空\n");
}

void setempty(s_link* link)
{
	if (NULL == link->next)
		return;
	int       i     = 0;
	s_link* tmp     = NULL;
	s_link* destory = NULL;
	

	
	for (tmp = link; tmp->next != NULL; )
	{
		destory = tmp;
		tmp = tmp->next;
		free(destory);
		

	}

	free(tmp);
	link->next = NULL;


}

void test()
{
	ElemType data;
	s_link* head = malloc(sizeof(s_link));
	Init_link(head, -1);
	Isempty(head);
	Create_linkbytail(head, 1);
	Create_linkbytail(head, 2);
	Create_linkbytail(head, 3);
	Create_linkbytail(head, 4);
	Create_linkbytail(head, 5);
	printf("Before delete:\n");
	Foreach_link(head);
	
	delete_link_bydata(head, 15);
	delete_link_bydata(head, 3);
	delete_link_bydata(head, 8);
	
	delete_linkbypose(head, 4);
	delete_linkbypose(head, 8);

	printf("After delete:\n");

	Foreach_link(head);
	setempty(head);
	Isempty(head);
	Foreach_link(head);
}

int main(int argc, char** argv)
{
	test();
	return 0;
}