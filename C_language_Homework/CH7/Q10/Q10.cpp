#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

int precinct[5][1], /* 只用4*1 */
	candidate_A,
	candidate_B,
	candidate_C,
	candidate_D,
	vote[4][4], /* 只用4*4 */
	top_tmp[4][1]; /* 每個候選人最高得票數暫存 */

double	vote_percentage_tmp[4][1]; /* 票數的%數存放 */

int main()
{
	int i = 0,
		sum_vote = 0.0,
		a_sum_vote = 0.0,
		b_sum_vote = 0.0,
		c_sum_vote = 0.0,
		d_sum_vote = 0.0;
	
	int a_max, /* 記錄每個候選人的最高票數 */
		b_max,
		c_max,
		d_max;

	FILE *data_input;
	data_input = fopen("race_data.txt", "r");
	while (!feof(data_input))
	{
		fscanf(data_input, "%d %d %d %d %d", &precinct[i][0], &candidate_A, &candidate_B, &candidate_C, &candidate_D);
		sum_vote = sum_vote + candidate_A + candidate_B + candidate_C + candidate_D; /* 全部票數加總 */
		for (int j = 0;j <= 4;j++) /* 將所有候選人的票存放於vote array */
		{
			switch (j)
			{
				case 0:
					vote[i][j] = candidate_A;
					break;
				case 1:
					vote[i][j] = candidate_B;
					break;
				case 2:
					vote[i][j] = candidate_C;
					break;
				default:
					vote[i][j] = candidate_D;
					break;
			}
		}
		i++;
	}

	/* a. Display the table with appropriate labels for the rows and columns. */
	printf("Precient    Candidate A       Candidate B       Candidate C       CandidateD\n");
	for (int m = 0;m <= 4;m++)
	{
		printf("%4d %14d %16d %18d %16d\n", precinct[m][0], vote[m][0],vote[m][1],vote[m][2],vote[m][3]);
	}
	printf("\n\n");

	/* b. Compute and display the total number of votes received by each candidate and the percentage of the total */
	for (int a = 0; a <= 4;a++)
	{
		a_sum_vote = a_sum_vote + vote[a][0];
		b_sum_vote = b_sum_vote + vote[a][1];
		c_sum_vote = c_sum_vote + vote[a][2];
		d_sum_vote = d_sum_vote + vote[a][3];
	}


	printf("Candidate A received: %d votes\n", a_sum_vote);
	printf("the percentage of the total votes: %.2f %%\n\n", double(a_sum_vote * 100.0 / sum_vote));
	printf("Candidate B received: %d votes\n", b_sum_vote);
	printf("the percentage of the total votes: %.2f %%\n\n", double(b_sum_vote * 100.0 / sum_vote));
	printf("Candidate C received: %d votes\n", c_sum_vote);
	printf("the percentage of the total votes: %.2f %%\n\n", double(c_sum_vote * 100.0 / sum_vote));
	printf("Candidate D received: %d votes\n", d_sum_vote);
	printf("the percentage of the total votes: %.2f %%\n\n", double(d_sum_vote * 100.0 / sum_vote));


	/* c. If any one candidate received over 50% of the votes, the program should 
	      display a message declaring that candidate the winner. */

	/*d.If no candidate received 50 % of the votes, the program should display a message declaring a runoff 
	    between the two candidates receiving the highest number of votes; the two candidates should be identified 
		by their letter names. */

	vote_percentage_tmp[0][0] = double(a_sum_vote * 100.0 / sum_vote); /* 暫時存放得票數所佔總票數的比例結果 */
	vote_percentage_tmp[1][0] = double(b_sum_vote * 100.0 / sum_vote);
	vote_percentage_tmp[2][0] = double(c_sum_vote * 100.0 / sum_vote);
	vote_percentage_tmp[3][0] = double(d_sum_vote * 100.0 / sum_vote);

	int a_top = 0,a_tmp,
		b_top = 0,b_tmp,
		c_top = 0,c_tmp,
		d_top = 0,d_tmp;

	if (vote_percentage_tmp[0][0] > 50.0) /* 判斷c小點的條件，若得票率大於50%就直接贏家 */
	{
		printf("\nCandidate A Winner!\n\n");
	}
	else if (vote_percentage_tmp[1][0] > 50.0)
	{
		printf("\nCandidate B Winner!\n\n");	
	}
	else if (vote_percentage_tmp[2][0] > 50.0)
	{
		printf("\nCandidate C Winner!\n\n");	
	}
	else if (vote_percentage_tmp[3][0] > 50.0)
	{
		printf("\nCandidate D Winner!\n\n");
	}
	else /* 反之若找不到握有得票數大於50%的候選人就會從此行往下執行 */
	{
		int top1 = 0, top2 = 0, top1_idx, top2_idx;
		for (int i = 0; i <= 4;i++)
		{
			if (a_top < vote[i][0]) /* 找出候選人A最高得票數 */
			{
				a_top = vote[i][0];
			}
			if (b_top < vote[i][1]) /* 找出候選人B最高得票數 */
			{
				b_top = vote[i][1];
			}
			if (c_top < vote[i][2]) /* 找出候選人C最高得票數 */
			{
				c_top = vote[i][2];
			}
			if (d_top < vote[i][3]) /* 找出候選人D最高得票數 */
			{
				d_top = vote[i][3];
			}
		}

		top_tmp[0][0] = a_top; /* 將每個候選人的最高票數結果暫存於top_tmp array */
		top_tmp[1][0] = b_top;
		top_tmp[2][0] = c_top;
		top_tmp[3][0] = d_top;

		for (int idx = 0; idx < 4; idx++)
		{
			if (top1 < top_tmp[idx][0])  /* 找出4位人誰的最高票數是第一名 */
			{
				top1 = top_tmp[idx][0];
				top1_idx = idx;
			}
		}
		for (int idx2 = 0; idx2 < 4; idx2++) /* 找出4位人誰的最高票數是第二名 */
		{
			if (top1 != 0) /* 有找到第一名票數最高者 */
			{
				if (top2 < top_tmp[idx2][0])
				{
					if (idx2 == top1_idx) /* 因為第一名的結果會有其對應的索引值，再找第二名時需跳過忽略 */
					{
						continue;
					}
					top2 = top_tmp[idx2][0];
					top2_idx = idx2;
				}
			}
			else
			{
				break;
			}
		}

		switch (top1_idx) /* 藉由暫存第一名其對應的索引值判斷是哪位候選人得票數第一 */
		{
		case 0:
			printf("\nNO.1: Candidate A -- %d votes\n", top1);
			break;
		case 1:
			printf("\nNO.1: Candidate B -- %d votes\n", top1);
			break;
		case 2:
			printf("\nNO.1: Candidate C -- %d votes\n", top1);
			break;
		default:
			printf("\nNO.1: Candidate D -- %d votes\n", top1);
			break;
		}

		switch (top2_idx) /* 藉由暫存第二名其對應的索引值判斷是哪位候選人得票數第二 */
		{
		case 0:
			printf("NO.2: Candidate A -- %d votes\n\n", top2);
			break;
		case 1:
			printf("NO.2: Candidate B -- %d votes\n\n", top2);
			break;
		case 2:
			printf("NO.2: Candidate C -- %d votes\n\n", top2);
			break;
		default:
			printf("NO.2: Candidate D -- %d votes\n\n", top2);
			break;
		}
	}
	return 0;
}