#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

int list[10];

void swap(int* x, int* y) /* 做排序時會使用到的交換 */
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void selection_sort(int list[], int list_len)
{
	int min;
	for (int i = 0; i < list_len - 1; i++)
	{
		min = i; /* 將最左邊的元素先設最小值 */
		for (int j = i + 1; j < list_len; j++)
		{
			if (list[j] < list[min]) /* 若找到比當前還要小的元素值 */
			{ 
				min = j; /* 最小值之索引值換成剛剛找到的 */
			}
		}
		swap(&list[i], &list[min]); /* 將剛剛找到的最小元素值和次之的最小元素值進行互換 */
	}

	printf("\n資料排序後: ");
	for (int k = 0; k < list_len; k++)
	{
		printf("%3d", list[k]);
	}
	printf("\n");
}

int compare(int x, int y) /* x是傳入的中間值, y為欲搜尋的值 */
{
	if (x < y) /* y比x大，代表欲搜尋的元素在中間值的右方 */
	{
		return -1;
	}
	else if (x == y) /* y等於x，代表元素值和欲搜尋的值在同一位置上 */
	{
		return 0;
	}
	else /* y比x小，代表欲搜尋的元素在中間值的左方 */
	{
		return 1;
	}
}

int binsearch(int list[], int found, int bottom, int top) /* 二元搜尋疊代 */
{
	int middle;
	while (bottom <= top) /* bottom要在top的左邊 */
	{
		middle = (bottom + top) / 2; /* 找出中間索引值 */
		switch (compare(list[middle], found)) /* 欲搜尋的元素值在中間元素的哪邊 */
		{
		case -1:
			bottom = middle + 1; /* 欲搜尋的值在中間值右方，故左邊界往右移動 */
			break;

		case 0: 
			return middle; /* 找到該元素就回傳其array index */
			break;

		case 1:
			top = middle - 1; /* 欲搜尋的值在中間值左方，故右邊界往左移動 */
			break;
		}
	}
	return -1; /* 找不到該元素就回傳-1 */
} 

int main()
{
	int list_len = 0,
		found = 0, /* 欲搜尋的元素 */
		bottom = 0, /* 左邊界 */
		top = 0; /* 右邊界 */

	/*Input example1: 2 4 6 8 10 1 3 5 7 9 */
	/*Input example2: 87 69 12 23 66 35 96 46 45 37 */

	printf("Input ten number: "); /* 只能輸入10筆資料 */
	for (int i = 0; i < 10; i++)
	{
		scanf("%d", &list[i]);
		list_len = i + 1;
	}
	top = list_len - 1; /* 獲取右邊界的值 */

	printf("輸入欲搜尋的值: ");
	scanf("%d", &found);

	selection_sort(list, list_len); /* 先將輸入的資料進行排序 */

	if (binsearch(list, found, bottom, top) != -1) /* 假若回傳的值不為-1 */
	{
		printf("\n欲搜尋的元素[%d]存在於所輸入的資料中\n", found);
		printf("欲搜尋的元素[%d]位置為: %d\n\n", found, binsearch(list, found, bottom, top) + 1);
	}
	else /* 反之找不到該元素存在於輸入的資料中 */
	{
		printf("\n欲搜尋的元素[%d]不存在於所輸入的資料中\n\n", found);
	}
	

	return 0;
}