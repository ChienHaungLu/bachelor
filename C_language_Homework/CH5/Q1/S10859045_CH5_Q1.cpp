#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h> //用於字串計算長度

int main()
{
	int num,tmp, count = 0;
	printf("Input your number: ");
	scanf("%d", &num);
	tmp = num;
	if ((num % 9) == 0) //判斷能不能被9整除
	{
		printf("\n輸入的數字 %d 可以被9整除\n\n", num);

	}
	else
	{
		printf("\n輸入的數字 %d 無法被9整除\n\n", num);
	}
	while (num != 0) //判斷幾位數
	{
		tmp = num % 10; //從個位數往十位數移動...
		++count;  //用於計算位數
		printf("從右邊往左數過來第%d數字為:%d\n",count,tmp);
		num = num / 10;
	}
	printf("\n");
	system("PAUSE");
	return 0;
}