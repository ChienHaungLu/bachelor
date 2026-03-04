#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main()
{
	double n = 0.0; //Data Usage (n), Gbs
	
	printf("Input Data Usage(Gbs): "); //輸入資料大小
	scanf("%lf", &n);
	if ((n > 0.0) && (n <= 1.0))
	{
		printf("charge: $%.2f\n\n", (250 * n));
	}
	else if ((n > 1.0) && (n <= 2.0))
	{
		printf("charge: $%.2f\n\n", (500 * n));
	}
	else if ((n > 2.0) && (n <= 5.0))
	{
		printf("charge: $%.2f\n\n", (1000 * n));
	}
	else if ((n > 5.0) && (n <= 10.0))
	{
		printf("charge: $%.2f\n\n", (1500 * n));
	}
	else if (n > 10.0)
	{
		printf("charge: $%.2f\n\n", (2000 * n));
	}
	else
		printf("bad data as well\n\n");
	system("PAUSE");
	return 0;
}