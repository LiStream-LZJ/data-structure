#ifndef _D_STRUCT_H
#define _D_STRUCT_H
typedef int Status;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#include <stdio.h>
#include <stdlib.h>
#endif // _D_STRUCT_H

typedef struct {
	int coef;
	int exp;
}ElemType;
typedef struct Node {
	ElemType data;
	struct Node*next;
}LNode, *LinkList;
/*Status initList(LinkList &L)
{
L = new LNode;
L->next = NULL;
return OK;
}*/
Status GreateList(LinkList & L)
{
	int n, i; LNode*p, *pre, *q;
	L = new LNode;
	L->next = NULL;
	scanf("%d", &n);
	for (i = 0; i<n; i++)
	{
		p = new LNode;
		scanf("%d%d", &p->data.coef, &p->data.exp);
		pre = L; q = L->next;
		while (q&&q->data.exp<p->data.exp)
		{
			pre = q; q = q->next;
		}
		p->next = q; pre->next = p;
	}
	return OK;
}
void AddPolyn(LinkList& pa, LinkList& pb)
{
	LNode*p1, *p2, *p3, *q;
	int coef;
	p1 = pa->next; p2 = pb->next; p3 = pa;
	while (p1&&p2)
	{
		if (p1->data.exp == p2->data.exp)
		{
			coef = p1->data.coef + p2->data.coef;
			if (coef != 0)
			{
				p1->data.coef = coef;
				p3->next = p1; p3 = p1;
				p1 = p1->next;
				q = p2; p2 = p2->next; delete q;
			}
			else
			{
				q = p1; p1 = p1->next; delete q;
				q = p2; p2 = p2->next; delete q;
			}
		}
		else if (p1->data.exp<p2->data.exp)
		{
			p3->next = p1; p3 = p1; p1 = p1->next;
		}
		else
		{
			p3->next = p2; p3 = p2; p2 = p2->next;
		}
	}
	p3->next = p1 ? p1 : p2;
	delete pb;
}
Status TraverseList(LinkList& L)
{
	LNode*p = L->next;
	while (p)
	{
		if (p->next == NULL)
			printf("%dx^%d", p->data.coef, p->data.exp);
		else
			printf("%dx^%d+", p->data.coef, p->data.exp);
		p = p->next;
	}
	printf("\n");
	return OK;
}
int main()
{
	LinkList A, B;
	GreateList(A); TraverseList(A);
	GreateList(B); TraverseList(B);
	AddPolyn(A, B);
	TraverseList(A);
	return 0;
}













