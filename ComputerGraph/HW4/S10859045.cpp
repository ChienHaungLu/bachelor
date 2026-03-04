#include <gl/freeglut_std.h>
#include <gl/freeglut.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include <iostream>
#include <cmath>
#include<math.h>

#define PI 3.1415926
double move = 10.0;
int i = 0;
int down = 1;
int count = 1;
double timeSpan = 0;				//下降到底所需时间
double movey = 0.0;
double duration = 0.0;			//持续时间
double length = 0.0;
clock_t start, end;

void init(void)
{
	GLfloat mat_specular[] = { 220.220,220.0,220.0,220.0 };
	GLfloat mat_shininess[] = { 70.0 };
	GLfloat light_position[] = { 1.0,  1.0,  0.0,  0.0 };  //r-l u-d f-b
	GLfloat  ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat  diffuseLight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
	GLfloat  specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glClearColor(1.0, 1.0, 1.0, 0.0); //bgc
	glColor3ub(23, 17, 215);
	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	//glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-12, 12, -12 * (GLfloat)(h) / (GLfloat)(w), 12 * (GLfloat)(h) / (GLfloat)(w), -1.0, 1.0);
	else
		glOrtho(-12 * (GLfloat)(w) / (GLfloat)(h), 12 * (GLfloat)(w) / (GLfloat)(h), -12, 12, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void initDisplay(void)
{
	down = 1;					   //向下运动
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 20.0, 0.0);
	glColor3f(1, 0,0);
	glBegin(GL_QUADS);
	glVertex3f(-0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.0f);
	glEnd();
	glFlush();
	//glutSolidSphere(0.4, 40, 50);
	glutSwapBuffers();
}

void display()
{
	
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0, move, 0.0);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	
	glVertex3f(-0.5, -0.5, 0.0);
	glVertex3f(0.5, -0.5, 0.0);
	glVertex3f(0.5, 0.5, 0.0);
	glVertex3f(-0.5, 0.5, 0.0);
	glEnd();

	glFlush();
	//glutSolidSphere(0.4, 40, 50);
	glutSwapBuffers();
}
void MoveSphereUp()
{
	end = clock();
	duration = (double)(end - start - 16.0) / CLOCKS_PER_SEC;
	length = 5 * (timeSpan - duration) * (timeSpan - duration);
	move = 20 - length;
	if (move > 19.932) {
		move = 20;
		down = 1;
		printf("%i", down);
		start = clock();
	}
	display();
	glLoadIdentity();
}

void MoveSphereDown()
{
	if (count == 1) {
		start = clock();
		count = 0;
	}
	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC;
	length = (1.0/2.0*9.8) * duration * duration; // 1/2*gt^2
	move = 20 - length;
	if (move < -20) {
		timeSpan = duration;    //下降所經歷的時間
		move = -20;
		start = clock();
		down = 0;               //向上运动
	}
	display();
	glLoadIdentity();
}
/*
void TimerFunc2(int value) {
	if (i == 0) {    //left
		GLfloat light_position[] = { 2.0,0.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (i == 1) {    //left-up
		GLfloat light_position[] = { 2.0,2.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (i == 2) {   //up
		GLfloat light_position[] = { 0.0,2.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (i == 3) {   //up-right
		GLfloat light_position[] = { -2.0,2.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (i == 4) {   //right
		GLfloat light_position[] = { -2.0,0.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (i == 5) {   //right-down
		GLfloat light_position[] = { -2.0,-2.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (i == 6) {   //down
		GLfloat light_position[] = { 0.0,-2.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	if (i == 7) {   //down-left
		GLfloat light_position[] = { 2.0,-2.0,0.0,0.0 };  //r-l u-d f-b
		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
	glutTimerFunc(60, TimerFunc2, 1);
}*/

void TimerFunc1(int value) {
	if (down == 1) {
		MoveSphereDown();
	}
	/*
	if (down == 0) {
		MoveSphereUp();
	}*/
	glutTimerFunc(10, TimerFunc1, 0);
}





int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 740);
	glutInitWindowPosition(300, 20);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(initDisplay);
	glutReshapeFunc(reshape);

	glutTimerFunc(1400, TimerFunc1, 0); //毫秒
	//glutTimerFunc(400, TimerFunc2, 1);  //毫秒

	glutMainLoop();
	return 0;
}