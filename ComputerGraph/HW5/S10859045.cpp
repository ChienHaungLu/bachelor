#define  _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <math.h>
#include <cmath>
#include<GL/glu.h>
#include<GL/glut.h>
#include <GL/glut.h>
#define PI 3.14

int n = 8;  //分割三角形8塊
static GLfloat spin = 2.5; //轉速
int surfaceID = 1;
int angle = 1; //2:Y  1:Z  0:X
int the_run = 0; //程式一開啟的旋轉模式，預設為暫停  1:順  

GLfloat vertex[4][3] = { {0,0,0.50},{0,0.70,0 },{-0.6,0,-0.25},{0.6,0,-0.25} };
GLfloat the_diffuse[] = { 0.8,0.2,0.5,1.0 };
GLfloat the_specular[] = { 1.0,1.0,1.0,1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 6.0 };
GLfloat high_shininess[] = { 150.0 };
GLfloat mat_emission[] = { 0.3,0.2,0.2,0.0 };
GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };


void triangle(GLfloat* x, GLfloat* y, GLfloat* z)
{
	glVertex3fv(x);
	glVertex3fv(y);
	glVertex3fv(z);
}

void tetrahedron(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d)
{
	glColor3f(0.0, 1.0, 0.0);
	triangle(a, b, d);
	glColor3f(0.0, 1.0, 0.0);
	triangle(a, d, c);
	glColor3f(0.0, 1.0, 0.0);
	triangle(b, d, c);
	glColor3f(0.0, 1.0, 0.0);
	triangle(a, b, c);
}

void divide_triangle(GLfloat* a, GLfloat* b, GLfloat* c, GLfloat* d, int m)
{
	GLfloat v1[3] = {}, v2[3] = {}, v3[3] = {}, v4[3] = {}, v5[3] = {}, v6[3] = {};
	int j;
	if (m > 0)
	{
		for (j = 0; j < 3; j++) v1[j] = (a[j] + b[j]) / 2.2;
		for (j = 0; j < 3; j++) v2[j] = (a[j] + c[j]) / 2.2;
		for (j = 0; j < 3; j++) v3[j] = (a[j] + d[j]) / 2.2;
		for (j = 0; j < 3; j++) v4[j] = (b[j] + c[j]) / 2.2;
		for (j = 0; j < 3; j++) v5[j] = (d[j] + b[j]) / 2.2;
		for (j = 0; j < 3; j++) v6[j] = (d[j] + c[j]) / 2.2;

		divide_triangle(a, v1, v2, v3, m - 1);
		divide_triangle(v1, b, v4, v5, m - 1);
		divide_triangle(v3, v5, v6, d, m - 1);
		divide_triangle(v2, v4, c, v6, m - 1);
	}
	else(tetrahedron(a, b, c, d));

}

void triangle_funct(GLfloat* x, GLfloat* y, GLfloat* z)
{
	glVertex3fv(x);
	glVertex3fv(y);
	glVertex3fv(z);
}

void divide_the_triangle(GLfloat* a, GLfloat* b, GLfloat* c, int m)
{
	GLfloat v1[3], v2[3], v3[3];
	int j;
	if (m > 0)
	{
		for (j = 0; j < 3; j++) v1[j] = (a[j] + b[j]) / 2;
		for (j = 0; j < 3; j++) v2[j] = (a[j] + c[j]) / 2;
		for (j = 0; j < 3; j++) v3[j] = (b[j] + c[j]) / 2;
		divide_the_triangle(a, v1, v2, m - 1);
		divide_the_triangle(c, v2, v3, m - 1);
		divide_the_triangle(b, v3, v1, m - 1);
	}
	else(triangle_funct(a, b, c));
}

void tetrahedron_funct(int m)
{
	glColor3f(0.0, 1.0, 0.0); 
	glNormal3f(0.0, 1.0, 0.0);
	glNormal3fv(vertex[0]);
	
	divide_the_triangle(vertex[0], vertex[1], vertex[2], m);

	glColor3f(0.0, 1.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glNormal3fv(vertex[3]);
	divide_the_triangle(vertex[3], vertex[2], vertex[1], m);

	glColor3f(0.0, 1.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glNormal3fv(vertex[0]);
	divide_the_triangle(vertex[0], vertex[3], vertex[1], m);

	glColor3f(0.0, 1.0, 0.0);
	glNormal3f(0.0, 1.0, 0.0);
	glNormal3fv(vertex[0]);
	divide_the_triangle(vertex[0], vertex[2], vertex[3], m);
}


void draw_the_cylinder(GLfloat r, GLfloat height, GLubyte RED, GLubyte GREEN, GLubyte BLUE)
{
	GLfloat x = 0.0;
	GLfloat y = 0.0;
	GLfloat angle = 0.0;
	GLfloat angle_stepsize = 0.1;

	//木頭部分的表皮上色
	glColor3ub(RED , GREEN , BLUE);
	glBegin(GL_QUAD_STRIP);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = r * cos(angle);
		y = r * sin(angle);
		glVertex3f(x, height * -1, y);
		glVertex3f(x, 0.0, y);
		angle = angle + angle_stepsize;
	}
	glVertex3f(r, height * -1, 0.0);
	glVertex3f(r, 0.0, 0.0);
	glEnd();

	//木頭部分底座
	glColor3ub(RED, GREEN, BLUE);
	glBegin(GL_POLYGON);
	angle = 0.0;
	while (angle < 2 * PI) {
		x = r * cos(angle);
		y = r * sin(angle);
		glVertex3f(x, height * -1, y);
		angle = angle + angle_stepsize;
	}
	glVertex3f(r, height * -1, 0.0);
	glEnd();
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, the_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, the_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_POLYGON);
	glLoadIdentity();

	glEnd();
	draw_the_cylinder(0.1, 0.5, 116, 53,2);  //木頭部分
	//glFlush();

	if (the_run == 1)
	{
		if (angle == 0)
		{
			glRotatef(spin, 1, 0, 0);
		}
		if (angle == 1)
		{
			glRotatef(spin, 0, 1, 0);
		}
		if (angle == 2)
		{
			glRotatef(spin, 0, 0, 1);
		}
	}
	/*if (the_run == 2)
	{
		if (angle == 0)
		{
			glRotatef(spin, -1, 0, 0);

		}
		if (angle == 1)
		{
			glRotatef(spin, 0, -1, 0);
		}
		if (angle == 2)
		{
			glRotatef(spin, 0, 0, -1);
		}
	}*/
	/*
	if (surfaceID == 0)
	{
		glBegin(GL_TRIANGLES);
		tetrahedron_funct(n);
		glEnd();
		glFlush();
	}*/

	if (surfaceID == 1)
	{
		glBegin(GL_TRIANGLES);
		divide_triangle(vertex[0], vertex[1], vertex[2], vertex[3], n);
		glEnd();
		glFlush();
	}

}


void initial()
{
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	//打光 光源環境設定...
	GLfloat the_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat the_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat the_specular[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat the_light[] = { 1.0, 3.0, 5,0, 0.0 };
	glEnable(GL_LIGHT5);
	glLightfv(GL_LIGHT5, GL_POSITION, the_light);
	glLightfv(GL_LIGHT5, GL_AMBIENT, the_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, the_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, the_specular);
	
	glLightModeli(GL_LIGHT_MODEL_AMBIENT, GL_TRUE);
	gluOrtho2D(-0.5, -0.5, -0.5, -0.5);
	glMatrixMode(GL_MODELVIEW);

	glClearColor(1, 1, 1, 1);
	glColor3f(0.0, 0.0, 0.0);

}


void submenu(int num)
{
	/*
	if (num == 1)
	{
		surfaceID = 0;
	}
	if (num == 2)
	{
		surfaceID = 1;
	}*/
	glutPostRedisplay();
}

void submenu3(int num)
{

}

void submenu4(int num)
{
	if (num == 6)
	{
		angle = 0;
	}
	if (num == 8)
	{
		angle = 1;
	}
	if (num == 7)
	{
		angle = 2;
	}
}

void submenu5(int num)
{
	if (num == 9)
	{
		the_run = 0;
	}
	if (num == 10)
	{
		the_run = 1;
	}
	if (num == 11)
	{
		the_run = 2;
	}
}

void inputkey(unsigned char key, int x, int y)
{
	if (key == 'E' || key == 'e')
	{
		exit(0);
	}
}


int main(int argc, char** argv)
{
	int Main_menu, Submenu, Submenu2, Submenu3, Submenu4, Submenu5;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("S10859045");


	Submenu4 = glutCreateMenu(submenu4);
	glutAddMenuEntry("X_axis", 6);
	glutAddMenuEntry("Y_axis", 7);
	glutAddMenuEntry("Z_axis", 8);


	Submenu5 = glutCreateMenu(submenu5);
	glutAddMenuEntry("Wait", 9);
	glutAddMenuEntry("The_Clockwise ", 10);
	//glutAddMenuEntry("The_Counter_Clockwise", 11);

	/*
	Submenu = glutCreateMenu(submenu);
	glutAddMenuEntry("Surface Subdivision", 1);
	glutAddMenuEntry("Volumne Subdivision ", 2);*/

	Submenu3 = glutCreateMenu(submenu3);
	glutAddSubMenu("rotation_axis", Submenu4);
	glutAddSubMenu("rotation_direction ", Submenu5);

	Main_menu = glutCreateMenu(submenu);
	//glutAddSubMenu("3D gasket", Submenu);
	glutAddSubMenu("Rotation", Submenu3);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutKeyboardFunc(inputkey);
	glutDisplayFunc(display);
	glutIdleFunc(display);

	initial();
	glutMainLoop();

}
