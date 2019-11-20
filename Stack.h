#pragma once
#include"Node.h"
typedef struct {
	LinkType top;
	int size;
}Stack;                 //ջ����

//��ʼ��ջ
void InitStack(Stack& S);

//����ջ
void DestroyStack(Stack& S);

//���ջ ������ջ��ͬ �������ͷ��ڴ�
void ClearStack(Stack& S);

//����ջ�ĳ���
int StackLength(Stack S);

//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(Stack S);


//����ջ��Ԫ��
Status GetTop(Stack S, ElemType e);

//��ջ����
Status Push(Stack& S, ElemType e);

//��ջ���� ����ջ��Ԫ�ش���
Status Pop(Stack& S, ElemType& e);

//���ջ��Ԫ��
void StackTraverse(Stack S);
