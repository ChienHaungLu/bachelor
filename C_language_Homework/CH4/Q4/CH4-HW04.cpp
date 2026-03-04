#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include<stdio.h>

int main()
{
	char color;
	printf("Input the a letter: "); //輸入字母判別顏色以便印出對應內容
	scanf("%c", &color);

	switch (color)
	{
		case 'O': case 'o':
			printf("The letter %c color is orange and the contents of a compressed-gas cylinder is ammonia\n\n", color);
			break;

		case 'B': case 'b':
			printf("The letter %c color is brown and the contents of a compressed-gas cylinder is carbon monoxide\n\n", color);
			break;

		case 'Y': case 'y':
			printf("The letter %c color is yellow and the contents of a compressed-gas cylinder is hydrogen\n\n", color);
			break;

		case 'G': case 'g':
			printf("The letter %c color is green and the contents of a compressed-gas cylinder is oxygen\n\n", color);
			break;
		default:	//如果上面的case皆不符合就執行此行
			printf("Contents unknown\n\n");
			break;
	}

	system("PAUSE");
	return 0;

}