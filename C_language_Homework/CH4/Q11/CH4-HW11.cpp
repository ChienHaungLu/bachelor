#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h>

int within_x_percent(double ref, double data, double x)
{
	if (((ref - (x / 100) * ref) <= data) && (data <= (ref + (x / 100) * ref)))
		return 1;
	else
		return 0;
}

int main()
{
	  // DATA瞶絛瞅:   lower  < data value < higher + higher*5%
	double	Normal_Boiling_Point, data, percentage_value,
		higher, lower; //い程蔼㎝程 Normal Boiling Point 

	printf("Input Normal Boiling Point: ");
	scanf("%lf", &Normal_Boiling_Point);
	printf("Input data: ");
	scanf("%lf", &data);
	printf("Input percentage value: ");
	scanf("%lf", &percentage_value);
	printf("Input the higher boiling points in the table: ");
	scanf("%lf", &higher);
	printf("Input the lower boiling points in the table: ");
	scanf("%lf", &lower);

	if ((lower > data) || ((higher + higher * 0.05) < data)) //ぃ才砏﹚计絛瞅ず
	{
		printf("Substance unknown\n\n");
	}
	else
	{
		if (within_x_percent(Normal_Boiling_Point, data, percentage_value) == 1) //耞function肚
			printf("The result is True\n\n");
		else
			printf("The result is False\n\n");
	}
	
	system("PAUSE");
	return 0;
}