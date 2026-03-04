#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>

int main()
{
	float beginning_odometer;
	float ending_odometer;
	printf("TAXI FARE CALCULATOR\n");
	printf("Enter beginning odometer reading=>");
	scanf("%f", &beginning_odometer);
	printf("Enter ending odometer reading=>");
	scanf("%f", &ending_odometer);
	printf("You traveled a distance of %.1f miles. At $1.50 per mile, your fare is $ %.2f .", (ending_odometer - beginning_odometer), (ending_odometer - beginning_odometer) * 1.50);
	return 0;
}

