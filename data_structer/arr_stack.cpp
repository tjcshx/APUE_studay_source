#include "arr_stack.h"
void Init(st_stack* s_ptr)
{
	if (NULL == s_ptr)
	{
		exit(0);
	}
	s_ptr->top = -1;
}

bool IsEmpty(st_stack* s_ptr)
{
	if (NULL == s_ptr)
	{
		exit(0);
	}

	if (-1 == s_ptr->top)
	{
		return true;
	}
	else
		return false;
}

void Push(st_stack* s_ptr, ElemetType data)
{
	if (NULL == s_ptr)
	{
		exit(0);
	}
	if (Max_dataSize == s_ptr->top)
	{
		cout << "ջ��" << endl;
		exit(0);
	}
		

	s_ptr->Data[++(s_ptr->top)] = data;
}
void Pop(st_stack* s_ptr)
{
	if (NULL == s_ptr)
	{
		exit(0);
	}

	if (-1 == s_ptr->top)
	{
		cout << "ջ��" << endl;
		exit(0);
	}
		
	while (s_ptr->top != -1)
	{
		cout << s_ptr->Data[(s_ptr->top)--] << endl;
	}
	
}
ElemetType GetTop(st_stack* s_ptr)
{
	if (NULL == s_ptr)
	{
		exit(0);
	}

	return s_ptr->Data[s_ptr->top];
}
bool SetEmpty(st_stack* s_ptr)
{
	if (NULL == s_ptr)
	{
		exit(0);
	}

	while (s_ptr->top != -1)
	{
		if (-1 == s_ptr->top)
		{
			cout << "ջ��" << endl;

		}
			

		s_ptr->Data[s_ptr->top] = -1;
		s_ptr->top--;
	}
	if (-1 == s_ptr->top)
	{
		return true;
	}
	else
		return false;
}
void test()
{
	ElemetType  val = -1;
	st_stack* arr = new st_stack;
	Init(arr);


	if (IsEmpty(arr))
	{
		cout << "ջ��" << endl;
	}
	else
	{
		cout << "ջ��Ϊ��" << endl;
	}
	

	Push(arr, 'A');
	Push(arr, 'B');
	Push(arr, 'C');
	Push(arr, 'D');


	if (IsEmpty(arr))
	{
		cout << "ջ��" << endl;
	}
	else
		cout << "ջ��Ϊ��" << endl;

	

	val = GetTop(arr);
	cout << "ջ��Ԫ��Ϊ��" << val << endl;
	
	Pop(arr);

	if (SetEmpty(arr))
	{
		cout << "�ÿճɹ�" << endl;
	}
	else
		cout << "�ÿ�ʧ��" << endl;

	if (IsEmpty(arr))
	{
		cout << "ջ��" << endl;
	}
	else
		cout << "ջ��Ϊ��" << endl;

}


int main(int argc, char** argv)
{
	test();

	return 0;
}

