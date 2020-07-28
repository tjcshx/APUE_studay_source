#ifndef __LINK_STACK_H__
#include <iostream>
#include <string>

using namespace std;
typedef int ElementType;

typedef struct Link_Stack {
	ElementType data;
	Link_Stack* next;
}L_Stack;
L_Stack* Init_stack(L_Stack* ptr);
L_Stack* Pop_stack(L_Stack* ptr);
L_Stack* SetEmpty_stack(L_Stack* ptr);
ElementType GetTop_stack(L_Stack* ptr);
#endif // !__LINK_STACK_H__

