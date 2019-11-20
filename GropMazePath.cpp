// GropMazePath.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <string>
#include <time.h>


using namespace std;
int Miss = 0;
MazeType maze;
Stack S;
//坐标
void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

}
//获取当前坐标
PosType getxy() {
	PosType c;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { 0, 0 }; //光标位置
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		c.c = csbi.dwCursorPosition.X;
		c.r = csbi.dwCursorPosition.Y;
		
	}
	return c;
}
//设置颜色
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}

void PrintMaze(MazeType maze, int x, int y) {
	for (int i = 0; i < maze.m+2; i++)
	{
		for (int j = 0; j < maze.n+2; j++) {
			cout << maze.arr[i][j];
		}
		gotoxy(x, y + i + 1);
	}

}
void PrintRectangMaze(MazeType maze, int x, int y) {
	for (int i = 0; i < maze.m + 2; i++)
	{
		for (int j = 0; j < maze.n + 2; j++) {
			if (maze.arr[i][j] == '#')
			{
				cout << "▓";
			}
			else if (maze.arr[i][j] == '-')
			{
				cout << "☆";
			}
			else if (maze.arr[i][j] == '@')
			{
				cout << "〓";
			}
			
			else
			{
				cout <<"  ";
			}
		}
		gotoxy(x, y + i + 1);
	}
}
//打印外观
void PrintBox() {

	color(3);
	gotoxy(5, 3);
	cout << "::";
	for (int i = 1; i < 106; i++) {
		cout << "=";
	}
	cout << "::";
	gotoxy(5, 4);
	for (int i = 0; i < 20; i++) {
		cout << "::";
		for (int j = 0; j < 105; j++) {
			cout << ' ';
		}
		cout << "::";
		gotoxy(5, i + 5);
	}

	gotoxy(7, 6);
	for (int i = 0; i < 105; i++)
	{
		cout << "-";
	}

	gotoxy(5, 23);
	cout << "::";
	for (int i = 0; i < 105; i++) {
		cout << "-";
	}
	cout << "::";
	color(11);
	gotoxy(50, 1);
	cout << "迷     宫";
	gotoxy(36, 4);
	cout << "******  操  作  提  示  ******";
	gotoxy(8, 5);
	cout << "1.CreatMaze    -c    2.MazePath    -m     3.AllMazePath    -a     4.PrintMaze    -p     5.Quit    -q";


	color(9);
	if (Miss == 1) {
		gotoxy(28, 12); color(2);
		cout << "输入操作有误，请重新操作！" << endl;
		Miss = 0;
	}
	gotoxy(50, 15); color(1);
	cout << "请输入操作:( )";

}
//转换页
void NextBox() {
	gotoxy(11, 3);
	color(1);
	for (int i = 0; i < 90; i++)
	{
		cout << "_";
	}
	gotoxy(11, 4);
	for (int i = 0; i < 20; i++)
	{
		cout << "|";

		gotoxy(11, 5 + i);
	}
	gotoxy(100, 4);
	for (int i = 0; i < 20; i++)
	{
		cout << "|";
		gotoxy(100, 5 + i);
	}
	gotoxy(11, 24);
	for (int i = 0; i < 90; i++)
	{
		cout << "-";
	}
	color(9);
}
//初始化界面

//求迷宫路径 所有 并求出最短路径 
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
			gotoxy(20, getxy().r + 1);
			cout << "路径" << count++ << "为：" ;
			gotoxy(20, getxy().r + 1);
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
		gotoxy(20, getxy().r + 1);
		cout << "该迷宫共有" << --count << "条路径" ;
		gotoxy(20, getxy().r + 1);
		cout << "最短路径是第" << minPath << "条,长度为" << minPathNum;
		return true;
	}
	else {
		return false;
	}


}
//输出某指针所指元素的值
void MyPrint(LinkType p,int num) {
	num++;
	if (p->next)
	{
		MyPrint(p->next,num);
		if (num%10 == 0)
		{
			gotoxy(20, getxy().r + 1);
		}
		cout << "(" << p->data.seat.r << "," << p->data.seat.c << ")" << " ";
	}
	else
	{   
		cout << "(" << p->data.seat.r << "," << p->data.seat.c << ")" << " ";
	}

}

//输出栈的元素 反序输出
void StackTraverse(Stack S) {
	LinkType p = S.top;
	int num = 0;
	MyPrint(p,num);
}

int Initialization() {
	PrintBox();
	return 0;
}
void ReadCommand(char &cmd) {
	color(4);
	gotoxy(62, 15);
	cmd = getchar();
	getchar();

}
void Interpret(char cmd) {
	char filename[10] = {};
	int m, n;
	int a[N][N] = {};
	PosType from, term;
	system("cls");
	NextBox();
	//解释执行操作命令
	switch (cmd) {
	case 'c':  
		//提示用户输入“迷宫数据的文件名“filename”
		//从文件读入数据
		gotoxy(20, 5);
		cout << "可使用的文件有： 1.m1.txt    2.m2.txt    3.m3.txt    4.m4.txt";
		gotoxy(20, 7);
		cout << "请输入想读取的文件名：";
		cin >> filename;
		readFile(filename, m, n, a);
		//初始化迷宫
		InitMaze(maze, a, m, n);
		gotoxy(20,9);
		if (maze.arr != NULL)
		{   
			cout << "迷宫创建完毕！迷宫为：";
			gotoxy(70, 11);
			PrintRectangMaze(maze, 70, 11);
		}
		else
		{
			cout << "迷宫创建失败！请重新创建！";
		}
		getchar();
		gotoxy(20, 11 + maze.m);
		cout << "按任意键继续！";
		getchar();
		break;
	case 'm':
		//提示用户输入迷宫的入口from和出口term的坐标位置
		
		ClearMaze(maze);
		while (true)
		{
			gotoxy(20, 10); cout << "请输入入口位置:(坐标间用空格隔开)";  cin >> from.r >> from.c;
			gotoxy(20, 12); cout << "请输入出口位置:(坐标间用空格隔开)";  cin >> term.r >> term.c;
			gotoxy(20, 14);
			if (MazePathOne(maze, from, term,S)) {
				cout << "路径查询完成，返回即可查看！" << endl;
				break;
			}
			else {
				system("cls");
				NextBox(); gotoxy(20, 8);
				cout << "该迷宫无路径可出！请重新定义出入口！" << endl;
			}
		}
		gotoxy(20, 20);
		getchar();
		cout << "按任意键继续！";
		getchar();
		break;
	case 'a':
		//提示用户输入迷宫的入口from和出口term的坐标位置
		system("cls");
		ClearMaze(maze);
		while (true)
		{
			gotoxy(20, 6); cout << "请输入入口位置:(坐标间用空格隔开)";  cin >> from.r >> from.c;
			gotoxy(20,8); cout << "请输入出口位置:(坐标间用空格隔开)";  cin >> term.r >> term.c;
			gotoxy(20,10);
			if (MazePathAll(maze, from, term)) {
				cout << "全部路径查询完成，返回即可查看！" << endl;
				break;
			}
			else {
				system("cls");
				NextBox(); gotoxy(20, 5);
				cout << "该迷宫无路径可出！请重新定义出入口！" << endl;
			}
		}
		gotoxy(20, getxy().r+3);
		getchar();
		cout << "按任意键继续！";
		getchar();
		break;
		
	case 'p':
		gotoxy(20, 8);  cout << "迷宫路径为：";
		gotoxy(20, 10); PrintRectangMaze(maze, 20, 10);
		gotoxy(20, getxy().r + 2);
		cout << "最短路径为：";
		gotoxy(20, getxy().r + 1);
		StackTraverse(S);
		gotoxy(20, 20);
		cout << "按任意键继续！";
		getchar();
		break;
	case 'q':
		break;
	default:
		Miss = 1;   //错误警告
		break;
	}
	system("cls");
}
int main()
{   
	char cmd;
	do {
		Initialization();   //初始化
		ReadCommand(cmd);  //读入一个操作命令
		Interpret(cmd);     //解释操作命令符

	} while (cmd!='q');
	PrintBox();            //结束
	gotoxy(40, 21); color(2);
	cout << "操作结束，感谢使用！" << endl;
	gotoxy(10, 25);
	
}



