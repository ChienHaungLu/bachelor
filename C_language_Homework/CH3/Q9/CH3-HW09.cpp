#define _CRT_SECURE_NO_DEPRECATE

#include <stdlib.h>
#include<stdio.h>
#include<math.h>


void model(void) //predict model calculate function
{
	int day;
	double cal_case;
	printf("Enter day number>> ");
	scanf("%d", &day);
	cal_case = 40000 / (1 + 39999 * exp(-0.24681 * day)); //the number of cases predicted
	printf("By day %d, model predicts %d cases total.\n\n", day, int(cal_case));
}

int main()
{
	printf("FLU EPIDEMIC PREDICTIONS BASED ON ELAPSED DAYS SINCE FIRST CASE REPORT\n\n");
	model();
	model();
	model();
	system("PAUSE");
	return 0;
}