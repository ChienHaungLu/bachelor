#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int volume, min,rate;
	printf("Volume to be infused (ml) => ");
	scanf("%d", &volume);
	printf("Minutes over which to infuse => ");
	scanf("%d", &min);
	printf("VTBI: %d ml\n",volume);

	rate = volume * (60/min);
	printf("Rate: %d ml/hr\n", rate);

	system("PAUSE");
	return 0;
}