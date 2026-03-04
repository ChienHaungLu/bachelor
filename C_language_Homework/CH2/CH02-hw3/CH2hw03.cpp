#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include<stdio.h>
#include<math.h>

int main()
{
	int hour, min;
	float temperature; //·Å«×
	float t; //®É¶¡
	printf("hour and min: ");
	scanf("%d %d", &hour, &min);
	t = hour + min / 60.0;
	temperature = (4.0 * pow(t,2) / (t + 2)) - 20;
	printf("Temperature: %f\n", temperature);
	system("pause");
	return 0;
}