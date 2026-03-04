#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

double func(double x, double n, double c) // f(x) = x^n - c
{
	double value1 = 1;
	for (int i = 1; i <= n; i++)
	{
		value1 = value1 * x;  //計算 x^n
	}
	value1 = value1 - c;
	return value1;
}

double func_diff(double x, double n, double c) // f'(x) = n * x^(n-1)
{
	double value2 = 1;
	for (int j = 1; j <= n - 1; j++)
		value2 = value2 * x;
	value2 = value2 * n;
	return value2;
}

double sqrt_calculated(double n, double c)
{
	double x = c / 2; //初始值
	for (int k = 1; k <= 100; k++)
	{
		if (func(x, n, c) == 0) // x^n-c = 0 代表有一根
			break;
		x = x - func(x, n, c) / func_diff(x, n, c);
	}
	return x;
}

int main()
{
	int n; //n為開根號的數
	double x, c; //x為近似值, c為被開根號的數，
	printf("請輸入被開根號的數值: ");
	scanf("%lf", &c);
	printf("請輸入欲開根號的值: ");
	scanf("%d", &n);
	x = sqrt_calculated(n, c);
	printf("計算的根值為: %lf\n\n", x);
	system("PAUSE");
	return 0;
}