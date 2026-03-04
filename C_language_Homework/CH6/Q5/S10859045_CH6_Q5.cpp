#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void reverse(char *str) /* 反轉 */
{
    char tmp;
    int n = strlen(str);
    for (int i = 0; i < n / 2; i++)
    {
        tmp = str[i]; /* 先將左邊部分資料暫存 */
        str[i] = str[n - 1 - i]; /* 開始反轉 */
        str[n - 1 - i] = tmp;
    }
    printf("%s\n", str);
}

bool prime(int num) /* 判斷質數 */
{
    if (num == 1) /* 1不是質數 */
    {
        return false;
    }
    
    for (int i = 2; i * i < num; i++) /* 窮舉法判斷質數 */
    {
        if (num % i == 0) /*找到能被整除得即非質數*/
        {
            return false;
        }
    }
    return true;
}

bool palindrome(char *point) /* 判斷回文 */
{
    int len = strlen(point);
    for (int i = 0; i < len / 2; i++)
    {
        if (point[i] != point[len - 1 - i]) /* 由左第一位 和 由右第一位往中心靠近來判斷是否為回文 */
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int input_num;
    char num_reverse[20];
    int num_prime;
    char num_palindrome[20];

    printf("輸入欲輸入的資料有幾筆: ");
    scanf("%d", &input_num);
    printf("---------------------------\n");
    printf("a. Reverse a given number.\n");
    printf("---------------------------\n");
    printf("\n請輸入欲反轉的資料: ");

    for (int i = 0;i < input_num;i++)
    {
        scanf("%s", &num_reverse);
        printf("\n%s經反轉後的資料為: ", num_reverse);
        reverse(num_reverse);
        printf("\n");
    }
    printf("---------------------------------------\n\n");

    printf("-------------------------------------------------\n");
    printf("b.Check whether the given number is prime or not.\n");
    printf("-------------------------------------------------\n");
    printf("\n請輸入欲判斷質數的資料: ");
    for (int i = 0;i < input_num;i++)
    {
        scanf("%d", &num_prime);
        printf("\n%d is prime? Ans: ", num_prime);
        if (prime(num_prime) == 0)
        {
            printf("不是質數");
        }
        else
        {
            printf("是質數");
        }
        
        printf("\n\n");
    }

    printf("-------------------------------------------------\n");
    printf("c.Check whether the given number is a palindrome or not.\n");
    printf("-------------------------------------------------\n");
    printf("\n請輸入欲判斷回文的資料: ");
    for (int i = 0;i < input_num;i++)
    {
        scanf("%s", &num_palindrome);
        printf("\n%s is palindrome? Ans: ", num_palindrome);
        if (palindrome(num_palindrome) == 0)
        {
            printf("False");
        }
        else
        {
            printf("True");
        }
        
        printf("\n\n");
    }
    system("PAUSE");
    return 0;
}