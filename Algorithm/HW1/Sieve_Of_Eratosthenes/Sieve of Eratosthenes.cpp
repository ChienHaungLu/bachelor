#include<iostream>
#include<iomanip>
#include<ctime>
using namespace std;
#define MAX_SIZE 100000000

void Prime(unsigned long long h)
{
	unsigned long long inputnum;
	unsigned long long  i, j;
	unsigned long long* arr;
	arr = new unsigned long long[h];

	cin >> inputnum;

	clock_t a = clock();
	for (unsigned long long i = 0; i < MAX_SIZE; i++)
		arr[i] = 1;

	//Sieve of Eratosthenes algorithm

	for (unsigned long long i = 2; i < MAX_SIZE; i++)
	{
		for (unsigned long long j = i * i; j < MAX_SIZE; j += i)
		{
			arr[j - 1] = 0;
		}
	}

	for (unsigned long long i = 2; i < MAX_SIZE; i++)
	{
	
		if (arr[i - 1] == 1)
		{
			if (i == inputnum)
			{
				cout << inputnum << "是質數";

			}
		}

	}
	clock_t b = clock();
	delete[] arr;
	cout << endl;
	cout << "執行時間: " << double(b - a) / CLOCKS_PER_SEC << "毫秒" << endl;

}

int main()
{
	cout << "請輸入一整數:";
	Prime(MAX_SIZE);
	system("pause");
	return 0;
}


