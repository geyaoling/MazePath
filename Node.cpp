#include"Node.h"

Status MakeNode(LinkType& p, ElemType e) {
	//����ռ�
	p = new NodeType;
	if (p)
	{
		//��������ֵ
		p->data = e;
		p->next = nullptr;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//�ͷŽ��
void FreeNode(LinkType& p) {
	delete p;
}