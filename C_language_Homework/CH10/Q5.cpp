#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
	int xx;
	int yy;
	int zz;
	int mm;
	char nickname[10]; /* 最多輸入十個 */
}address_struct;

/* input data format:
	111 22 3 44 platte
	555 66 7 88 wabash
	111 22 5 66 green
	0 0 0 0 none
*/

void scan_address(address_struct* address)
{
	printf("Input xx yy zz mm and nickname: ");
	scanf("%d %d %d %d %s", &address->xx, &address->yy, &address->zz, &address->mm, &address->nickname);
}

int local_address(address_struct address1, address_struct address2)
{
	if (address1.xx == address2.xx && address1.yy == address2.yy)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void print_address(address_struct address) 
{
	printf("%d.%d.%d.%d  %s\n", address.xx, address.yy, address.zz, address.mm, address.nickname);
}

int main()
{
	address_struct address[4];
	int i = -1;
	do
	{
		i++;
		scan_address(&address[i]);
		if (i == 4)
		{
			break;
		}

	} while (address[i].xx != 0 && address[i].yy != 0 && address[i].zz != 0 && address[i].mm != 0 && address[i].nickname != 0);

	for (int a = 0;a < 4;a++)
	{
		for (int b = a + 1;b < 4;b++)
		{
			if(local_address(address[a], address[b]))
			{
				printf("\nMachines %s and %s are on the same local network.\n\n", address[a].nickname, address[b].nickname);
			}
		}
	}

	printf("Full list:\n");
	for (int x = 0;x < 4;x++)
	{
		print_address(address[x]);
	}


	return 0;
}