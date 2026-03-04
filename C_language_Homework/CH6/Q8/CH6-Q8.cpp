#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

double charge_calculated(double hour, double *charge_per_hour, double *avg_cost) /* 費用計算 */
{
	if (hour <= 10)
	{
		*charge_per_hour = 7.99;
		*avg_cost = *charge_per_hour / hour;
	}
	else /* hour >10 */
	{
		*charge_per_hour = 7.99 + ceil(hour - 10) * 1.99;
		*avg_cost = *charge_per_hour / hour;
	}
	return *avg_cost;
}

int main()
{
	FILE* input_file, *output_file;
	int customer,mouth, year; /* 存放月份和年份的變數 */
	double hour_used, charge_per_hour,avg_cost;

	input_file = fopen("usage.txt", "r"); /* 開啟usage文檔並讀取 */
	output_file = fopen("charges.txt", "w"); /* 開啟charge文檔並寫入 */

	if (input_file == NULL)
	{
		printf("開啟檔案失敗");
	}
	else
	{
		fscanf(input_file, "%d %d", &mouth, &year);
		fprintf(output_file, "Charges for %d/%d \n\n", mouth, year);
		fprintf(output_file, "Customer  Hours used  Charge per hour  Average cost\n");

		while(!feof(input_file)) /* usage檔案尚未讀取完畢 */
		{
			fscanf(input_file,"%d %lf", &customer, &hour_used); /* 讀取所需資料 */
			charge_calculated(hour_used, &charge_per_hour, &avg_cost); /* 計算總費用及每小時平均花費 */
			fprintf(output_file, "%d        %.1f           %2.2f            %2.2f\n", customer, hour_used, charge_per_hour, avg_cost); /*寫入資料至相對應的輸出檔案*/
		}
		printf("charges.txt 檔案寫入完成!\n");
	}
	
	return 0;
}

