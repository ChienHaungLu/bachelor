#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include<stdio.h>
#define MAX 8

void print_maze_sol(int maze_sol[MAX][MAX]) /* 印出迷宮 */
{
	printf("The maze solution: \n\n");
	for (int i = 0; i < MAX; i++)
	{
		for (int j = 0; j < MAX; j++)
		{
			printf("%2d", maze_sol[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int isExist(char maze[MAX][MAX], int x, int y) /* 判斷路徑是否合乎條件 */
{
	if (x >= 0 && x < MAX && y >= 0 && y < MAX && maze[x][y] == ' ') 
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

int solve_maze_path(char maze[MAX][MAX], int x, int y, int maze_sol[MAX][MAX])
{
	if (x == MAX - 1 && y == MAX - 1) /* 終點(7,7) */
	{
		maze_sol[x][y] = 1;
		return 1;
	}
	if (isExist(maze, x, y) == 1)
	{
		maze_sol[x][y] = 1; /* 當前位置有效就考慮為路徑 */
		
		if (solve_maze_path(maze, x + 1, y, maze_sol) == 1) /* x先疊代找路徑 */
			return 1;
		
		if (solve_maze_path(maze, x, y + 1, maze_sol) == 1) /* 找不到x的路徑才從y方向找路徑 */
			return 1;

		maze_sol[x][y] = 0;/* 以上路徑都找不到可走的 */
		return 0; 
 	}
	return 0;
}

int solve_maze(char maze[MAX][MAX]) /* 迷宮解決辦法 */
{
	int maze_sol[MAX][MAX] = {  { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
								{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
								{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
								{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
								{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
								{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
								{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
								{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } };

	if (solve_maze_path(maze,0,1,maze_sol) == 0) /* 路徑都找不到代表不存在可以走到終點的路徑 */
	{
		printf("The maze path does not exist!");
		return 0;
	}
	print_maze_sol(maze_sol);
	return 1;
}

int main()
{
	char maze[MAX][MAX] = { {'X' , ' ' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X'},
							{'X' , ' ' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X'},
							{'X' , ' ' , ' ' , ' ' , 'X' , 'X' , 'X' , 'X'},
							{'X' , 'X' , 'X' , ' ' , 'X' , ' ' , 'X' , 'X'},
							{'X' , 'X' , 'X' , ' ' , 'X' , ' ' , 'X' , 'X'},
							{'X' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , 'X'},
							{'X' , ' ' , 'X' , 'X' , 'X' , 'X' , ' ' , ' '},
							{'X' , 'X' , 'X' , 'X' , 'X' , 'X' , 'X' , ' '} };
	solve_maze(maze);
	return 0;
}