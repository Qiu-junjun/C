#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2
#define EASY_COUNT 10
#define win ROW*COL-EASY_COUNT
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
void InitBoard(char board[ROWS][COLS],int rows,int cols,char set);
void DisplayBoard(char board[ROWS][COLS],int row,int col);
void SetMine(char board[ROWS][COLS],int row,int col);
void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col);
int get_mine_count(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);
void UpdateShow(char mine[ROWS][COLS], char show[ROWS][COLS], int x, int y);
void ProShow(char show[ROWS][COLS],int row,int col);
void CountWin(char show[ROWS][COLS], int row,int col,int* num);