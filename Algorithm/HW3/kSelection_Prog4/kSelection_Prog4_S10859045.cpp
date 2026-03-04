#include<iostream>  
#include<ctime>
#include<iomanip>
#include<cstdlib>
#define SIZE 10      //輸入元素個數時，這裡必須一起更動
int list[SIZE] = { '0' };
using namespace std;

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int Partition(int list[], int lleft, int rright) 
{
    int pivot = list[rright];
    int i = lleft - 1;
    for (int j = lleft; j <= rright-1; j++) {
        if (list[j] < pivot) {
            i++;
            swap(&list[i], &list[j]);
        }
    }
    swap(&list[i+1], &list[rright]);
    return (i+1);
}

//若K值比n/2取最大整數還小，則左邊遞迴，右邊不遞迴。
//反之，若k值比n/2取最大整數還大，則左邊不遞迴，右邊遞迴。
int QuickSelection(int list[], int lleft, int rright,int key)
{
    if (key > 0 && key <= (rright - lleft + 1))
    {
        int index = Partition(list, lleft, rright);
        if (index - lleft == key - 1)
            return list[index];
        else if (index - lleft > key - 1)
            return QuickSelection(list, lleft, index - 1, key);
        else
            return QuickSelection(list, index + 1, rright , key - index + lleft - 1);
    }
}


int main() {

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
    
    cout << "選擇第k小資料: "; cin >> k;
    cout << endl << "排序前: ";
    int list_size = sizeof(list) / sizeof(list[0]);
    for (int i = 0; i < list_size; i++)
    {
        cout << right << setw(2) << fixed << list[i] << "  ";

    }
    cout << endl;
    
    cout << "排序後: ";
    const int val=QuickSelection(list, 0, list_size- 1,k);
    if (n % 2 != 0)
    {
        if (k <= (n / 2 + 1))
        {
            for (int i = 0; i < (list_size / 2 + 1); i++)
            {
                cout << right << setw(2) << fixed << list[i] << "  ";
            }
            cout << endl;
        }
        if (k > (n / 2 + 1)) 
        {
            for (int i = 0; i < (list_size / 2 + 1); i++)
            {
                cout << right << setw(2) << fixed << "    ";
            }
            for (int i = (list_size / 2 + 1); i < list_size; i++)
            {
                cout << right << setw(2) << fixed << list[i] << "  ";
            }
            cout << endl;
        }
    }
    if (n % 2 == 0)
    {
        if (k <= (n / 2))
        {
            for (int i = 0; i < (list_size / 2); i++)
            {
                cout << right << setw(2) << fixed << list[i] << "  ";
            }
            cout << endl;
        }
        if (k > (n / 2))
        {
            for (int i = 0; i < (list_size / 2); i++)
            {
                cout << right << setw(2) << fixed << "    ";
            }
            for (int i = list_size / 2; i < list_size; i++)
            {
                cout << right << setw(2) << fixed << list[i] << "  ";
            }
            cout << endl;
        }
    }
   /* for (int i = 0; i < list_size; i++)
    {
        cout << right << setw(2) << fixed << list[i]<<"  ";
    }
    cout << endl<<endl; */

    cout << endl;
    if (n % 2 != 0)
    {
        if (k < (n / 2 + 1))
        {
            cout << "【說明】" << "k<中間值，所以左邊QuickSelection遞迴，右邊不遞迴，以此類推..." << endl;
        }
        else
        {
            cout << "【說明】" << "k>中間值，所以左邊不遞迴，右邊QuickSelection遞迴，以此類推..." << endl;
            cout << "【說明】" << "k=中間值，就直接找到了，不需遞迴。" << endl;
        }
    }
    if (n % 2 == 0)
    {
        if (k < (n / 2))
        {
            cout << "【說明】" << "k<中間值，所以左邊QuickSelection遞迴，右邊不遞迴，以此類推..." << endl;
        }
        else
        {
            cout << "【說明】" << "k>中間值，所以左邊不遞迴，右邊QuickSelection遞迴，以此類推..." << endl;
            cout << "【說明】" << "k=中間值，就直接找到了，不需遞迴。" << endl;
        }
    }

    cout <<endl<< endl << "第1小的元素值為:" << list[0]<<endl;
    if (n % 2 != 0)
    {
        cout << endl << "第" << (n/2+1) << "小的元素值為: " << list[n/2] << endl;
    }
    if(n%2==0)
    {
        cout << endl << "第" << (n / 2) << "小的元素值為: " << list[(n / 2) -1] << endl;
    }
    cout<<endl <<"第"<<k<<"小的元素值為: " << val<<endl;
    cout << "-------------------------------------------------" << endl;
    end = clock();

    cout << "本次運算總花費時間: " << float((end - start) / CLOCKS_PER_SEC) << "s" << endl << endl;

    system("pause");
    return 0;
}