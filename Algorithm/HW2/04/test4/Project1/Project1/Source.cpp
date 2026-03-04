#include <iostream>
#include <vector>	
#include <cfloat>	
#include <cmath>	
#include <fstream>	
#include <sstream>	
using namespace std;

class Point
{
public:
	int x;
	int y;
};

class HungarianMethod
{
public:
	HungarianMethod();
	~HungarianMethod();
	double Solve(vector <vector<double> >& DistanceMatrix, vector<int>& Assignment);

private:
	void optimal(int* assignment, double* cost, double* DistanceMatrix, int nOfRows, int nOfColumns);
	void buildassignmentvector(int* assignment, bool* starMatrix, int nOfRows, int nOfColumns);
	void compute_cost(int* assignment, double* cost, double* DistanceMatrix, int nOfRows);
	void HungarianMethod_step2a(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
	void HungarianMethod_step2b(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
	void HungarianMethod_step3(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
	void HungarianMethod_step4(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col);
	void HungarianMethod_step5(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim);
};

HungarianMethod::HungarianMethod() {}
HungarianMethod::~HungarianMethod() {}

int minP1 = 0;
int minP2 = 0;
double HungarianMethod::Solve(vector <vector<double> >& DistanceMatrix, vector<int>& Assignment)
{
	unsigned int nRows = DistanceMatrix.size();
	unsigned int nCols = DistanceMatrix[0].size();
	double* DistanceMatrixIn = new double[nRows * nCols];
	int* assignment = new int[nRows];
	double cost = 0.0;

	for (unsigned int i = 0; i < nRows; i++)
		for (unsigned int j = 0; j < nCols; j++)
			DistanceMatrixIn[i + nRows * j] = DistanceMatrix[i][j];

	optimal(assignment, &cost, DistanceMatrixIn, nRows, nCols);

	Assignment.clear();
	for (unsigned int r = 0; r < nRows; r++)
		Assignment.push_back(assignment[r]);

	delete[] DistanceMatrixIn;
	delete[] assignment;
	return cost;
}

void HungarianMethod::optimal(int* assignment, double* cost, double* DistanceMatrixIn, int nOfRows, int nOfColumns)
{
	double* DistanceMatrix, * DistanceMatrixTemp, * DistanceMatrixEnd, * columnEnd, value, MinimumValue;
	bool* coveredColumns, * coveredRows, * starMatrix, * newStarMatrix, * primeMatrix;
	int nOfElements, minDim, row, col;
	*cost = 0;
	for (row = 0; row < nOfRows; row++)
		assignment[row] = -1;

	nOfElements = nOfRows * nOfColumns;
	DistanceMatrix = (double*)malloc(nOfElements * sizeof(double));
	DistanceMatrixEnd = DistanceMatrix + nOfElements;

	//檢查所有element是否>=0 ??
	for (row = 0; row < nOfElements; row++)
	{
		value = DistanceMatrixIn[row];
		if (value < 0)
			cout << "所有的element應該>=0" << endl;
		DistanceMatrix[row] = value;
	}

	coveredColumns = (bool*)calloc(nOfColumns, sizeof(bool));
	coveredRows = (bool*)calloc(nOfRows, sizeof(bool));
	starMatrix = (bool*)calloc(nOfElements, sizeof(bool));
	primeMatrix = (bool*)calloc(nOfElements, sizeof(bool));
	newStarMatrix = (bool*)calloc(nOfElements, sizeof(bool));

	if (nOfRows <= nOfColumns)
	{
		minDim = nOfRows;

		for (row = 0; row < nOfRows; row++)
		{
			DistanceMatrixTemp = DistanceMatrix + row;
			MinimumValue = *DistanceMatrixTemp;
			DistanceMatrixTemp += nOfRows;
			while (DistanceMatrixTemp < DistanceMatrixEnd)
			{
				value = *DistanceMatrixTemp;
				if (value < MinimumValue)
					MinimumValue = value;
				DistanceMatrixTemp += nOfRows;
			}

			// 找出row中最小的元素 
			DistanceMatrixTemp = DistanceMatrix + row;
			while (DistanceMatrixTemp < DistanceMatrixEnd)
			{
				*DistanceMatrixTemp -= MinimumValue;
				DistanceMatrixTemp += nOfRows;
			}
		}

		for (row = 0; row < nOfRows; row++)
			for (col = 0; col < nOfColumns; col++)
				if (fabs(DistanceMatrix[row + nOfRows * col]) < DBL_EPSILON)
					if (!coveredColumns[col])
					{
						starMatrix[row + nOfRows * col] = true;
						coveredColumns[col] = true;
						break;
					}
	}
	else
	{
		minDim = nOfColumns;
		for (col = 0; col < nOfColumns; col++)
		{
			//找row中的最小值
			DistanceMatrixTemp = DistanceMatrix + nOfRows * col;
			columnEnd = DistanceMatrixTemp + nOfRows;

			MinimumValue = *DistanceMatrixTemp++;
			while (DistanceMatrixTemp < columnEnd)
			{
				value = *DistanceMatrixTemp++;
				if (value < MinimumValue)
					MinimumValue = value;
			}

			//找column中最小值
			DistanceMatrixTemp = DistanceMatrix + nOfRows * col;
			while (DistanceMatrixTemp < columnEnd)
				*DistanceMatrixTemp++ -= MinimumValue;
		}

		for (col = 0; col < nOfColumns; col++)
			for (row = 0; row < nOfRows; row++)
				if (fabs(DistanceMatrix[row + nOfRows * col]) < DBL_EPSILON)
					if (!coveredRows[row])
					{
						starMatrix[row + nOfRows * col] = true;
						coveredColumns[col] = true;
						coveredRows[row] = true;
						break;
					}
		for (row = 0; row < nOfRows; row++)
			coveredRows[row] = false;

	}

	HungarianMethod_step2b(assignment, DistanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
	compute_cost(assignment, cost, DistanceMatrixIn, nOfRows);

	free(DistanceMatrix);
	free(coveredColumns);
	free(coveredRows);
	free(starMatrix);
	free(primeMatrix);
	free(newStarMatrix);

	return;
}

//cost的計算
void HungarianMethod::buildassignmentvector(int* assignment, bool* starMatrix, int nOfRows, int nOfColumns)
{
	int row, col;

	for (row = 0; row < nOfRows; row++)
		for (col = 0; col < nOfColumns; col++)
			if (starMatrix[row + nOfRows * col])
			{
				assignment[row] = col + 1;
				assignment[row] = col;
				break;
			}
}

void HungarianMethod::compute_cost(int* assignment, double* cost, double* DistanceMatrix, int nOfRows)
{
	int row, col;

	for (row = 0; row < nOfRows; row++)
	{
		col = assignment[row];
		if (col >= 0)
			*cost += DistanceMatrix[row + nOfRows * col];
	}
}


void HungarianMethod::HungarianMethod_step2a(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim)
{
	bool* starMatrixTemp, * columnEnd;
	int col;

	for (col = 0; col < nOfColumns; col++)
	{
		starMatrixTemp = starMatrix + nOfRows * col;
		columnEnd = starMatrixTemp + nOfRows;
		while (starMatrixTemp < columnEnd) {
			if (*starMatrixTemp++)
			{
				coveredColumns[col] = true;
				break;
			}
		}
	}

	HungarianMethod_step2b(assignment, DistanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void HungarianMethod::HungarianMethod_step2b(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim)
{
	int col, nOfCoveredColumns;
	nOfCoveredColumns = 0;
	for (col = 0; col < nOfColumns; col++)
		if (coveredColumns[col])
			nOfCoveredColumns++;
	if (nOfCoveredColumns == minDim)
	{
		buildassignmentvector(assignment, starMatrix, nOfRows, nOfColumns);
	}
	else
	{
		HungarianMethod_step3(assignment, DistanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
	}

}

//檢查各列  碰上的第一個0做記號 
void HungarianMethod::HungarianMethod_step3(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim)
{
	bool zerosFound;
	int row, col, starCol;

	zerosFound = true;
	while (zerosFound)
	{
		zerosFound = false;
		for (col = 0; col < nOfColumns; col++)
			if (!coveredColumns[col])
				for (row = 0; row < nOfRows; row++)
					if ((!coveredRows[row]) && (fabs(DistanceMatrix[row + nOfRows * col]) < DBL_EPSILON))
					{
						primeMatrix[row + nOfRows * col] = true;
						for (starCol = 0; starCol < nOfColumns; starCol++)
							if (starMatrix[row + nOfRows * starCol])
								break;

						if (starCol == nOfColumns)
						{
							HungarianMethod_step4(assignment, DistanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim, row, col);
							return;
						}
						else
						{
							coveredRows[row] = true;
							coveredColumns[starCol] = false;
							zerosFound = true;
							break;
						}
					}
	}

	HungarianMethod_step5(assignment, DistanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void HungarianMethod::HungarianMethod_step4(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim, int row, int col)
{
	int n, starRow, starCol, primeRow, primeCol;
	int nOfElements = nOfRows * nOfColumns;


	for (n = 0; n < nOfElements; n++)
		newStarMatrix[n] = starMatrix[n];

	newStarMatrix[row + nOfRows * col] = true;

	starCol = col;
	for (starRow = 0; starRow < nOfRows; starRow++)
		if (starMatrix[starRow + nOfRows * starCol])
			break;

	while (starRow < nOfRows)
	{

		newStarMatrix[starRow + nOfRows * starCol] = false;

		primeRow = starRow;
		for (primeCol = 0; primeCol < nOfColumns; primeCol++)
			if (primeMatrix[primeRow + nOfRows * primeCol])
				break;

		newStarMatrix[primeRow + nOfRows * primeCol] = true;


		starCol = primeCol;
		for (starRow = 0; starRow < nOfRows; starRow++)
			if (starMatrix[starRow + nOfRows * starCol])
				break;
	}

	for (n = 0; n < nOfElements; n++)
	{
		primeMatrix[n] = false;
		starMatrix[n] = newStarMatrix[n];
	}
	for (n = 0; n < nOfRows; n++)
		coveredRows[n] = false;

	HungarianMethod_step2a(assignment, DistanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

void HungarianMethod::HungarianMethod_step5(int* assignment, double* DistanceMatrix, bool* starMatrix, bool* newStarMatrix, bool* primeMatrix, bool* coveredColumns, bool* coveredRows, int nOfRows, int nOfColumns, int minDim)
{
	double h, value;
	int row, col;

	h = DBL_MAX;
	for (row = 0; row < nOfRows; row++)
		if (!coveredRows[row])
			for (col = 0; col < nOfColumns; col++)
				if (!coveredColumns[col])
				{
					value = DistanceMatrix[row + nOfRows * col];
					if (value < h)
						h = value;
				}


	for (row = 0; row < nOfRows; row++)
		if (coveredRows[row])
			for (col = 0; col < nOfColumns; col++)
				DistanceMatrix[row + nOfRows * col] += h;


	for (col = 0; col < nOfColumns; col++)
		if (!coveredColumns[col])
			for (row = 0; row < nOfRows; row++)
				DistanceMatrix[row + nOfRows * col] -= h;

	HungarianMethod_step3(assignment, DistanceMatrix, starMatrix, newStarMatrix, primeMatrix, coveredColumns, coveredRows, nOfRows, nOfColumns, minDim);
}

int main(void)
{
	Point P1[500];
	Point Man2[500];
	double distancePM[100][100];
	string data;
	Point* P2 = NULL;
	fstream file, file2;
	file.open("people.txt", ios::in);	//遊客位置座標檔
	file2.open("point.txt", ios::in);	//景點位置座標檔

	if (!file && !file2)				//兩個檔案無法開啟之錯誤訊息
		cout << "檔案無法開啟" << endl;

	int i = 0;
	while (getline(file, data))
	{
		stringstream temp(data);
		string x;
		string y;
		getline(temp, x, ' ');
		getline(temp, y, ' ');
		istringstream forIntX(x);
		istringstream forIntY(y);

		forIntX >> P1[i].x;
		forIntY >> P1[i].y;
		i++;
	}
	P2 = new Point[i + 1];
	for (int j = 0; j <= i; j++)
	{
		P2[j].x = P1[j].x;
		P2[j].y = P1[j].y;
	}
	int n = 1;
	n = i;

	double closest_distance = 0;

	vector< vector<double> >  costMatrix;
	vector <double> costrow;
	int j = 0;
	while (getline(file2, data))
	{
		stringstream temp(data);
		string x;
		string y;
		getline(temp, x, ' ');
		getline(temp, y, ' ');
		istringstream forIntX(x);
		istringstream forIntY(y);
		forIntX >> Man2[j].x;
		forIntY >> Man2[j].y;
		for (int k = 0; k < i; k++)
		{
			double xpow = pow(P1[k].x - Man2[j].x, 2);
			double ypow = pow(P1[k].y - Man2[j].y, 2);
			distancePM[j][k] = abs(sqrt(xpow + ypow));
			double distance = 0;
			distance = distancePM[j][k];
			costrow.push_back(distancePM[j][k]);

		}
		costMatrix.push_back(costrow);
		j++;
	}
	cout << "從景點檔案讀取座標如下" << endl;
	for (int p = 0; p < j; p++)
	{
		cout << "景點" << p + 1 << ": (" << Man2[p].x << "," << Man2[p].y << ")" << endl;
	}
	cout << endl;
	HungarianMethod hungarian;
	vector<int> assignment;
	double cost = hungarian.Solve(costMatrix, assignment);
	for (unsigned int i = 0; i < costMatrix.size(); i++)
	{
		int point = assignment[i];
		cout << "第" << i + 1 << "位遊客的位置" << "：" << "(" << P1[point].x << "," << P1[point].y << ")" << endl;
	}
	cout << "\n最少的總距離之總和為： " << cost << endl << endl;

	file.close();	file2.close(); //關閉檔案
	delete P2;
	system("PAUSE");
	return (0);
}