#pragma once
#include"Constant.h"

// ����λ������
typedef struct {
	int r, c;  //�Թ���r��c�е�λ��
}PosType;

typedef struct {
	int step;          //��ǰλ����·���ϵġ���š�
	PosType seat;      //��ǰ������λ��
	directiveType di;  //����һ����λ�õķ���
}ElemType;             //ջ��Ԫ������
//���
typedef struct NodeType {
	ElemType data;
	NodeType* next;
}NodeType, * LinkType;    //������ͣ�ָ������

//���ɽ��
Status MakeNode(LinkType& p, ElemType e);

//�ͷŽ��
void FreeNode(LinkType& p);
