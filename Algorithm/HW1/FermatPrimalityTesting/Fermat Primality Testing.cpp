#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// (Base^Exp % Mod)
unsigned long long mod_function(unsigned long long Base, unsigned long long Exp, unsigned long long Mod) 
{
    unsigned long long x = 1; unsigned long long y = Base;

    while (Exp > 0) 
    {
        if (Exp % 2 == 1) 
        {
            x = (x * y) % Mod;
        }    
        y = (y * y) % Mod;
        Exp /= 2;
    }
    return x % Mod;
}


int Prime(unsigned long long p, int times) 
{
    if (p == 1) 
    {
        return 0;
    }
    for (int j = 0; j < times; j++) {
        unsigned long long k = rand() % (p - 1) + 1;
        if (mod_function(k, p - 1, p) != 1) 
        {
            return 0;
        }
    }
    return 1;
}

/*主函數區域*/
int main() 
{
    clock_t t1, t2;
    int times; unsigned long long n;

    cout << "請輸入一整數判斷是否為質數:"; cin >> n;
    cout << "請輸入迴圈執行次數:"; cin >> times;
    cout << endl;

    //三種可能性，截取自參考資料。
    //(a) n為質數時， a^(n-1) % n = 1 必成立。
    //(b) n不為質數時，a^(n - 1) % n = 1 也可能成立。
    //(c) 若以上兩條件皆不成立，則不是質數。

    t1 = clock();
    if (Prime(n, times) == 1)
    {
        cout << "您所輸入的" <<  n << "是質數" <<endl;
    }
    else
    {
        cout << "您所輸入的" << n << "不是質數" << endl;
    }
    t2 = clock();

    cout << "本次程式執行時間為:" << double(t2-t1) / CLOCKS_PER_SEC << "毫秒" << endl;
	system("pause");
    return 0;
}
