#include <iostream>
#include <stdlib.h>
using namespace std;
typedef int Elementtype;
typedef struct st_link
{
	Elementtype data;
	struct st_link* next;
}s_link;

s_link* Create_link(Elementtype data, int num)
{
	s_link* head;
	s_link* newnode;
	s_link* curnode = NULL;

	head = (s_link*)malloc(sizeof(s_link));
	head->data = -1;
	head->next = NULL;

	for (int i = 0; i < num; ++i)
	{
		newnode = (s_link*)malloc(sizeof(s_link));
		if (NULL == head->next)
		{
			newnode->data = data + i;
			newnode->next = NULL;
			curnode = newnode;
			head->next = newnode;
		}
		curnode->next = newnode;
		newnode->data = data + i;
		newnode->next = NULL;
		curnode = newnode;
	}
	return head;
}

int* Push_stack(s_link * link,int cnt)
{
	if (NULL == link || cnt <= 0)
	{
		return NULL;
	}

	int top = 0;
	int *arr =(int *)malloc(sizeof(arr));
	s_link* tmp = link;

	for (top = 0; top < cnt; ++top)
	{
		arr[top] = link->data;
		if (link->next != NULL)
		{
			link = link->next;
			free(tmp);
		}
		tmp = link;

	}
	return arr;
}

void pop_stack(int *arr, int cnt)
{
	for (int i = cnt - 1; i >= 0; --i)
	{
		cout << arr[i] << endl;
	}
	free(arr);
}
void test()
{
	int* Itmp = NULL;
	s_link* tmp = Create_link(10,10);
	Itmp = Push_stack(tmp,10);
	pop_stack(Itmp, 10);
}

int main()
{
	test();
}
