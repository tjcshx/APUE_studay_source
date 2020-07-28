#ifndef  __LINK_H__
#define  __LINK_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef int    ElemType;
typedef struct st_link
{
	ElemType         data;
	struct st_link* next;
}s_link;
static void Init_link(s_link* link, ElemType data);
void Create_linkbytail(s_link* link, ElemType data);
void Create_linkbyhead(s_link* link, ElemType data);
void Foreach_link(s_link* link);
static int g_count = 0;
void delete_link_bydata(s_link* link, ElemType data);
static void Isempty(s_link* link);
void delete_linkbypose(s_link* link, int pose);
void setempty(s_link* link);
#endif // ! __LINK_H__

