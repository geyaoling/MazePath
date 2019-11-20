#pragma once
#include"Constant.h"

// 坐标位置类型
typedef struct {
	int r, c;  //迷宫中r行c列的位置
}PosType;

typedef struct {
	int step;          //当前位置在路径上的“序号”
	PosType seat;      //当前的坐标位置
	directiveType di;  //往下一坐标位置的方向
}ElemType;             //栈的元素类型
//结点
typedef struct NodeType {
	ElemType data;
	NodeType* next;
}NodeType, * LinkType;    //结点类型，指针类型

//生成结点
Status MakeNode(LinkType& p, ElemType e);

//释放结点
void FreeNode(LinkType& p);
