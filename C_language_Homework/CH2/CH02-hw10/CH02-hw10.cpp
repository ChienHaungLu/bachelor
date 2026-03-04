#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>

int main()
{	
	float x1, y1, x2, y2, x_mid, y_mid, fist_line_slope, perpendicular_bisector_slope, perpendicular_bisector_y_intercept;
	printf("Input the First Point of x:");
	scanf("%f", &x1);
	printf("Input the First Point of y:");
	scanf("%f", &y1);
	printf("Input the Second Point of x:");
	scanf("%f", &x2);
	printf("Input the Second Point of y:");
	scanf("%f", &y2);

	x_mid = (x1 + x2) / 2.0; //第一條線中心點x座標
	y_mid = (y1 + y2) / 2.0; // 第一條線中心點y座標
	fist_line_slope = (y1 - y2) / (x1 - x2); //第一條線斜率
	perpendicular_bisector_slope = -1 / fist_line_slope; //另一條線的斜率為第一條線斜率的乘上負號並倒數
	perpendicular_bisector_y_intercept = y_mid - perpendicular_bisector_slope * x_mid; //算另一條方程式的y截距
	printf("original two points: (%f,%f)、(%f,%f)\n", x1, y1, x2, y2);
	printf("perpendicular bisector equation: y = %.1fx + %.2f\n", perpendicular_bisector_slope, perpendicular_bisector_y_intercept);
	system("PAUSE");
	return 0;
}
