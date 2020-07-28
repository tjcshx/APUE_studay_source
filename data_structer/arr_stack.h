#ifndef __SATCK_H__
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

typedef char ElemetType;
const int   Max_dataSize = 7;
typedef struct Dstack
{
	ElemetType Data[Max_dataSize];
	int   top;
}st_stack;
void Init(st_stack* s_ptr);
void Push(st_stack* s_ptr, ElemetType data);
void Pop(st_stack* s_ptr);
ElemetType GetTop(st_stack* s_ptr);
bool SetEmpty(st_stack* s_ptr);

#endif // !__SATCK_H__


