
#include<gl/glut.h>

void mydisplay() { //繪圖,不接受任何引數
	glClear(GL_COLOR_BUFFER_BIT); //預設白色，背景
	glBegin(GL_POLYGON);  //透過以下的點畫圖
	glVertex2f(-0.5, -0.5); //2維，以浮點數繪製
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush(); //frame buffer更新
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutCreateWindow("S10859045"); //視窗名
	glutDisplayFunc(mydisplay); 
	glutMainLoop();  //類似system pause
}