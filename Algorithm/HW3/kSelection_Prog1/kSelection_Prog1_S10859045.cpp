#include<iostream>  
#include<ctime>
#include<cstdlib>
#define SIZE 10
int array[SIZE] = { '0' };
int list[SIZE] = { '0' };
using namespace std;

void Insertion_Sort(int array[],int x,int key)
{

    cout << "排列前:" << endl;
    for (int i = 0; i < x; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl << endl;
    for (int k = 1; k < x; k++)
    {
        int temp = array[k];
        int j = k - 1;
        while (j >= 0 && temp <= array[j])
        {
              array[j + 1] = array[j];
              j = j - 1;
        }
        array[j + 1] = temp;
    }
    cout << "排列後:" << endl;
    for (int i = 0; i < x; i++)
    {
        cout << array[i] << " ";
    }
   
    cout << endl << endl << "第1" << "小的元素為(k=1): " << array[0] << endl;

    if (x % 2 != 0)
    {
        cout << "第" << (x / 2)+1 << "小的元素為(k = ┌ n/2┐ 取最大整數) : " << array[x / 2] << endl;
    }
    else
    {
        cout << "第" << x/2 << "小的元素為(k= ┌ n/2┐): " << array[x / 2] << endl;
    }
    cout << "第" << key << "小的元素為(k=n): " << array[key - 1] << endl;
}



int main()
{
    clock_t start, end;
    int n; //輸入個數
    int k; //選第幾小

    cout << "幾個元素:"; cin >> n;
    cout << "請輸入一序列:";

    start = clock();
    for (int i = 0; i < n; i++)
    {
        cin >> list[i];
      
    }
    cout << "選擇第幾小資料: "; cin >> k;

    cout <<endl<< "【Insertion Sort】" <<endl<<endl;
        Insertion_Sort(list, n,k);
    cout << "-------------------------------------------------" << endl ;
    end = clock();

    cout << "本次運算總花費時間: " << float((end - start) / CLOCKS_PER_SEC)<<"s"<<endl<<endl;
    system("pause");
    return 0;
}
