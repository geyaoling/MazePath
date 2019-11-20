#include "maze.h"
#include <iostream>
#include <fstream>

using namespace std;




//����ģ��
//��ʶ�߹���λ��
void FootPrint(MazeType& maze, PosType point) {
	maze.arr[point.r][point.c] = '-';
}

//�Բ���ͨ����λ�����±��
void MarkPrint(MazeType& maze, PosType point) {
	maze.arr[point.r][point.c] = '@';
}

//�ָ�ԭ״
void RenewPrint(MazeType& maze, PosType point) {
	maze.arr[point.r][point.c] = ' ';
}

//��ǰ�����Ƿ�ɴ�
bool Pass(MazeType maze, PosType point) {
	if (maze.arr[point.r][point.c] == ' ') {
		return true;
	}
	else
	{
		return false;
	}
}

//ȷ����һ����
PosType NextPos(PosType point, directiveType di) {
	switch (di)
	{
	case 1:
		//��һ������
		point.c++;
		break;
	case 2:
		//��һ��������
		point.r++;
		break;
	case 3:
		//��һ��������
		point.c--;
		break;
	case 4:
		//��һ������
		point.r--;
		break;
	}
	return point;
}

//�ж��Ƿ��ѵ������
Status Same(PosType start, PosType end) {
	//�ж��������Ƿ�һ�� �����ıȽ�
	if (start.r == end.r && start.c == end.c) {
		//һ�����ѵ������
		return TRUE;
	}
	else
	{
		//������δ�������
		return FALSE;
	}
}

//��ʼ���Թ��ĳ�ֵ
void InitMaze(MazeType& maze, int a[][N], int row, int col) {
	ClearMaze(maze);  //�����ͼ
	maze.m = row;
	maze.n = col;
	//���Թ�maze���ó�ֵ ����Χ��Χǽ
	for (int i = 0; i < row + 2; i++) {
		for (int j = 0; j < col + 2; j++) {
			if (i == 0 || j == 0 || i == row + 1 || j == col + 1) {
				//��Χǽ��ֵ'#'
				maze.arr[i][j] = '#';
			}
			else {
				//�������鸳ֵΪ����������
				if (a[i-1][j-1] == 0) {
					//���� �ÿո��ʾ����
					maze.arr[i][j] = ' ';
				}
				else {
					//�ϰ�
					maze.arr[i][j] = '#';
				}

			}
		}
	}
	
}


//����Թ�·��  ���һ��
bool MazePathOne(MazeType& maze, PosType start, PosType end,Stack &S) {
	//���Թ�maze�д��ڴ����start������end��ͨ���������һ�������ջ��
	//��ʼ��ջ
	InitStack(S);
	//��ǰλ�� �趨��ǰλ��Ϊ���λ��
	PosType curpos = start;
	//��¼·���ĳ���
	int curstep = 1;
	//�ȼٶ�û���Թ�·��
	Status found = FALSE;
	ElemType e;

	//̽����һ��
	do {
		if (Pass(maze, curpos)) {
			//��ǰλ�ÿ���ͨ�� ���Ϊ��*��  ��ʾ�Ѿ��߹�
			FootPrint(maze, curpos);
			//��eԪ�ش洢��λ�� �Ա����ջ��
			e.step = curstep;
			e.seat = curpos;
			e.di = 1;
			//����ջ��
			Push(S, e);
			//�ж��Ƿ񵽴�·��
			if (Same(curpos, end)) {
				found = TRUE;
			}
			else {
				curpos = NextPos(curpos, 1);         //��һλ���ǵ�ǰλ�õĶ��� Ĭ��������
				curstep++;                           //·�����ȼ�һ
			}
		}
		else {
			//��ǰλ�ò���ͨ��
			//�ж�ջ�Ƿ�Ϊ��
			if (!StackEmpty(S)) {
				//��Ϊ��
				//������ͨ�����Ǹ�λ��ɾ����·��
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)) {
					//��ʶ��·��ͨ
					MarkPrint(maze, e.seat);
					//����һ��
					Pop(S, e);
					//�˻�һ��
					curstep--;
				}
				//������
				if (e.di < 4) {
					e.di++;
					//������ͨ�� ����·��
					Push(S, e);
					//�ѵ�ǰ����λ�ú�di����ȥ
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!StackEmpty(S) && !found);   //ѭ���������Ǵ��·����ջ��Ϊ�� ��·����û�ҵ�

	//ѭ������ ���������
	return found;
}

//�����ϴ��������Ķ��������·�� �����·��
bool MazePathAll2(MazeType& maze, PosType start, PosType end) {
	//���Թ�maze�д��ڴ����start������end��ͨ���������һ�������ջ��
	//��ʼ��ջ
	Stack S;
	InitStack(S);
	//��ǰλ�� �趨��ǰλ��Ϊ���λ��
	PosType curpos = start;
	//�ȼٶ�û���Թ�·��
	Status found = FALSE;
	ElemType e;
	int minPathNum = 100;
	int count = 1;
	int minPath = 0;
	//̽����һ��
	do {
		if (Pass(maze, curpos)) {
			//��ǰλ�ÿ���ͨ�� ���Ϊ��*��  ��ʾ�Ѿ��߹�
			FootPrint(maze, curpos);
			//��eԪ�ش洢��λ�� �Ա����ջ��
			e.seat = curpos;
			e.di = 1;
			//����ջ��
			Push(S, e);
			//�ж��Ƿ񵽴�·��
			if (Same(curpos, end)) {
				found = TRUE;

				//�������
			//�ж��Ƿ��ǵ�ǰ����С·��
				if (S.size < minPathNum) {
					//�ǵĻ� �����ǵڼ��� �Լ�·������
					minPathNum = S.size;
					minPath = count;
				}
				//���
				cout << "·��" << count++ << "Ϊ��" << endl;
				StackTraverse(S);
				cout << "\n";

				//�ָ�Ϊ����
				RenewPrint(maze, e.seat);
				//Ȼ���ջ ��ջ��ֵ������e��
				Pop(S, e);

				//���浱ǰջ��ֵ �ж�
				curpos = S.top->data.seat;
			}
			else {
				curpos = NextPos(curpos, S.top->data.di);         //��һλ���ǵ�ǰλ�õĶ��� Ĭ��������
			}
		}
		else {
			//��ǰλ�ò���ͨ��
			//�ж�ջ�Ƿ�Ϊ��
			if (!StackEmpty(S)) {
				//��Ϊ��
				//������ͨ�����Ǹ�λ��ɾ����·��
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)) {
					//�ָ�Ϊ����
					RenewPrint(maze, e.seat);
					//����һ��
					Pop(S, e);
				}
				//������
				if (e.di < 4) {
					e.di++;
					//������ͨ�� ����·��
					Push(S, e);
					//�ѵ�ǰ����λ�ú�di����ȥ
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!StackEmpty(S));   //ѭ���������Ǵ��·����ջ��Ϊ�� �Ա���ö���·��


	if (found) {
		cout << "\n";
		cout << "���Թ�����" << --count << "��·��" << endl;
		cout << "���·���ǵ�" << minPath << "��,����Ϊ" << minPathNum;
		return true;
	}
	else {
		return false;
	}
}

//���Թ�·�� ���� ��������·�� 
/*
bool MazePathAll(MazeType& maze, PosType start, PosType end) {
	//�������·�������ݷ� ��¼��ÿ��λ�õ�diȻ����� Ѱ���Ƿ�����������֮·
	Stack S;
	InitStack(S);
	//��ʱ�����洢
	ElemType e;
	PosType current;
	int di = 0;
	e.seat = start;
	e.di = 0;
	//��ʼ������ջ
	Push(S, e);
	//����߹�
	FootPrint(maze, e.seat);
	//�Ƿ�����һ���߷���
	bool find;
	//�Ƿ���·��
	bool isFound = false;
	//����С·�� �Ƚ�·�����ȵó�
	//�ڼ���·��
	int count = 1;
	//��С·���ĳ��ȴ�С
	int minPathNum = 100;
	//��С·���ǵڼ���
	int minPath = 0;

	while (!StackEmpty(S)) {
		current = S.top->data.seat;
		di = S.top->data.di;              //�ñ�����ջ��Ԫ��ֵ�������� Ȼ���ж�
		if (Same(current, end)) {
			isFound = true;
			//�������
			//�ж��Ƿ��ǵ�ǰ����С·��
			if (S.size < minPathNum) {
				//�ǵĻ� �����ǵڼ��� �Լ�·������
				minPathNum = S.size;
				minPath = count;
			}
			//���
			cout << "·��" << count++ << "Ϊ��" << endl;
			StackTraverse(S);
			
			
			cout << "\n";

			//�ָ�Ϊ����
			RenewPrint(maze, current);
			//Ȼ���ջ ��ջ��ֵ������e��
			Pop(S, e);

			//���浱ǰջ��ֵ �ж�
			current = S.top->data.seat;
			di = S.top->data.di;
		}
		find = false;
		//Ѱ����һ���߷���
		while (di < 4 && !find) {
			di++;
			e.seat = NextPos(current, di);
			//�ж���һ�����Ƿ����
			if (Pass(maze, e.seat)) {
				//����
				find = true;
			}
		}
		//���� 
		if (find) {
			//����ջ��Ԫ�ص�ǰdi��ֵ 
			S.top->data.di = di;
			//����һ���߷�����ջ
			e.di = 0;
			Push(S, e);
			//����߹�
			FootPrint(maze, e.seat);
		}
		else {
			//�ָ��ɿ��߷��� �Ա�����·�����ߵ���
			RenewPrint(maze, current);
			//�ĸ������������ �򽫵�ǰ�����ջ
			Pop(S, e);
		}
	}

	if (isFound) {
		cout << "\n";
		cout << "���Թ�����" << --count << "��·��" << endl;
		cout << "���·���ǵ�" << minPath << "��,����Ϊ" << minPathNum;
		return true;
	}
	else {
		return false;
	}


}
*/
//��ʾ������Թ�·��
void PrintMaze(MazeType S) {
	for (int i = 0; i < S.m + 2; i++) {
		for (int j = 0; j < S.n + 2; j++) {
			if (i != 0 && j != 0 && i != S.m + 1 && j != S.n + 1) {
				cout << S.arr[i][j] << " ";
			}
		}
		cout << endl;
	}
	//д���ļ�
	writeToFile(S);
}

//�����ͼ
void ClearMaze(MazeType& maze) {
	for (int i = 0; i <maze.m+2; i++)
	{
		for (int j = 0; j < maze.n+2; j++)
		{
			if (maze.arr[i][j] == '-' || maze.arr[i][j] == '@')
			{
				maze.arr[i][j] = ' ';
			}
		}

	}
}
//�ļ�����
void readFile(char* filename, int& row, int& col, int a[][N]) {
	ifstream infile;
	infile.open(filename);
	infile >> row;
	infile >> col;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			infile >> a[i][j];
		}
	}
	infile.close();
}

void writeToFile(MazeType S) {
	ofstream outfile;
	outfile.open("result.txt", ios::app);

	for (int i = 0; i < S.m + 2; i++) {
		for (int j = 0; j < S.n + 2; j++) {
			if (i != 0 && j != 0 && i != S.m + 1 && j != S.n + 1) {
				outfile << S.arr[i][j] << " ";
			}
		}
		outfile << "\n";
	}
	outfile.close();
}