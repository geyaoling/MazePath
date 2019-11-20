#include <iostream>
#include "Stack.h"
using namespace std;
//ջ�Ļ�������
//��ʼ��ջ
void InitStack(Stack& S) {
	//��ʼ������SΪ��ջ
	S.top = NULL;
	S.size = 0;
}

//����ջ
void DestroyStack(Stack& S) {
	//����ջ�����ͷ���ռ�ռ�
	LinkType p = S.top;
	LinkType q = NULL;
	while (p)
	{
		//��ʱ����
		q = p;
		//�ͷ�
		//FreeNode(q);
		delete q;
		//�ƶ�ָ��
		p = p->next;
	}
}

//���ջ ������ջ��ͬ �������ͷ��ڴ�
void ClearStack(Stack& S) {
	//ͷָ����Ϊ��
	S.top = NULL;
	//���ȹ�0
	S.size = 0;
}

//����ջ�ĳ���
int StackLength(Stack S) {
	return S.size;
}

//�ж�ջ�Ƿ�Ϊ��
Status StackEmpty(Stack S) {
	//ͨ��ջ��ָ�����ջ�ĳ����ж�
	if (S.top == NULL) {
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//����ջ��Ԫ��
Status GetTop(Stack S, ElemType e) {
	//�ж��Ƿ�Ϊ��
	if (!StackEmpty(S)) {
		//��Ϊ���򷵻�Ԫ����ֵ
		e = S.top->data;
		return TRUE;
	}
	else
	{
		//���򷵻�FALSE
		return FALSE;
	}
}

//��ջ����
Status Push(Stack& S, ElemType e) {
	//����ռ�
	LinkType p = NULL;
	if (MakeNode(p, e)) {
		//ʹp��Ϊջ��Ԫ��
		p->next = S.top;
		//�޸�ջ��ָ��
		S.top = p;
		//ջ����+1
		S.size++;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//��ջ���� ����ջ��Ԫ�ش���
Status Pop(Stack& S, ElemType& e) {
	LinkType p = NULL;
	if (!StackEmpty(S)) {
		//����ջ��ָ���ֵ�Ա��ͷ�ջ���ռ�
		p = S.top;
		//����ջ��Ԫ�ص�ֵ
		e = S.top->data;
		//�޸�ջ��ָ��
		S.top = S.top->next;
		//ɾ��p
		delete p;
		S.size--;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


