#define _CRT_SECURE_NO_WARNINGS
#include"game.h"
void InitBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			board[i][j] = set;
		}
	}
}
void DisplayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 1;
	int j = 1;
	for (i = 0; i <= row; i++)
	{
		if (i == 1)
			printf(" %d ", i);
		else
			printf("%d ",i);
	}
	printf("\n");
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d  ", i);
		for (j = 1; j <= col; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}
void SetMine(char board[ROWS][COLS], int row, int col)
{
	int x = 0, y = 0;
	int count = 1;
	while (1)
	{
		if (count <= EASY_COUNT)
		{
			x = rand() % 9 + 1;
			y = rand() % 9 + 1;
			if (board[x][y] == '0')
			{
				board[x][y] = '1';
				count++;
			}
		}
		else
			break;
	}
}
int get_mine_count(char mine[ROWS][COLS], int x, int y)
{
	return (mine[x-1][y-1]+
		mine[x-1][y]+
		mine[x-1][y+1]+
		mine[x][y-1]+
		mine[x][y+1]+
		mine[x+1][y-1]+
		mine[x+1][y]+
		mine[x+1][y+1]-8*'0');
}
void UpdateShow(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y)
{
	show[x][y] = get_mine_count(mine, x, y) + '0';
	if (show[x][y] == '0')
	{
		if (x - 1 >= 1 && x - 1 <= ROW && y - 1 >= 1 && y - 1 <= COL && show[x-1][y-1] == '*')
		{
			UpdateShow(mine, show, x - 1, y - 1);
		}
		if (x - 1 >= 1 && x - 1 <= ROW && y >= 1 && y <= COL && show[x-1][y] == '*')
		{
			UpdateShow(mine, show, x - 1, y);
		}
		if (x - 1 >= 1 && x - 1 <= ROW && y + 1 >= 1 && y + 1 <= COL && show[x-1][y+1] == '*')
		{
			UpdateShow(mine, show, x - 1, y + 1);
		}
		if (x >= 1 && x <= ROW && y - 1 >= 1 && y - 1 <= COL && show[x][y-1] == '*')
		{
			UpdateShow(mine, show, x, y - 1);
		}
		if (x >= 1 && x <= ROW && y + 1 >= 1 && y + 1 <= COL && show[x][y+1] == '*')
		{
			UpdateShow(mine, show, x - 1, y - 1);
		}
		if (x + 1 >= 1 && x + 1 <= ROW && y - 1 >= 1 && y - 1 <= COL && show[x+1][y-1] == '*')
		{
			UpdateShow(mine, show, x + 1, y - 1);
		}
		if (x + 1 >= 1 && x + 1 <= ROW && y >= 1 && y <= COL && show[x+1][y] == '*')
		{
			UpdateShow(mine, show, x + 1, y);
		}
		if (x + 1 >= 1 && x + 1 <= ROW && y + 1 >= 1 && y + 1 <= COL && show[x+1][y+1] == '*')
		{
			UpdateShow(mine, show, x + 1, y + 1);
		}
	}
	
}
void ProShow(char show[ROWS][COLS], int row, int col)
{
	int i, j = 1;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (show[i][j] == '0')
				show[i][j] = ' ';
		}
	}
}
void CountWin(char show[ROWS][COLS], int row, int col, int* num)
{
	int i = 1, j = 1;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (show[i][j] != '*')
				*num = *num + 1;
		}
	}
}
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0, y = 0;
	int count = 0;
	int num = 0;
	while (num < win)
	{
		printf("请输入排查雷的坐标>");
		scanf("%d%d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				printf("很遗憾，你踩到雷了，被炸死了\n");
				DisplayBoard(mine, ROW, COL);
				break;
			}
			else
			{
				/*count = get_mine_count(mine, x, y);*/
				/*show[x][y] = '0' + count;*/
				UpdateShow(mine, show, x, y);
				ProShow(show, ROW, COL);
				CountWin(show, ROW, COL, &num);
				system("cls");
				DisplayBoard(show, ROW, COL);
			}
		}
		else
		{
			printf("坐标输入非法，请重新输入\n");
		}
	}
	if (num == win)
	{
		printf("恭喜你，扫雷成功\n");
		DisplayBoard(mine, ROW, COL);
		Sleep(3000);
		system("cls");
	}
}
