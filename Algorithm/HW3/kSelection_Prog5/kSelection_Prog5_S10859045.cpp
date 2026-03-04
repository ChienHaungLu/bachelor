#include <iostream>
#include <vector>
#include <algorithm>
#include<iomanip>
#include<ctime>
#define SIZE 105 

using namespace std;

int Find_Median(vector<int> vec) { //找中間值

    int median;
    size_t size = vec.size();
    median = vec[(size / 2)];
    return median;
}

int Find_Median_Of_Medians(vector<vector<int> > values) { //找中間值的中間值
    vector<int> medians;

    for (int i = 0; i < values.size(); i++) {
        int m = Find_Median(values[i]);
        medians.push_back(m);
    }

    return Find_Median(medians);
}

//分3團
void Selection_Used_Median_Of_Medians(const vector<int> values, int k)
{
    vector<vector<int> > vec2D;

    int count = 0;
    while (count != values.size()) {
        int countRow = 0;
        vector<int> row;

        while ((countRow < 3) && (count < values.size())) {
            row.push_back(values[count]);
            count++;
            countRow++;
        }
        vec2D.push_back(row);
    }

    cout << endl << endl << "印出2維vector: " << endl;
    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[i].size(); j++) {
            cout << right << setw(2) << fixed << vec2D[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl;


    int m = Find_Median_Of_Medians(vec2D);
    cout << "Median of medians is : " << m << endl << endl;   //從當前2維向量陣列裡印出中間值的中間值
    cout << "------------------------------------" << endl;

    vector<int> L1, L2;

    for (int i = 0; i < vec2D.size(); i++) {
        for (int j = 0; j < vec2D[i].size(); j++) {
            if (vec2D[i][j] > m) {
                L1.push_back(vec2D[i][j]);
            }
            else if (vec2D[i][j] < m) {
                L2.push_back(vec2D[i][j]);
            }
        }
    }


    cout << endl << "印出比中間值還大的元素: " << endl;
    for (int i = 0; i < L1.size(); i++) {
        cout << right << setw(2) << fixed << L1[i] << "  ";
    }

    cout << endl << endl << "印出比中間值還小的元素 : " << endl;
    for (int i = 0; i < L2.size(); i++) {
        cout << right << setw(2) << fixed << L2[i] << "  ";
    }


    if ((k - 1) == L1.size()) {
        cout << endl << endl << "這個case所指定的第K小的元素值為: " << m;
    }
    else if (k <= L1.size()) {
        return Selection_Used_Median_Of_Medians(L1, k);
    }
    else if (k > (L1.size() + 1)) {
        return Selection_Used_Median_Of_Medians(L2, k - ((int)L1.size()) - 1);
    }

}

int main()
{
    clock_t start, end;
    int n; //輸入個數
    int k; //選第幾小
    cout << "請輸入有幾個元素(n):"; cin >> n;
    cout << "請輸入一序列:";
    int values[SIZE] = { '0' };

    start = clock();
    for (int i = 0; i < n; i++)
    {
        cin >> values[i];

    }
    cout << "選擇第幾小資料(k=n): "; cin >> k;

    vector<int> vec(values, values + n);

    cout << "The given array is : " << endl;
    for (int i = 0; i < vec.size(); i++) {
        cout << right << setw(2) << fixed << vec[i] << "   ";
    }
    cout << endl;
    cout << "---------------------------------------------------------------------------------------" << endl << endl;
    cout << "【K=1的case】" << endl;
    Selection_Used_Median_Of_Medians(vec, n);
    cout << endl << endl;

    cout << "---------------------------------------------------------------------------------------" << endl << endl;
    cout << "【K=n/2取最大整數的case】" << endl;
    Selection_Used_Median_Of_Medians(vec, n / 2 + 1);
    cout << endl << endl;

    cout << "---------------------------------------------------------------------------------------" << endl << endl;
    cout << "【K=n的case】" << endl;
    Selection_Used_Median_Of_Medians(vec, n - k + 1);
    cout << endl << endl;
    end = clock();

    cout << "本次程式執行時間共" << float((end - start) / CLOCKS_PER_SEC) << "s" << endl << endl;
    system("pause");
    return 0;
}