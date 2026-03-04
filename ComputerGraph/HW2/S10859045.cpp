#include<GL/glut.h>	
#include<iostream>
#include<cmath>		
using namespace std;

//Volume Subdivision位置初始化
GLfloat v[4][3] = { {0.0, 0.0, sqrt(6) / 4}, {0.0, sqrt(3) / 3, sqrt(6) / 12}, {-0.5, -sqrt(3) / 6, sqrt(6) / 12} ,{0.5, -sqrt(3) / 6, sqrt(6) / 12} };
//Surface Subdivision位置初始化
GLfloat vplum[4][3] = { {0.0, 0.0, sqrt(6) / 4}, {0.0, sqrt(3) / 3, sqrt(6) / 12}, {-0.5, -sqrt(3) / 6, sqrt(6) / 12} ,{0.5, -sqrt(3) / 6, sqrt(6) / 12} };

int n; //全域變數宣告分割次數


//下面開始處理Surface Subdivision畫圖
void triangle(GLfloat* a, GLfloat* b, GLfloat* c)
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

//遞迴傳入引數 分別為頂點及切的次數
void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m)
{
	GLfloat v1[3], v2[3], v3[3];	//記錄切割ab bc ac的中點
	int j;
	if (m > 0)
	{
		for (j = 0; j < 3; j++) v1[j] = (a[j] + b[j]) / 2;	//point v1
		for (j = 0; j < 3; j++) v2[j] = (a[j] + c[j]) / 2; //point v2
		for (j = 0; j < 3; j++) v3[j] = (b[j] + c[j]) / 2;
		divide_triangle(a, v1, v2, m - 1);					//以point a呼叫遞迴 div
		divide_triangle(c, v2, v3, m - 1);					//以point c呼叫遞迴 div
		divide_triangle(b, v3, v1, m - 1);					
	}
	else
		triangle(a, b, c);	//當剩餘切的次數為0時 呼叫紀錄頂點的函式
}

//當遞迴到最小時依據三個頂點圍成的區域塗上顏色 而四個遞迴分別對應四個面
void tetrahedron(int m)
{
	//以下開始畫圖
	glColor3f(0.0, 1.0, 0.0);		
	divide_triangle(vplum[3], vplum[2], vplum[1], m);	//底
	glColor3f(0.0, 0.0, 0.0);		
	divide_triangle(vplum[0], vplum[2], vplum[3], m);	//側
	glColor3f(1.0, 0.0, 0.0);		
	divide_triangle(vplum[0], vplum[1], vplum[2], m);	//側
	glColor3f(0.0, 0.0, 1.0);		
	divide_triangle(vplum[0], vplum[3], vplum[1], m);	//側

}


//下面開始處理Volume Subdivision做圖
void color(GLfloat* x, GLfloat* y, GLfloat* z)
{
	glVertex3fv(x);
	glVertex3fv(y);
	glVertex3fv(z);
}

//分割成最小三角椎體並上色
void triangular_pyramid(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d)
{
	glColor3f(0.0, 0.0, 1.0);	
	color(a, b, c);				
	glColor3f(0.0, 1.0, 0.0);	
	color(a, c, d);				
	glColor3f(1.0, 0.0, 0.0);	
	color(a, b, d);				
}

//分割三角錐體
void divide_pyramid(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m)
{
	//椎體內的其他頂點
	GLfloat v1[3], v2[3], v3[3], v4[3], v5[3], v6[3];
	int j = 0;
	if (m == 0)
	{
		triangular_pyramid(a, b, c, d);		//當切的次數為0，則紀錄頂點及上色的函式會被呼叫
	}
	else
	{
		//計算兩頂點中心
		for (j = 0; j < 3; j++) v1[j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; j++) v2[j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) v3[j] = (a[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) v4[j] = (b[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) v5[j] = (b[j] + d[j]) / 2;
		for (j = 0; j < 3; j++) v6[j] = (c[j] + d[j]) / 2;

		//將三角椎體分割成四個小椎體
		divide_pyramid(a, v1, v2, v3, m - 1);
		divide_pyramid(v1, b, v4, v5, m - 1);
		divide_pyramid(v2, v4, c, v6, m - 1);
		divide_pyramid(v3, v5, v6, d, m - 1);

	}
}

//開始處理畫圖
void displayTriangle()		//Surface Subdivision畫圖     		
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glBegin(GL_TRIANGLES);								
	tetrahedron(n);
	glEnd();

	glFlush();				
}
void displayPyramid()		//Volume Subdivision畫圖
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_pyramid(v[0], v[1], v[2], v[3], n);
	glEnd();

	glFlush();				//通常情況下opengl的指令會先送到buffer 此為強制將指令送到硬體執行
}

//初始化opengl
void myinit()
{
	glEnable(GL_DEPTH_TEST);           
	glMatrixMode(GL_PROJECTION);		
	glLoadIdentity();					//重置當前矩陣
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);	
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);			//視窗顏色初始化
}


void mainMenu(int index) //呼叫submenu1元素分別為Surface Subdivision & Volume Subdivision
{
}

//定義點選此menu後的事件處理 以index作為參數識別user點選的內容
void subMenu1(int index)
{
	switch (index)
	{
	case 1:
		glutDisplayFunc(displayTriangle);	//繪新圖

		break;
	case 2:
		glutDisplayFunc(displayPyramid);	//繪新圖
		break;
	}
}

//點選menu的後續處理
void subMenu2(int nn)
{
	switch (nn)
	{
	case 2:		//nn==2 設定n=2
		n = 2;
		break;
	case 3:		//nn==3 設定n=3
		n = 3;
		break;
	case 4:		//nn==4 設定n=4
		n = 4;
		break;
	}
}

int main(int argc, char* argv[])
{
	int index;

	cout << "'1'為Surface Subdivision   '2'為Volume Subdivision " << endl;
	cout << "請輸入模式(數字): ";
	cin >> index;
	cout << "請輸入分割次數: ";
	cin >> n;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);	
	glutInitWindowPosition(100, 100);	//視窗位置初始化
	glutInitWindowSize(500, 500);		//視窗大小初始化
	glutCreateWindow("3D Gasket");      

	myinit();
	mainMenu(index);
	subMenu1(index);
	subMenu2(n);
	glutMainLoop();					   //使程式進入loop持續進行
}