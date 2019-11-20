#pragma once
#include "Stack.h"

typedef struct {
	int m, n;
	char arr[RANGE][RANGE];    //各位置取值‘ ’，‘#’，‘@’，‘*’
}MazeType;


//标识走过的位置
void FootPrint(MazeType& maze, PosType point);

//对不能通过的位置留下标记
void MarkPrint(MazeType& maze, PosType point);

//当前方块是否可达
bool Pass(MazeType maze, PosType point);

//确定下一方块
PosType NextPos(PosType point, directiveType di);

//确定下一方块
PosType NextPos(PosType point, directiveType di);

//判断是否已到达出口
Status Same(PosType start, PosType end);
//迷宫模块



//初始化迷宫的初值
void InitMaze(MazeType& maze, int a[][N], int row, int col);

//求解迷宫路径  求得一条
bool MazePathOne(MazeType& maze, PosType start, PosType end,Stack &S);

//求迷宫路径 所有 
//bool MazePathAll(MazeType& maze, PosType start, PosType end);
bool MazePathAll2(MazeType& maze, PosType start, PosType end);
void RenewPrint(MazeType& maze, PosType point);
//显示求解后的迷宫路径
void PrintMaze(MazeType S);

void ClearMaze(MazeType& maze);

//读取文件
void readFile(char* filename, int& row, int& col, int a[][N]);
//写入文件
void writeToFile(MazeType S);