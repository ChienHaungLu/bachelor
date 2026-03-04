#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	char str;
	int num, tmp, sum = 0;

	printf("Input your digit: ");
	scanf("%d", &num);

	while (num != 0) //判斷數字是否讀取完畢
	{
		str = (num % 10) + '0'; //將(LSB -> MSB)之每一位數字轉ASCII存放
		tmp = str - '0'; //(LSB -> MSB)之每一位轉為數值化過程
		printf("each digit: %d\n", (num % 10));
		sum = sum + tmp;
		num = num / 10; //換下一位數(由LSB -> MSB 移動)
	}

	printf("\nSum of thenumeric values of the digits is %d !\n\n", sum);
	system("PAUSE");
	return 0;
}