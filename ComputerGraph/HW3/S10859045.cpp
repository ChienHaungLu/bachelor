#include<cmath>
#include<GL/glut.h> 

int n = 3; //預設分割次數
int p = 0;
GLfloat v[4][3] = { {0.0, 0.0, sqrt(6) / 4}, {0.0, sqrt(3) / 3, sqrt(6) / 12}, {-0.5, -sqrt(3) / 6, sqrt(6) / 12} ,{0.5, -sqrt(3) / 6, sqrt(6) / 12} }; //Volume Subdivision位置初始化
GLfloat vplum[4][3] = { {0.0, 0.0, sqrt(6) / 4}, {0.0, sqrt(3) / 3, sqrt(6) / 12}, {-0.5, -sqrt(3) / 6, sqrt(6) / 12} ,{0.5, -sqrt(3) / 6, sqrt(6) / 12} };//Surface Subdivision位置初始化

//下面開始處理Surface Subdivision畫圖
void triangle(GLfloat* a, GLfloat* b, GLfloat* c) //三角形頂點座標記錄
{
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void div_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m) //遞迴傳入引數 分別為頂點及切的次數
{
	GLfloat v1[3], v2[3], v3[3]; //記錄切割ab bc ac的中點
	int j;
	if (m > 0)
	{
		for (j = 0; j < 3; j++) v1[j] = (a[j] + b[j]) / 2; //point v1
		for (j = 0; j < 3; j++) v2[j] = (a[j] + c[j]) / 2; //point v2
		for (j = 0; j < 3; j++) v3[j] = (b[j] + c[j]) / 2; 
		div_triangle(a, v1, v2, m - 1);     //以point a呼叫遞迴 div
		div_triangle(c, v2, v3, m - 1);     //以point b呼叫遞迴 div
		div_triangle(b, v3, v1, m - 1);     
	}
	else
		triangle(a, b, c); //當切的次數為0，則紀錄頂點的函式會被呼叫
}

//當遞迴到最小時依據三個頂點圍成的區域塗上顏色 而四個遞迴分別對應四個面
void tetrahedron(int m)
{	//glColor3f(R,G,B)
	glColor3f(0.0, 1.0, 0.0); 
	div_triangle(vplum[3], vplum[2], vplum[1], m); //底部
	glColor3f(0.0, 0.0, 0.0);  
	div_triangle(vplum[0], vplum[2], vplum[3], m); //側邊
	glColor3f(1.0, 0.0, 0.0); 
	div_triangle(vplum[0], vplum[1], vplum[2], m); //側邊
	glColor3f(0.0, 0.0, 1.0); 
	div_triangle(vplum[0], vplum[3], vplum[1], m); //側邊

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
	//glColor3f(R,G,B)
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
	GLfloat v1[3], v2[3], v3[3], v4[3], v5[3], v6[3];
	int j = 0;
	if (m == 0)
	{
		triangular_pyramid(a, b, c, d);  //當切的次數為0，則紀錄頂點及上色的函式會被呼叫
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
void displayTriangle()  //Surface Subdivision畫圖     
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glBegin(GL_TRIANGLES);       
	tetrahedron(n);
	glEnd();
	glFlush();    
}
void displayPyramid()  //Volume Subdivision畫圖
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	divide_pyramid(v[0], v[1], v[2], v[3], n);
	glEnd();
	glFlush();    
}

void myinit()
{
	glEnable(GL_DEPTH_TEST);            
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();    
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.0, 0.0, 0.0);  
}

void mainMenu(int i) //呼叫submenu1元素分別為Surface Subdivision & Volume Subdivision
{
}


//點選menu的後續處理
void subMenu1(int i)
{
	switch (i)
	{
	case 1:
		glutPostRedisplay();   
		glutDisplayFunc(displayTriangle); //畫新圖
		myinit();
		break;
	case 2:
		glutPostRedisplay();   
		glutDisplayFunc(displayPyramid); //畫新圖
		myinit();
		break;
	}
}

//點選menu的後續處理
void subMenu2(int i)
{
	switch (i)
	{
	case 1:  n = 2; break;
	case 2:  n = 3;; break;
	case 3: n = 4; break;
	}
}

void subMenu3(int p)
{
	exit(0);
}

//Define menu生成、階層
void creatMenu()
{
	int mainmenu = glutCreateMenu(mainMenu);

	//生成的圖形type
	int submenu1 = glutCreateMenu(subMenu1);
	glutAddMenuEntry("Surface Subdivision", 1);
	glutAddMenuEntry("Volume Subdivision", 2);

	//Define切割次數
	int submenu2 = glutCreateMenu(subMenu2);
	glutAddMenuEntry("2", 1);
	glutAddMenuEntry("3", 2);
	glutAddMenuEntry("4", 3);

	//Exit專用
	int submenu3 = glutCreateMenu(subMenu3);

	//生成主選單底下新增兩個子選單分別為 submenu1 & submenu2
	glutAddSubMenu("3D Gasket", submenu1);
	glutAddSubMenu("SubdivisionLevel", submenu2);
	glutAddMenuEntry("Exit", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON); //觸發menu得先按滑鼠右鍵
}


void keyboard(unsigned char key, int x, int y)
{
	if (key == 'Q' || key == 'q')	//按q或Q退出
		exit(0);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH); 
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(500, 500);  
	glutCreateWindow("3D Gasket");     
	creatMenu();     
	glutKeyboardFunc(keyboard);  
	glutDisplayFunc(displayTriangle);
	myinit();
	glutMainLoop();       
}
