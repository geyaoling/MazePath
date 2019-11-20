#pragma once
#include "Stack.h"

typedef struct {
	int m, n;
	char arr[RANGE][RANGE];    //��λ��ȡֵ�� ������#������@������*��
}MazeType;


//��ʶ�߹���λ��
void FootPrint(MazeType& maze, PosType point);

//�Բ���ͨ����λ�����±��
void MarkPrint(MazeType& maze, PosType point);

//��ǰ�����Ƿ�ɴ�
bool Pass(MazeType maze, PosType point);

//ȷ����һ����
PosType NextPos(PosType point, directiveType di);

//ȷ����һ����
PosType NextPos(PosType point, directiveType di);

//�ж��Ƿ��ѵ������
Status Same(PosType start, PosType end);
//�Թ�ģ��



//��ʼ���Թ��ĳ�ֵ
void InitMaze(MazeType& maze, int a[][N], int row, int col);

//����Թ�·��  ���һ��
bool MazePathOne(MazeType& maze, PosType start, PosType end,Stack &S);

//���Թ�·�� ���� 
//bool MazePathAll(MazeType& maze, PosType start, PosType end);
bool MazePathAll2(MazeType& maze, PosType start, PosType end);
void RenewPrint(MazeType& maze, PosType point);
//��ʾ������Թ�·��
void PrintMaze(MazeType S);

void ClearMaze(MazeType& maze);

//��ȡ�ļ�
void readFile(char* filename, int& row, int& col, int a[][N]);
//д���ļ�
void writeToFile(MazeType S);