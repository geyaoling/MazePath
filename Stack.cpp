#include <iostream>
#include "Stack.h"
using namespace std;
//栈的基本操作
//初始化栈
void InitStack(Stack& S) {
	//初始化，设S为空栈
	S.top = NULL;
	S.size = 0;
}

//销毁栈
void DestroyStack(Stack& S) {
	//销毁栈，并释放所占空间
	LinkType p = S.top;
	LinkType q = NULL;
	while (p)
	{
		//临时保存
		q = p;
		//释放
		//FreeNode(q);
		delete q;
		//移动指针
		p = p->next;
	}
}

//清空栈 与销毁栈不同 销毁需释放内存
void ClearStack(Stack& S) {
	//头指针置为空
	S.top = NULL;
	//长度归0
	S.size = 0;
}

//返回栈的长度
int StackLength(Stack S) {
	return S.size;
}

//判断栈是否为空
Status StackEmpty(Stack S) {
	//通过栈顶指针或者栈的长度判断
	if (S.top == NULL) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//返回栈顶元素
Status GetTop(Stack S, ElemType e) {
	//判断是否为空
	if (!StackEmpty(S)) {
		//不为空则返回元素数值
		e = S.top->data;
		return TRUE;
	}
	else
	{
		//否则返回FALSE
		return FALSE;
	}
}

//入栈操作
Status Push(Stack& S, ElemType e) {
	//分配空间
	LinkType p = NULL;
	if (MakeNode(p, e)) {
		//使p成为栈顶元素
		p->next = S.top;
		//修改栈顶指针
		S.top = p;
		//栈长度+1
		S.size++;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//出栈操作 并将栈顶元素带出
Status Pop(Stack& S, ElemType& e) {
	LinkType p = NULL;
	if (!StackEmpty(S)) {
		//保存栈顶指针的值以便释放栈顶空间
		p = S.top;
		//保存栈顶元素的值
		e = S.top->data;
		//修改栈顶指针
		S.top = S.top->next;
		//删除p
		delete p;
		S.size--;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


