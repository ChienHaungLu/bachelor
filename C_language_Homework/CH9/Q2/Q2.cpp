#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX 20

int isPalindrome(char tmp_str[MAX],int first,int last)
{
	if (tmp_str[first] != tmp_str[last]) /* 不相同就不是回文 */
	{
		return 0;
	}

	if (first < last + 1) /* 遞迴判斷回文 */
	{
		isPalindrome(tmp_str, first + 1, last - 1);
	}
	return 1;
}

int main()
{
	char str[MAX]={}, tmp_str[MAX]={}, ch;
	int j = 0;
	printf("Input your string: ");
	scanf("%[^\n]",&str); /* 連同有空格的字串一併寫入至str array */

	for (int i = 0; i < strlen(str); i++) /* 判斷回文 */
	{
		ch = tolower(str[i]); /* 輸入的字元皆強制轉為小寫 */
		if (ch >= 'a' && ch <= 'z' || ch >='0' && ch <= '9')
		{
			tmp_str[j] = ch;
			j++;
		}
	}
	if (isPalindrome(tmp_str,0,strlen(tmp_str)-1))
	{
		printf("The string [%s] is a palindrome!\n\n", tmp_str);
	}
	else
	{
		printf("The string [%s] is not a palindrome!\n\n", tmp_str);
	}
	return 0;
}