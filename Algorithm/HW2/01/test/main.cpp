#include<stdlib.h>
#include<stdio.h>
#include<cmath>
#include<string.h>
#include<algorithm>
#include <iostream>
using namespace std;

struct point
{
	double x;
	double y;
};

double Distance(point a,point b)
{
	double s = sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
	return s;
}

//依x軸排序
bool sort1(point a, point b)
{
	return a.x < b.x;
}

//依y軸排序
bool sort2(point a, point b)
{
	return a.y < b.y;
}

double closestpoint(point s[],const int low,const int high, point r[])
{	
	int i, j, index, middle;
	double x1, y1, x2, y2; //記錄最近的兩點位置(x1,y1)(x2,y2)
	double distance1, distance2, distance3, distance;
	
	point P[high - low + 1], set1[2], set2[2], set3[2]; //set1記錄左集合,set2記錄右集合,set3則記錄中間垂直帶的
	
	//當只有兩個點
	if (high - low == 1)
	{
		r[0].x = s[low].x;
		r[0].y = s[low].y;
		r[1].x = s[high].x;
		r[1].y = s[high].y;
	}
	else if (high - low == 2)
	{
		distance1 = Distance(s[low], s[low + 1]);
		distance2 = Distance(s[low + 1], s[high]);
		distance3 = Distance(s[low], s[high]);
		if ((distance1 < distance2) && (distance1 < distance3))
		{
			r[0].x = s[low].x;
			r[0].y = s[low].y;
			r[1].x = s[low + 1].x;
			r[1].y = s[low + 1].y;
			return distance1;
		}
		else if (distance2 < distance3)
		{
			r[0].x = s[low + 1].x;
			r[0].y = s[low + 1].y;
			r[1].x = s[high].x;
			r[1].y = s[high].y;
			return distance2;
		}
		else
		{
			r[0].x = s[low].x;
			r[0].y = s[low].y;
			r[1].x = s[high].x;
			r[1].y = s[high].y;
			return distance3;
		}
	}
	else
	{
		middle = (low + high) / 2;
		distance1 = closestpoint(s, low, middle, r);
		set1[0] = r[0];
		set1[1] = r[1];
		distance2 = closestpoint(s,middle+1,high, r);
		set2[0] = r[0];
		set2[1] = r[1];
		if (distance1 < distance2)
		{
			distance = distance1;
			r[0] = set1[0];
			r[1] = set1[1];
		}
		else
		{
			distance = distance2;
			r[0] = set2[0];
			r[1] = set2[1];
		}

		index = 0;
		for (i = middle; (i >= low) && ((s[middle].x - s[i].x) < distance); i--)
		{
			P[index++] = s[i];
		}
		for (i = middle+1; (i <= high) && ((s[i].x - s[middle].x) < distance); i++)
		{
			P[index++] = s[i];
		}
		sort(P, P + index, sort2);
		for (i = 0; i < index; i++)
		{
			for (j = i + 1; j < i + 7 && j < index; j++)
			{
				if ((P[j].y - P[i].y) >= distance)
				{
					break;
				}
				else
				{
					distance3 = Distance(P[i], P[j]);
					if (distance3 < distance)
					{
						r[0].x = P[i].x;
						r[0].y = P[i].y;
						r[1].x = P[j].x;
						r[1].y = P[j].y;
						distance = distance3;
					}
				}
			}
		}
		return distance;
	}
}

int main()
{
	point p[100];
	int n;
	double dmin;
	cout << "請輸入點的個數:"; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout<<"請輸入第"<<i+1<<"座標:";
		cin>>p[i].x ; cin>>p[i].y ;
		
	}
	sort(p, p + n, sort1);
	point index[2];
	dmin = closestpoint(p, 0, n - 1, index);
	
	cout << "最小距離為: " << dmin << endl;
	cout << endl << "最小距離的點為: (" << index[0].x << "," << index[0].y << "),(" << index[1].x << "," << index[1].y << ")" << endl;
	system("pause");
	return 0;
}
