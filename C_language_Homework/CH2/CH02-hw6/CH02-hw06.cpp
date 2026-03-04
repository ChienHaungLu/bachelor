#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>

//final * 0.25 + current_avg * 0.75 = 79.5 (min_avg)

int main()
{
	int percentage;
	char grade_level;
	float min_avg, current_avg, final;
	printf("Enter desired grade> ");
	scanf("%c", &grade_level);
	printf("Enter minimum average required> ");
	scanf("%f",&min_avg);
	printf("Enter current average in course> ");
	scanf("%f", &current_avg);
	printf("Enter how much the final counts\n");
	printf("as a percentage of the course grade> ");
	scanf("%d", &percentage);

	final = (min_avg - current_avg * ((100 - percentage) / 100.0)) * 4; // final = (79.5 - 74.6 * 0.75) / 0.25
	printf("You need a score of %.2f on the final to get a %c", final, grade_level);
	system("PAUSE");
	return 0;
}