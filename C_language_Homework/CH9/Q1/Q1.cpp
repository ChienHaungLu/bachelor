#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>



int blob_check(int array[][5], int x, int y)
{
	int counter = 0;
	if (x < 0 || x>=5 || y < 0 || y>=5) /* 超出資料邊界就為0 */
	{
		return 0;
	}
	if(array[x][y] == 0) /* 該座標網格 */
	{
		return 0;
	}
	else
	{
		array[x][y] = 0; /* 避免重複計算 */
		counter += blob_check(array, x - 1, y - 1); /* 九宮格左上角 */
		counter += blob_check(array, x, y - 1); /* 九宮格上方 */
		counter += blob_check(array, x + 1, y - 1); /* 九宮格右上角 */
		counter += blob_check(array, x - 1, y); /* 九宮格之中心點左方 */
		counter += blob_check(array, x + 1, y); /* 九宮格之中心點右方 */
		counter += blob_check(array, x - 1, y + 1); /* 九宮格之中心點左下角 */
		counter += blob_check(array, x , y + 1); /* 九宮格之中心點下方 */
		counter += blob_check(array, x + 1, y + 1); /* 九宮格之中心點右下角 */
	}

	return counter+1;
}

int main()
{
	int x,y;
	int array[5][5];
	printf("輸入資料: ");			// 1 1 0 0 0
	for (int i = 0;i < 5;i++)		// 0 1 1 0 0
	{								// 0 0 1 0 1
		for (int j = 0;j < 5;j++)	// 1 0 0 0 1
		{							// 0 1 0 1 1
			scanf("%d", &array[i][j]);
		}
	}
	
	printf("請輸入xy座標: ");  /* 0~4 */
	scanf("%d %d",&x,&y);
	printf("座標(%d,%d)獲取的總數值為: %d\n\n",x,y,blob_check(array, x, y));
	
	return 0;
}