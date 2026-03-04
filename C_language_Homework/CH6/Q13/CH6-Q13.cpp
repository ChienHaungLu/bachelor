#define _CRT_SECURE_NO_WARNINGS
#define input_data_size 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define start 0
#define build_num 1  //數字
#define build_id 2

bool the_letter(char ch) /* 判斷字元 */
{
	return 'A' <= ch && ch <= 'Z' || 'a' <= ch && ch <= 'z';
}

bool the_digit(char num) /* 判斷數值 */
{
	return '0' <= num && num <= '9';
}

void the_identifier(char* ch,int idx) /* 依據題目要求Output Identifier Message */
{
	for (int k = 0;k < idx;k++)
	{
		printf("%c", ch[k]); /* 從字串中逐次印出字元 */
	}
	printf(" – Identifier\n");
	
}

void the_number(char* ch, int idx) /* 依據題目要求Output Number Message */
{
	for (int k = 0;k < idx;k++)
	{
		printf("%c", ch[k]); /* 從字串中逐次印出字元 */
	}
	printf(" – Number\n");
}

int main()
{
	char str[input_data_size];
	char msg[10]; 
	char *ptr; /* 宣告欲指向字串地址的指標ptr */

	int current_state = start;
	int next_state = start;
	int idx = 0;
	

	printf("Input:\n");
	gets_s(str);
	int str_len = strlen(str);
	printf("\nOutput: \n");

	for (int i = 0;i <= str_len;i++)
	{
		ptr = &str[i]; /* 將指標指向字串的地址 */
		switch (current_state)
		{
			case start:
				if (*ptr == '.') /* Period(2) */
				{
					break;
				}
				if (isblank(*ptr)) /* Blank(3) */
				{
					next_state = start;
					current_state = next_state;
					continue;
				}
				if (the_letter(*ptr)) /* Letter(4) */
				{
					next_state = build_id;
					msg[idx++] = *ptr; 
					current_state = next_state;
				}
				if (the_digit(*ptr)) /* Digit(1) */
				{
					next_state = build_num;
					msg[idx++] = *ptr;
					current_state = next_state;
				}
				break;

			case build_id:
				/* Letter(5) */ /* Digit(6) */ /* Underscore(7) */
				if (the_digit(*ptr) || the_letter(*ptr) || *ptr == '_')
				{
					next_state = build_id;
					msg[idx++] = *ptr;
					current_state = next_state;
				}
				else
				{
					the_identifier(msg, idx);
					idx = 0; /* 索引值歸0，以便msg後續空間重複利用 */
					next_state = start;
					current_state = next_state;
				}
				break;

			case build_num:
				if (the_digit(*ptr))
				{
					next_state = build_num;
					msg[idx++] = *ptr;
					current_state = next_state;
				}
				else
				{
					the_number(msg, idx);
					idx = 0; /* 索引值歸0，以便msg後續空間重複利用 */
					next_state = start;
					current_state = next_state;
				}
				break;
		}
	}
	printf("\n");
	system("PAUSE");
	return 0;
}