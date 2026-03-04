#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
	double down_payment, //頭期款
		car_total_price, //車子價格總金額
		annual_rate, //年利率
		P, //借的金額
		i, //月利率
		n, //總共支付金額
		payment; //每個月要支付的

	printf("down payment: ");
	scanf("%lf", &down_payment);
	printf("car total price: ");
	scanf("%lf", &car_total_price);
	printf("annual rate: ");
	scanf("%lf", &annual_rate);
	printf("the amount you borrow: ");
	scanf("%lf", &P);
	printf("total number of payments: ");
	scanf("%lf", &n);

	i = annual_rate / 12 / 100;
	payment = (i * P) / (1 - pow((1 + i), -n));

	printf("the monthly payment: $%.2f\n", payment);
	system("PAUSE");
	return 0;
}