#include<iostream>  
#include<ctime>
#include<iomanip>
#include<cstdlib>
#define SIZE 10
int list[SIZE] = { '0' };
using namespace std;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int* list, int front, int end) {
    int pivot = list[end];
    int i = front - 1;
    for (int j = front; j < end; j++) {
        if (list[j] < pivot) {
            i++;
            swap(&list[i], &list[j]);
        }
    }
    i++;
    swap(&list[i], &list[end]);
    return i;
}

void Quick_Sort(int* list, int front, int end) {
    if (front < end) {
        int pivot = Partition(list, front, end);
        Quick_Sort(list, front, pivot - 1);
        Quick_Sort(list, pivot + 1, end);
    }
}
void PrintArray(int* list, int x,int key) {
    for (int i = 0; i < x; i++) {
        cout << right<<setw(2) << fixed << list[i]<<"  ";
    }
    cout <<endl;
    cout << endl << endl << "第1" << "小的元素為(k=1): " << list[0] <<setw(2)<< endl;

    if (x % 2 != 0)
    {
        cout << "第" << (x / 2) << "小的元素為(k = ┌ n/2┐ 取最大整數) : " << list[x / 2 - 1] << endl;
    }
    else
    {
        cout << "第" << x/2 << "小的元素為(k= ┌ n/2┐): " << list[x - 1] << endl;
    }
    cout << "第" << key << "小的元素為(k=n): " << list[key - 1] << endl;
    cout << endl;
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
    cout << "選擇第幾小資料: "; cin >> k;
    cout <<endl<< "排序前: " ;
    for (int i = 0; i < n; i++)
    {
        cout << right <<setw(2)<< fixed <<list[i]<<"  ";

    }
    cout << endl;
    Quick_Sort(list, 0, n - 1);

    cout << "排序後: ";
    PrintArray(list, n,k);
    cout << "-------------------------------------------------" << endl;
    end = clock();

    cout << "本次運算總花費時間: " << float((end - start) / CLOCKS_PER_SEC) << "s" << endl << endl;
    system("pause");
    return 0;
}