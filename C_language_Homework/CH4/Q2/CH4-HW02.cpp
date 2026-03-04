#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double wt_lb = 0.0, ht_in = 0.0, BMI = 0.0; //wt_lb is weight in pounds and ht_in is height in inches.
	printf("Input your  weight in pounds and height in inches: ");
	scanf("%lf %lf", &wt_lb, &ht_in);

	BMI = 703.0 * wt_lb / pow(ht_in, 2.0); //BMI ­pºâ
	printf("BMI: %.1f\n", BMI);

	// BMI §PÂ_
	if (BMI < 18.5)
		printf("Your Weight Status is Underweight\n");
	else if ((BMI >= 18.5) && (BMI <= 24.9))
		printf("Your Weight Status is Normal\n");
	else if ((BMI >= 25.0) && (BMI <= 29.9))
		printf("Your Weight Status is Overweight\n");
	else
		printf("Your Weight Status is Obese\n");

	system("PAUSE");
	return 0;
}