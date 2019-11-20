#include "maze.h"
#include <iostream>
#include <fstream>

using namespace std;




//方块模块
//标识走过的位置
void FootPrint(MazeType& maze, PosType point) {
	maze.arr[point.r][point.c] = '-';
}

//对不能通过的位置留下标记
void MarkPrint(MazeType& maze, PosType point) {
	maze.arr[point.r][point.c] = '@';
}

//恢复原状
void RenewPrint(MazeType& maze, PosType point) {
	maze.arr[point.r][point.c] = ' ';
}

//当前方块是否可达
bool Pass(MazeType maze, PosType point) {
	if (maze.arr[point.r][point.c] == ' ') {
		return true;
	}
	else
	{
		return false;
	}
}

//确定下一方块
PosType NextPos(PosType point, directiveType di) {
	switch (di)
	{
	case 1:
		//下一步向东走
		point.c++;
		break;
	case 2:
		//下一步向南走
		point.r++;
		break;
	case 3:
		//下一步向西走
		point.c--;
		break;
	case 4:
		//下一步向北走
		point.r--;
		break;
	}
	return point;
}

//判断是否已到达出口
Status Same(PosType start, PosType end) {
	//判断两坐标是否一致 分量的比较
	if (start.r == end.r && start.c == end.c) {
		//一致则已到达出口
		return TRUE;
	}
	else
	{
		//否则则未到达出口
		return FALSE;
	}
}

//初始化迷宫的初值
void InitMaze(MazeType& maze, int a[][N], int row, int col) {
	ClearMaze(maze);  //清理地图
	maze.m = row;
	maze.n = col;
	//给迷宫maze设置初值 最外围是围墙
	for (int i = 0; i < row + 2; i++) {
		for (int j = 0; j < col + 2; j++) {
			if (i == 0 || j == 0 || i == row + 1 || j == col + 1) {
				//给围墙赋值'#'
				maze.arr[i][j] = '#';
			}
			else {
				//其他方块赋值为所读到的数
				if (a[i-1][j-1] == 0) {
					//可走 用空格表示可走
					maze.arr[i][j] = ' ';
				}
				else {
					//障碍
					maze.arr[i][j] = '#';
				}

			}
		}
	}
	
}


//求解迷宫路径  求得一条
bool MazePathOne(MazeType& maze, PosType start, PosType end,Stack &S) {
	//若迷宫maze中存在从入口start到出口end的通道，则求得一条存放在栈中
	//初始化栈
	InitStack(S);
	//当前位置 设定当前位置为入口位置
	PosType curpos = start;
	//记录路径的长度
	int curstep = 1;
	//先假定没有迷宫路径
	Status found = FALSE;
	ElemType e;

	//探索第一步
	do {
		if (Pass(maze, curpos)) {
			//当前位置可以通过 标记为“*”  表示已经走过
			FootPrint(maze, curpos);
			//用e元素存储该位置 以便加入栈中
			e.step = curstep;
			e.seat = curpos;
			e.di = 1;
			//加入栈中
			Push(S, e);
			//判断是否到达路径
			if (Same(curpos, end)) {
				found = TRUE;
			}
			else {
				curpos = NextPos(curpos, 1);         //下一位置是当前位置的东邻 默认先向东行
				curstep++;                           //路径长度加一
			}
		}
		else {
			//当前位置不能通过
			//判断栈是否为空
			if (!StackEmpty(S)) {
				//不为空
				//将不能通过的那个位置删除出路径
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)) {
					//标识此路不通
					MarkPrint(maze, e.seat);
					//回退一步
					Pop(S, e);
					//退回一步
					curstep--;
				}
				//换方向
				if (e.di < 4) {
					e.di++;
					//假设能通过 加入路径
					Push(S, e);
					//把当前坐标位置和di传过去
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!StackEmpty(S) && !found);   //循环的条件是存放路径的栈不为空 且路径还没找到

	//循环结束 将结果返回
	return found;
}

//对书上代码稍作改动求得所有路径 及最短路径
bool MazePathAll2(MazeType& maze, PosType start, PosType end) {
	//若迷宫maze中存在从入口start到出口end的通道，则求得一条存放在栈中
	//初始化栈
	Stack S;
	InitStack(S);
	//当前位置 设定当前位置为入口位置
	PosType curpos = start;
	//先假定没有迷宫路径
	Status found = FALSE;
	ElemType e;
	int minPathNum = 100;
	int count = 1;
	int minPath = 0;
	//探索第一步
	do {
		if (Pass(maze, curpos)) {
			//当前位置可以通过 标记为“*”  表示已经走过
			FootPrint(maze, curpos);
			//用e元素存储该位置 以便加入栈中
			e.seat = curpos;
			e.di = 1;
			//加入栈中
			Push(S, e);
			//判断是否到达路径
			if (Same(curpos, end)) {
				found = TRUE;

				//到达出口
			//判断是否是当前的最小路径
				if (S.size < minPathNum) {
					//是的话 保存是第几条 以及路径长度
					minPathNum = S.size;
					minPath = count;
				}
				//输出
				cout << "路径" << count++ << "为：" << endl;
				StackTraverse(S);
				cout << "\n";

				//恢复为可走
				RenewPrint(maze, e.seat);
				//然后出栈 将栈顶值保存在e中
				Pop(S, e);

				//保存当前栈顶值 判断
				curpos = S.top->data.seat;
			}
			else {
				curpos = NextPos(curpos, S.top->data.di);         //下一位置是当前位置的东邻 默认先向东行
			}
		}
		else {
			//当前位置不能通过
			//判断栈是否为空
			if (!StackEmpty(S)) {
				//不为空
				//将不能通过的那个位置删除出路径
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S)) {
					//恢复为可走
					RenewPrint(maze, e.seat);
					//回退一步
					Pop(S, e);
				}
				//换方向
				if (e.di < 4) {
					e.di++;
					//假设能通过 加入路径
					Push(S, e);
					//把当前坐标位置和di传过去
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!StackEmpty(S));   //循环的条件是存放路径的栈不为空 以便求得多条路径


	if (found) {
		cout << "\n";
		cout << "该迷宫共有" << --count << "条路径" << endl;
		cout << "最短路径是第" << minPath << "条,长度为" << minPathNum;
		return true;
	}
	else {
		return false;
	}
}

//求迷宫路径 所有 并求出最短路径 
/*
bool MazePathAll(MazeType& maze, PosType start, PosType end) {
	//求得所有路径：回溯法 记录下每个位置的di然后回溯 寻找是否有其他可走之路
	Stack S;
	InitStack(S);
	//临时变量存储
	ElemType e;
	PosType current;
	int di = 0;
	e.seat = start;
	e.di = 0;
	//起始点先入栈
	Push(S, e);
	//标记走过
	FootPrint(maze, e.seat);
	//是否有下一可走方块
	bool find;
	//是否有路径
	bool isFound = false;
	//求最小路径 比较路径长度得出
	//第几条路径
	int count = 1;
	//最小路径的长度大小
	int minPathNum = 100;
	//最小路径是第几条
	int minPath = 0;

	while (!StackEmpty(S)) {
		current = S.top->data.seat;
		di = S.top->data.di;              //用变量将栈顶元素值保存起来 然后判断
		if (Same(current, end)) {
			isFound = true;
			//到达出口
			//判断是否是当前的最小路径
			if (S.size < minPathNum) {
				//是的话 保存是第几条 以及路径长度
				minPathNum = S.size;
				minPath = count;
			}
			//输出
			cout << "路径" << count++ << "为：" << endl;
			StackTraverse(S);
			
			
			cout << "\n";

			//恢复为可走
			RenewPrint(maze, current);
			//然后出栈 将栈顶值保存在e中
			Pop(S, e);

			//保存当前栈顶值 判断
			current = S.top->data.seat;
			di = S.top->data.di;
		}
		find = false;
		//寻找下一可走方块
		while (di < 4 && !find) {
			di++;
			e.seat = NextPos(current, di);
			//判断下一方块是否可走
			if (Pass(maze, e.seat)) {
				//可走
				find = true;
			}
		}
		//可走 
		if (find) {
			//保存栈顶元素当前di的值 
			S.top->data.di = di;
			//将下一可走方块入栈
			e.di = 0;
			Push(S, e);
			//标记走过
			FootPrint(maze, e.seat);
		}
		else {
			//恢复成可走方块 以便其他路径可走到这
			RenewPrint(maze, current);
			//四个方向均不可走 则将当前方块出栈
			Pop(S, e);
		}
	}

	if (isFound) {
		cout << "\n";
		cout << "该迷宫共有" << --count << "条路径" << endl;
		cout << "最短路径是第" << minPath << "条,长度为" << minPathNum;
		return true;
	}
	else {
		return false;
	}


}
*/
//显示求解后的迷宫路径
void PrintMaze(MazeType S) {
	for (int i = 0; i < S.m + 2; i++) {
		for (int j = 0; j < S.n + 2; j++) {
			if (i != 0 && j != 0 && i != S.m + 1 && j != S.n + 1) {
				cout << S.arr[i][j] << " ";
			}
		}
		cout << endl;
	}
	//写入文件
	writeToFile(S);
}

//清理地图
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
//文件操作
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