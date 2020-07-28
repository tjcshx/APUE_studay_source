#include <iostream>  
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

typedef struct queue
{
	int            data;
	struct queue*   next;
}qu;

inline qu* Init_Queue(qu* q, int data);            //初始化一个队列的节点
qu* Insert_Queue(qu* q, int data, int q_length);   //入队
void Out_Queue(qu* q, int q_length);                             //出队

int main()
{
	qu* q1;
	q1 = (qu *)malloc(sizeof(qu));
	qu* q2 = Insert_Queue(Init_Queue(q1, -1), 96, 21);
	Out_Queue(q2, 21);
	return 0;
}

inline qu* Init_Queue(qu* q, int data)
{
	q->data = data;
	q->next = NULL;

	return q;
}
qu* Insert_Queue(qu* q, int data, int q_length)
{
	qu* head = q;
	qu* cut = q;
	int  i = 0;
	if (q_length <= 0 || NULL == q)
	{
		cout << "Error queue length or queue is't init." << endl;
		return NULL;
	}
	puts("入队：");
	cout << endl;
	for (i = 0; i < q_length; i++)
	{
		qu* newq = (qu*)malloc(sizeof(qu));

		if (head->next == NULL)
		{
			head->next = newq;
			cut = newq;
			Init_Queue(newq, data + i);
			cout << newq->data << "  ";
		}
		else
		{
			cut->next = newq;
			Init_Queue(newq, data + i);
			cout << newq->data << "  ";
			cut = newq;

		}

	}
	cout << endl;
	cout << endl;

	return q;

}

void Out_Queue(qu* q, int q_length)
{
	int  i = 0;
	if (NULL == q)
		return;
	qu* head = q;

    puts("出队：");
	cout << endl;
	q = head->next;
	for(i = 1; i< q_length +1; ++i)
	{           
		if (q->next != NULL)
		{
			
			cout << q->data << "  ";
		}
		else
			cout << q->data << "  ";

		q = q->next;
	}

	cout << endl;
	cout << endl;

}
