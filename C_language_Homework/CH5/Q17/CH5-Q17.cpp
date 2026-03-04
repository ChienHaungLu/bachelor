#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double g_of_x(double x)
{
	return x*x* sin(x);
}

double h_of_x(double x)
{
	return sqrt(4 - x*x);
}

double trap(double a, double b, int n, double f(double x)) //計算梯形面積
{
	double h = (b - a) / n; //每個等份高度(△X) (可想成是Xi-1到Xi之間的距離值, i = 1,2,...)
	double sum = f(a) + f(b); //將上下梯形加總
	for (int i = 1; i <= n - 1; i++)
	{
		sum = sum + f(a + i * h); //a可想成是原點到x1的距離 
	}
	double area = h / 2 * sum; //線下面積總和
	return area;
}

int main()
{
	double a1 = 0, b1 = 3.14159; //g(x) bounded
	double a2 = -2, b2 = 2; // h(x) bounded

	printf("計算g(x)線下面積中...\n\n");
	for (int j = 2;j <= 128;j *= 2)
	{
		printf("g(x)分成%d等份的面積為: %lf", j, trap(a1, b1, j, g_of_x));
		printf("\n");
	}
	printf("\n");

	printf("-----------------------------------\n");

	printf("計算h(x)線下面積中...\n\n");
	for (int k = 2;k <= 128;k *= 2)
	{
		printf("g(x)分成%d等份的面積為: %lf", k,trap(a2, b2, k, h_of_x));
		printf("\n");
	}
	printf("\n\n");
	system("PAUSE");
	return 0;
}