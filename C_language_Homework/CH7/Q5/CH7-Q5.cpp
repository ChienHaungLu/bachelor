#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void computation_number(char str[])
{
	int odd = 0,
		even = 0,
		even_add_odd = 0,
		check_digit = 0;
	
	int len = strlen(str) / 2; /* 因為奇數跟偶數計算的位置各半 */

	for (int i = 0; i < len; i++)
	{
		odd = odd + int(str[i * 2] - '0');
		if (i == 5) /* 避免將最後一個位元(LSB)也算數偶數部分，因為它是檢查位元，故不列入 */
		{
			continue;
		}
		else
		{
			even = even + int(str[(i + 1) * 2 - 1] - '0');
		}
		
	}

	odd = odd * 3; /* step1 */
	even_add_odd = odd + even; /* step2 */

	if ((even_add_odd % 10) != 0) /* 取step2的值的個位數，若不為0，則用10減去後可得到check_digit */
	{
		check_digit = 10 - (even_add_odd % 10);
	}
	else
	{
		check_digit = 0;
	}

	if ((str[11] - '0') == check_digit) /* 若check_digit和條碼最後一位的檢查碼一致 */
	{
		printf("%s validated!\n", str);
	}
	else
	{
		printf("%s error in barcode!\n", str);
	}
	printf("step1 result: %d\n", odd);
	printf("step2 result: %d\n\n", even_add_odd);
}


int main()
{
	int in;
	char str[13];
	printf("有幾組欲輸入的資料: ");
	scanf("%d", &in);
	for (int i = 1; i <= in;i++)
	{
		printf("請輸入資料: "); /* 079400804501、024000162860、011110856807、051000138101 */
		scanf("%s", str);
		computation_number(str);
	}

	system("PAUSE");
	return 0;
}