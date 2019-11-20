#pragma once
#include"Node.h"
typedef struct {
	LinkType top;
	int size;
}Stack;                 //栈类型

//初始化栈
void InitStack(Stack& S);

//销毁栈
void DestroyStack(Stack& S);

//清空栈 与销毁栈不同 销毁需释放内存
void ClearStack(Stack& S);

//返回栈的长度
int StackLength(Stack S);

//判断栈是否为空
Status StackEmpty(Stack S);


//返回栈顶元素
Status GetTop(Stack S, ElemType e);

//入栈操作
Status Push(Stack& S, ElemType e);

//出栈操作 并将栈顶元素带出
Status Pop(Stack& S, ElemType& e);

//输出栈的元素
void StackTraverse(Stack S);
