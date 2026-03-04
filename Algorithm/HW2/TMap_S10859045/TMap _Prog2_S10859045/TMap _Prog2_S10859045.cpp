#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <algorithm>
#define PI 3.1415926535897
using namespace std;

class Point
{
private:
    double x;
    double y;
    double angle;
public:
    void get_coords(double a, double b)
    {
        x = a;
        y = b;
    }
    void set_angle(double ang)
    {
        angle = ang;
    }
    double get_x()
    {
        return x;
    }
    double get_y()
    {
        return y;
    }
    double obtain_angle() const
    {
        return angle;
    }
};

int obtain_orientation(Point P1, Point P2, Point P);
bool internal(Point P1, Point P2, Point P3, Point P);
int random_point(vector<Point> P);
bool sort_angle(Point& P1, Point& P2);
double maxDist(pair<long, long> p[], int n);

int obtain_orientation(Point P1, Point P2, Point P)
{
    double orientation = ((P2.get_x() - P1.get_x()) * (P.get_y() - P1.get_y()) - (P2.get_y() - P1.get_y()) * (P.get_x() - P1.get_x()));
    if (orientation > 0)
    {
        return 1;
    }
    else if (orientation < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

bool internal(Point P1, Point P2, Point P3, Point P)
{
    int line1 = obtain_orientation(P1, P2, P);
    int line2 = obtain_orientation(P2, P3, P);
    int line3 = obtain_orientation(P3, P1, P);
    return ((line1 == line2) && (line2 == line3));
}

int random_point(vector<Point> P)
{
    double min_x;
    int minimum;
    minimum = 0;
    min_x = P[0].get_x();
    for (int i = 1; i < P.size(); i++)
    {
        if (P[i].get_x() < min_x)
        {
            min_x = P[i].get_x();
            minimum = i;
        }
    }
    return minimum;
}

bool sort_angle(Point& P1, Point& P2)
{
    return (P1.obtain_angle() < P2.obtain_angle());
}

long dist(pair<long, long> p1,
    pair<long, long> p2)
{
    long x0 = p1.first - p2.first;
    long y0 = p1.second - p2.second;
    return x0 * x0 + y0 * y0;
}

// Function to find the maximum
// distance between any two points
double maxDist(pair<long, long> p[], int n)
{
    double Max = 0;

    // Iterate over all possible pairs
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {

            // Update max
            Max = max(Max, (double)dist(p[i],
                p[j]));
        }
    }

    // Return actual distance
    return sqrt(Max);
}

int main(int argc, char* argv[])
{
    const char* filename = argv[1];
    const int nn = 8;
    pair<long, long> p[nn];
    ifstream inFile("filename.txt");
    Point t;
    vector<Point> P, convex_hull;
    vector<int> external;

    int pts, exter = 1;
    int a, b, a_point;
    int count = 0;
    double compute_area = 0;



    if (!inFile) {
        cout << endl << "Can't open input file - " << filename;
        system("PAUSE");
        return 1;
    }
    pts = 0;
    while (!inFile.eof())
    {
        inFile >> a;
        inFile >> b;
        t.get_coords(a, b);
        P.push_back(t);
        pts++;
    }

    for (int i = 0; i < pts; i++)
    {
        external.push_back(i);
    }

    a_point = random_point(P);
    P[a_point].set_angle(PI);

    for (int i = 0; i < P.size(); i++)
    {

        if (P[i].obtain_angle() != P[a_point].obtain_angle())
        {
            P[i].set_angle(atan2(P[i].get_y() - P[a_point].get_y(), P[i].get_x() - P[a_point].get_x()));
        }
    }

    cout << "輸入的檔案資料偵測到" << pts << "個點" << endl << endl;
    cout << "在內部點有:";
    for (int i = 0; i < pts; i++)
    {
        for (int j = i + 1; j < pts; j++)
        {
            if (j != i)
            {
                for (int k = j + 1; k < pts; k++)
                {
                    if (k != j && k != i)
                    {
                        for (int l = 0; l < pts; l++)
                        {
                            if (l != i && l != j && l != k && external[l] != -1) //&& external[l] != -1
                            {
                                if (internal(P[i], P[j], P[k], P[l]))
                                {
                                    cout << "(" << P[external[l]].get_x() << "," << P[external[l]].get_y() << ") ";
                                    count++;
                                    external[l] = -1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    external.erase(remove(external.begin(), external.end(), -1), external.end());

    exter = external.size();
    compute_area = 0;

    for (int i = 0; i < exter; i++) {
        if (external[i] != -1) {
            convex_hull.push_back(P[external[i]]);
        }
    }
    cout << endl << endl;

    sort(convex_hull.begin(), convex_hull.end(), sort_angle);

    cout << "包圍所形成Convex Hull的點:" << endl;
    cout << " X座標  Y座標" << endl;
    for (int j, i = 0; i < convex_hull.size(); i++) {
        cout << "(" << convex_hull[i].get_x() << ", " << convex_hull[i].get_y() << ")  " << endl;
        j = (i + 1) % exter;
        compute_area += convex_hull[i].get_x() * convex_hull[j].get_y();
        compute_area -= convex_hull[i].get_y() * convex_hull[j].get_x();
    }

    cout << "總面積為: " << abs(compute_area) << endl;

    for (int i = 0; i < pts; i++)
    {
        p[i].first = convex_hull[i].get_x(); p[i].second = convex_hull[i].get_y();
    }

    cout << "最長距離為:" << fixed << setprecision(3) << maxDist(p, nn) << endl << endl;
    system("PAUSE");
    return 0;
}



