#include "Link_stack.h"
L_Stack* Init_stack(L_Stack* ptr)
{
	ptr->data = -1;
	ptr->next = NULL;
	return ptr;
}
bool IsEmpty(L_Stack* ptr)
{
	if (NULL == ptr->next)
	{
		return true;
	}
	return false;
}
L_Stack* Push_stack(L_Stack* ptr,ElementType data)
{
	L_Stack* new_stack = new L_Stack;
	L_Stack* cur_stack = ptr;

	if (NULL ==ptr->next)
	{
		ptr->next = new_stack;
		new_stack->data = data;
		new_stack->next = NULL;
	}
	else
	{
		new_stack->next = ptr->next;
		new_stack->data = data;
		ptr->next = new_stack;
	}
	return ptr;
}
L_Stack* Pop_stack(L_Stack* ptr)
{
	if (IsEmpty(ptr))
	{
		cout << "Õ»¿Õ" << endl;
	}
	
	while (ptr ->next != NULL)
	{
		cout << ptr->next->data << endl;
		ptr = ptr->next;
	}
	return ptr;
}

L_Stack* SetEmpty_stack(L_Stack* ptr)
{
	if (IsEmpty(ptr))
	{
		cout << "Õ»¿Õ" << endl;
	}
	while (ptr->next != NULL)
	{
		L_Stack* tmp = ptr;
		ptr = ptr->next;
		delete(tmp);
	}
	return ptr;
}
ElementType GetTop_stack(L_Stack* ptr)
{
	if (IsEmpty(ptr))
	{
		cout << "Õ»¿Õ" << endl;
	}
	return ptr->next->data;

}

void test()
{
	L_Stack* ptr = new L_Stack;
	ElementType val = -1;

	Init_stack(ptr);

	if (IsEmpty(ptr))
		cout << "Õ»¿Õ" << endl;
	else
		cout << "Õ»²»Îª¿Õ" << endl;


	Push_stack(ptr, 1);
	Push_stack(ptr, 2);
	Push_stack(ptr, 3);
	Push_stack(ptr, 4);

	if (IsEmpty(ptr))
		cout << "Õ»¿Õ" << endl;
	val = GetTop_stack(ptr);
	cout << "Õ»¶¥ÔªËØÎª£º" << val << endl;
	if (IsEmpty(ptr))
		cout << "Õ»¿Õ" << endl;
	else
		cout << "Õ»²»Îª¿Õ" << endl;
	Pop_stack(ptr);
	ptr = SetEmpty_stack(ptr);

	if (IsEmpty(ptr))
		cout << "Õ»¿Õ" << endl;
	else
		cout << "Õ»²»Îª¿Õ" << endl;
	

}
int main(int argc, char** argv)
{
	test();
	return 0;
}

