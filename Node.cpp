#include"Node.h"

Status MakeNode(LinkType& p, ElemType e) {
	//分配空间
	p = new NodeType;
	if (p)
	{
		//给数据域赋值
		p->data = e;
		p->next = nullptr;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//释放结点
void FreeNode(LinkType& p) {
	delete p;
}