#include<iostream>  
#include<ctime>
#include<cstdlib>
#include <vector>
#define SIZE 10  //若需要增加元素需在這裡做更動
int list[SIZE] = { '0' };
using namespace std;
const int Max = 1000;

void Merge(std::vector<int>& Array, int front, int mid, int end) {

    // array[front] to array[mid]放入 LeftSubarray[] , array[mid+1] to array[end]放入 RightSubarray[]

    std::vector<int> LeftSubarray(Array.begin() + front, Array.begin() + mid + 1),
        RightSubarray(Array.begin() + mid + 1, Array.begin() + end + 1);

    LeftSubarray.insert(LeftSubarray.end(), Max);      // 在LeftSub[]尾端加入值為 Max 的元素
    RightSubarray.insert(RightSubarray.end(), Max);    // 在RightSubarray[]尾端加入值為 Max 的元素

    int idxLeft = 0, idxRight = 0;

    for (int i = front; i <= end; i++) {

        if (LeftSubarray[idxLeft] <= RightSubarray[idxRight]) {
            Array[i] = LeftSubarray[idxLeft];
            idxLeft++;
        }
        else {
            Array[i] = RightSubarray[idxRight];
            idxRight++;
        }
    }
}

void Merge_Sort(std::vector<int>& array, int front, int end) {
    // front與end為矩陣範圍
    if (front < end) {                   // 表示目前的矩陣範圍是有效的
        int mid = (front + end) / 2;         // mid即是將矩陣對半分的index
        Merge_Sort(array, front, mid);    // 繼續divide矩陣的前半段subarray
        Merge_Sort(array, mid + 1, end);    // 繼續divide矩陣的後半段subarray
        Merge(array, front, mid, end);   // 將兩個subarray做比較, 並合併出排序後的矩陣
    }
}

void PrintArray(std::vector<int>& array,int key,int num)
{
    for (int i = 0; i < array.size(); i++) 
    {
        cout<< array[i] << " ";
    }

    cout << endl << endl << "第1" << "小的元素為(k=1): " << array[0] << endl;

    if (num % 2 != 0)
    {
        cout << "第" << (num / 2) << "小的元素為(k = ┌ n/ 2┐ 取最大整數) : " << array[num/2-1] << endl;
    }
    else
    {
        cout <<"第"<<key<<"小的元素為(k= ┌ n/ 2┐): "<<array[key-1]<<endl;
    }
    cout << "第"<<key<< "小的元素為(k=n): " << array[key-1] << endl;

    array.clear();
}


int main()
{
    clock_t start, end;
    int n; //元素個數;
    int k; //選第幾小

    cout << "幾個元素:"; cin >> n; 
    cout << "請輸入一序列:";
  
    start = clock();
    for (int i = 0; i < n; i++)
    {
        cin >> list[i];

    }
    std::vector<int> array(list, list + sizeof(list) / sizeof(int));
    cout << endl << "選擇第幾小資料: "; cin >> k;

    cout << endl << "【Merge Sort】" << endl << endl;
    cout << "排序前: " << endl;
    for (int i = 0; i < n; i++)
    {
        cout << list[i]<<" ";
    }
    cout << endl;
    cout <<endl<<"排序後: " << endl;
    Merge_Sort(array, 0, n-1);
    PrintArray(array,k,n);
    cout << "-------------------------------------------------" << endl;
    end = clock();

    cout << "本次運算總花費時間: " << double((end - start) / CLOCKS_PER_SEC) << "s" << endl << endl;
    system("pause");
    return 0;
}
