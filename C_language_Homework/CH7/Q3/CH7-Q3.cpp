#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int matrix[4][4];
int mass[4][1];

void fget_point_mass(int e1, int e2, int e3, int e4, int n, int loop_count)
{
	for (loop_count; loop_count < n; loop_count++) /* loop_count 用於記錄上一次寫入matrix的row位置 */
	{
		for (int j = 0;j < n;j++)
		{
			if (j == 0)
			{
				matrix[loop_count][j] = e1;
			}
			if (j == 1)
			{
				matrix[loop_count][j] = e2;
			}
			if (j == 2)
			{
				matrix[loop_count][j] = e3;
			}
			if (j == 3)
			{
				matrix[loop_count][j] = e4;
				mass[loop_count][0] = e4; /* 最後一行的所有元素為mass vector，獨立存放於mass array */
			}
		}
	}
	
}


void fwrite_point_mass(int n)
{
	FILE *outfile;
	outfile = fopen("output.txt", "w");
	fprintf(outfile, "location  ");

	for (int i = 0; i < n;i++)
	{
		for (int j = 0;j < n;j++)
		{
			if (j < 3) /*非最後一個column的元素都將他們印出並作為local matrix*/
			{
				fprintf(outfile, " %2d ", matrix[i][j]);
			}
			else /* 超過matrix[i][2]就直接跳過這次，會進到下一個row的資料來寫入輸出的檔案 */
			{
				fprintf(outfile, "\n");
				continue;
			}
		}
		fprintf(outfile, "         ");
	}
	fprintf(outfile, "\n");

	fprintf(outfile, "mass     ");
	for (int a = 0; a < n;a++)
	{
		for (int b = 0;b < n;b++)
		{
			if (b == 3) /* matrix最後一個column的所有元素為mass vector */
			{
				fprintf(outfile, "%2d", matrix[a][b]);
				fprintf(outfile, "\n");
			}
			else
			{
				continue;
			}
		}
		fprintf(outfile, "         ");
	}
	fprintf(outfile, "\n");
	fprintf(outfile, "n        %2d\n",n);
}

void center_grav() /* 計算重心 */
{
	double center;
	double mp_sum_0 = 0.0;
	double mp_sum_1 = 0.0;
	double mp_sum_2 = 0.0;

	double m = 0.0;
	double c0 = 0.0,
		   c1 = 0.0,
		   c2 = 0.0;

	/*  
		C = (m1 * p1 + m2 * p2 + ... + mn * pn) / m    (p為三維座標)
	*/
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (j == 0)
			{
				// 2 * 5 + 5 * 4 + 2 * (-4) + 1 * (-9) 
				mp_sum_0 = mp_sum_0 + mass[i][0] * matrix[i][j];
			}

			if (j == 1)
			{
				// 2 * (-4) + 5 * 3 + 2 * (-3) + 1 * 8
				mp_sum_1 = mp_sum_1 + mass[i][0] * matrix[i][j];
			}

			if (j == 2)
			{
				// 2 * 3 + 5 * (-2) + 2 * (-1) + 1 * 6
				mp_sum_2 = mp_sum_2 + mass[i][0] * matrix[i][j];
			}
		}

		m = m + mass[i][0]; /* 所有mass元素加總 */
	}
	c0 = mp_sum_0 / m;
	c1 = mp_sum_1 / m;
	c2 = mp_sum_2 / m;
	printf("\ncenter of gravity:(%.2f, %.2f, %.2f)\n", c0, c1, c2); /* 重心座標 */
}


int main()
{
	int n;
	int loop_count = 0;
	int e1, e2, e3, e4;


	FILE *infile; /* 宣告指標變數 */
	infile = fopen("file.txt", "r");

	fscanf(infile, "%d", &n); /* 讀取n的值 */

	while (!feof(infile)) /* 依題目要求，重複輸入直到讀檔完畢 */
	{
		fscanf(infile, "%d %d %d %d", &e1, &e2, &e3, &e4); /* 每一row裡面的對應column元素讀取 */
		fget_point_mass(e1, e2, e3, e4, n, loop_count);
		fwrite_point_mass(n);
		loop_count++;
	}

	printf("location matrix:\n");
	for (int i = 0; i < n;i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%2d", matrix[i][j]);
		}
		printf("\n");
	}

	printf("\nmass vector:\n");
	for (int k = 0; k < n; k++)
	{
		printf("%2d\n", mass[k][0]); /* mass為4*1的矩陣 */
	}
	
	center_grav();

	return 0;

}