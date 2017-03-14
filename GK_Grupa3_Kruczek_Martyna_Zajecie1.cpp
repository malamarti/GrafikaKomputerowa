#include "stdafx.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cmath>

// Pocz¹tkowy rozmiar i pozycja prostokta
GLfloat x_1 = 25.0f;
GLfloat y_1 = 25.0f;
GLfloat angle = 0.0f;
GLsizei rsize = 25.0f;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Dane zmieniajcych siê rozmiarów okna
GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.22f, 0.06f, 0.02f);
	int triangleAmount = 10;
	GLfloat twicePi = 2.0f * 3.14f;
	angle += 0.8f;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(x_1, y_1, 0);
	glRotatef(-angle, 0, 0, 1);
	glTranslatef(-x_1, -y_1, 0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x_1, y_1); // center of circle
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x_1 + ((6.0*cos(i*twicePi / triangleAmount)) * 4.0f),
			y_1 + ((6.0*sin(i*twicePi / triangleAmount)) * 4.0f)
		);
	}
	glEnd();
	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

GLfloat xsteptemp = 0;
GLfloat ysteptemp = 0;

void TimerFunction(int value) {
	// Odwrócenie kierunku, je¿eli osi¹gniêto lew¹ lub praw¹ krawêdŸ
	//if (x_1 > windowWidth - rsize || x_1 < 20)
	//	xstep = -xstep;

	//// Odwrócenie kierunku, je¿eli osi¹gniêto doln¹ lub górn¹ krawêdŸ
	//if (y_1 > windowHeight - rsize || y_1 < 20)
	//	ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy³o swoj wielkoœæ w czasie, gdy kwadrat odbija³ siê od     
	// krawêdzi, co mog³oby spowodowaæ, ¿e znalaz³ by siê poza      
	// przestrzeni¹ ograniczajc¹.  

	x_1 += xsteptemp;
	y_1 += ysteptemp;

	if (x_1 == windowWidth - rsize && y_1 == rsize) {
		xsteptemp = 0.f;
		ysteptemp = ystep;
	}

	if (x_1 == windowWidth - rsize && y_1 == windowHeight - rsize) {
		xsteptemp = -1.f;
		ysteptemp = 0.f;
	}

	if (x_1 == rsize && y_1 == windowHeight - rsize) {
		xsteptemp = 0.f;
		ysteptemp = -1.f;
	}

	if (x_1 == rsize && y_1 == rsize) {
		xsteptemp = xstep;
		ysteptemp = 0.f;
	}

	// Wykonanie przesuniêcia kwadratu
	//x_1 += xstep;
	//y_1 += ystep;

	if (x_1 > windowWidth - rsize)
		x_1 = windowWidth - rsize - 1;

	if (y_1 > windowHeight - rsize)
		y_1 = windowHeight - rsize - 1;

	if (x_1 < rsize) {
		x_1 = rsize;
		xsteptemp = 0;
		ysteptemp = -1.0f;
	}

	if (y_1 < rsize)
		y_1 = rsize;
	// Ponowne rysowanie sceny z nowymi wspó³rzêdnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielkoœci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk³adu wspó³rzêdnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void SetupRC(void) {
	glClearColor(0.6f, 0.4f, 0.12f, 1.0f);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Mój pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}