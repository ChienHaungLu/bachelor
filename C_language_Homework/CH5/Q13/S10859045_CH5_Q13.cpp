#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{	
	char str[50];
	int n_player, //幾位選手
		player_num; //選手編號
	
	printf("How many players? Ans: ");
	scanf("%d", &n_player);
	for (int i = 1;i <= n_player;i++)
	{
		double batting = 0.0; //打擊率
		printf("Input the number of the player: ");
		scanf("%d", &player_num);
		printf("Input the record of the player: ");
		scanf(" %s", str);
		for (int i = 1; i <= n_player; i++)
		{
			int str_len;
			double h = 0.0, // h = hit
				   o = 0.0; //out
			
			str_len = strlen(str);
			for (int j = 1; j <= str_len; j++)
			{
				if (str[j - 1] == 'H')
				{
					h++;			
				}
				if (str[j - 1] == 'O')
				{
					o++;
				}
			}

			batting = h / (h + o);
		}
		
		printf("\nPlayer %d's record: %s\n", player_num,str);
		printf("\nPlayer %d's batting average: %.4f\n\n", player_num, batting);

	}
	system("PAUSE");
	return 0;
}