#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#define mile 5280 //1英里 = 5280 feets
#define kilometer 3282 //1公里 = 3282 feets

void runner1(void)
{

	double min1,sec1,fps1,mps1;

	printf("Input Runner1 minutes and seconds: ");
	scanf("%lf %lf", &min1, &sec1);

	sec1 = min1*60 + sec1; //時間單位統一 (秒)
	fps1 = mile / sec1; // 計算feet per second
	mps1 = kilometer / sec1; //計算 meters per second

	printf("Output Runner1 speed in feet per second: %.2f (fps)\n", fps1);
	printf("Output Runner1 speed in meters per second: %.2f (mps)\n\n", mps1);
}

void runner2()
{
	double min2,sec2,fps2,mps2;

	printf("Input Runner2 minutes and seconds: ");
	scanf("%lf %lf", &min2, &sec2);

	sec2 = min2 * 60 + sec2;
	fps2 = mile / sec2;
	mps2 = kilometer / sec2;

	printf("Output Runner2 speed in feet per second: %.2f (fps)\n", fps2);
	printf("Output Runner2 speed in meters per second: %.2f (mps)\n\n", mps2);
}


void runner3()
{
	double min3,sec3,fps3,mps3;

	printf("Input Runner3 minutes and seconds: ");
	scanf("%lf %lf", &min3, &sec3);
	
	sec3 = min3 * 60 + sec3;
	fps3 = mile / sec3;
	mps3 = kilometer / sec3;

	printf("Output Runner3 speed in feet per second: %.2f (fps)\n", fps3);
	printf("Output Runner3 speed in meters per second: %.2f (mps)\n\n", mps3);
}


void runner4()
{
	double min4,sec4,fps4,mps4;

	printf("Input Runner4 minutes and seconds: ");
	scanf("%lf %lf", &min4, &sec4);
	
	sec4 = min4 * 60 + sec4;
	fps4 = mile / sec4;
	mps4 = kilometer / sec4;

	printf("Output Runner4 speed in feet per second: %.2f (fps)\n", fps4);
	printf("Output Runner4 speed in meters per second: %.2f (mps)\n\n", mps4);
}


int main()
{
	runner1(); //呼叫跑者1函式
	runner2(); //呼叫跑者2函式
	runner3(); //呼叫跑者3函式
	runner4(); //呼叫跑者4函式
	system("PAUSE");
	return 0;
}
