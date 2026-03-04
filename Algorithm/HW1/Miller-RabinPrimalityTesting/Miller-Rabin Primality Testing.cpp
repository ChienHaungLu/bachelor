#include <iostream>
#include <cstdlib>
#include<ctime>
using namespace std;

unsigned long long mulMod (unsigned long long , unsigned long long , unsigned long long);
unsigned long long mod_function (unsigned long long, unsigned long long, unsigned long long);
bool Prime(unsigned long long, int);


//主函數區域
int main()
{
    long long times;
    unsigned long long n;
    clock_t t1, t2;

    cout << "請輸入欲判斷的一整數:"; cin >> n;
    cout << "請輸入執行loop次數:"; cin >> times;

    t1 = clock();
    if (Prime(n, times))
    {
        cout <<"您所輸入的 "<< n << "為質數" << endl;
    }
    else
    {
        cout <<"您所輸入的 "<< n << "不為質數" << endl;
    }
    t2 = clock();

    cout << "本次程式執行時間:" << double(t2-t1) / CLOCKS_PER_SEC << "毫秒" << endl;
    
	system("pause");
    return 0;
}


unsigned long long mulMod(unsigned long long a, unsigned long long b, unsigned long long Mod)
{
    unsigned long long x = 0, y = a % Mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = (x + y) % Mod;
        }
        y = (y * 2) % Mod;
        b /= 2;
    }
    return x % Mod;
}

//Base^Exp % Mod
unsigned long long mod_function(unsigned long long Base, unsigned long long Exp, unsigned long long Mod)
{
    unsigned long long x = 1 , y = Base;

    while (Exp > 0)
    {
        if (Exp % 2 == 1)
            x = (x * y) % Mod;
        y = (y * y) % Mod;
        Exp = Exp / 2;
    }
    return x % Mod;
}

//Rabin 質數測試
bool Prime(unsigned long long p, int times)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2 == 0)
    {
        return false;
    }
    unsigned long long s = p - 1;

    while (s % 2 == 0)
    {
        s /= 2;
    }
    
    for (int j = 0; j < times; j++)
    {
        unsigned long long t = s;
        unsigned long long k = rand() % (p - 1) + 1;
        unsigned long long Mod = mod_function(k, t, p);

        while (t != p - 1 && Mod != 1 && Mod != p - 1)
        {
            Mod = mulMod(Mod, Mod, p);
            t *= 2;
        }

        if (Mod != p - 1 && t % 2 == 0)
        {
            return false;
        }
    }

    return true;
}

