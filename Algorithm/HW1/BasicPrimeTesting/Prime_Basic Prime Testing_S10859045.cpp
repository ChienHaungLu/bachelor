#include <iostream>
#include <cstdlib>
#include<ctime>
using namespace std;
unsigned long long Prime(unsigned long long);

int main() 
{
	clock_t a, b;
	
	unsigned long long n; //unsigned long long可表示的範圍:0~18,446,744,073,709,551,615

	cout << "請輸入大於等於100的一整數:"; cin >> n;
	
		a = clock(); //計時開始
		if (Prime(n)) 
		{ 
			cout << n << "是質數" << endl; 
		}
		else 
		{ 
			cout << n << "不是質數" << endl; 
		}
		b = clock(); //計時結束
		
	cout<<"執行時間: "<<double(b-a)/ CLOCKS_PER_SEC<<"毫秒" << endl<<endl;
	system("pause");
	return 0;
}

/*判斷質數函式*/
unsigned long long Prime(unsigned long long x)
{
	unsigned long long i;
	for (i = 2; i * i <= x; ++i)
	{
		if (x % i == 0)
		{
			return 0;
		}
	}
	return 1;
}
