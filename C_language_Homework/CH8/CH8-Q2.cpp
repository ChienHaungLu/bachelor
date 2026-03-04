#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char COLOR_CODES[10][7] = { "black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "gray", "white" };
char band1[7], band2[7], band3[7]; /* 將字串裡面的每個字元存放至字元陣列 */

void comparsion_and_calculated(char band1[], char band2[], char band3[], char COLOR_CODES[10][7])
{
	int result_comparsion1 = 1,
		result_comparsion2 = 1,
		result_comparsion3 = 1,
		idx1 = 0,
		idx2 = 0,
		idx3 = 0,
		resistance_value = 0;

	for (int i = 0; i < 10; ++i)
	{
		if (strcmp(band1, COLOR_CODES[i]) == 0) /* 比對相同 */
		{
			idx1 = i;
			result_comparsion1 = 0;
		}
		if (strcmp(band2, COLOR_CODES[i]) == 0) /* 比對相同 */
		{
			idx2 = i;
			result_comparsion2 = 0;
		}
		if (strcmp(band3, COLOR_CODES[i]) == 0) /* 比對相同 */
		{
			idx3 = i;
			result_comparsion3 = 0;
		}
	}

	if (result_comparsion1 == 1) /* 比對不同會顯示錯誤輸入的色環名稱 */
	{
		printf("Invalid color: %s\n", band1);
	}
	else if (result_comparsion2 == 1)
	{
		printf("Invalid color: %s\n", band2);
	}
	else if (result_comparsion3 == 1)
	{
		printf("Invalid color: %s\n", band3);
	}
	else /* 比對相同才會開始計算電阻值 */
	{
		/* 第一還為十位數字，第二環為個位數字，第三環乘法的值 */
		resistance_value = (idx1 * pow(10,1) + idx2) * pow(10, idx3) / 1000;  /* 除1000是為了保持 kilo-ohms單位 */
		printf("Resistance value: %d kilo-ohms\n", resistance_value);
	}
}

int main()
{
	int idx = 1;
	char condition[2];

	printf("Enter the colors of the resistor's three bands, beginning with the band nearest the end.Type the colors in lowercase letters only, NO CAPS.\n\n");
	printf("Band 1 => ");
	scanf("%s", band1);
	printf("Band 2 => ");
	scanf("%s", band2);
	printf("Band 3 => ");
	scanf("%s", band3);
	comparsion_and_calculated(band1, band2, band3, COLOR_CODES); /* 比對色環和計算電阻值 */
	printf("Do you want to decode another resistor?(y/n)\n");
	printf("=>");
	scanf("%s",&condition);

	if (condition[0] == 'y' || condition[0] == 'Y') /* y || Y */
	{
		printf("\n\n");
		main(); /* 回到主函式再次執行所有敘述 */
	}
	return 0;
}