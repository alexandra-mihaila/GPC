#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "glut.h"


// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		//x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		//y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		//x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		//y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}

// graficul functiei 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
	double pi = 4 * atan(1);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}
double d(double x)
{
	return fabs(x - round(x));
}

void Display3() {

	// f(x) = 1, x=0 
	// f(x) = d(x)/x , 0< x <=100
	double xmax = 100 * 0.25;
	double ymax = 1.1;
	double ratia = 0.5;
	double x1, y1;


	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	glVertex2f(-0.01, 1/ymax);
	for (double x = 0 + ratia; x <= 100; x += ratia) {
		x1 = x / xmax;
		y1 = (d(x) / x) / ymax;
		// ca sa nu iasa din cadru
		if (x+1 == xmax) {
			break;
		}
		glVertex2f(x1, y1);
	}
	glEnd();

}

void Display4()
{

	//x = 2*(a*cos(t) + b) * cos(t) 
	//y = 2 * (a*cos(t)+b) * sin(t)
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double a = 0.3;
	double b = 0.2;
	double x1, y1;
	double xmax = (2 * (a * cos(0) + b) * cos(0));
	for (double t = -pi + ratia; t < pi; t += ratia)
	{
		x1 = (2 * (a * cos(t) + b) * cos(t));

		if (x1 > xmax)
		{
			xmax = x1;
		}
	}
	xmax = xmax+0.1;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_LOOP);
	for (double t = -pi + ratia; t < pi; t += ratia)
	{
		x1 = (2 * (a * cos(t) + b) * cos(t))/xmax;
		y1 = (2 * (a * cos(t) + b) * sin(t));

		glVertex2f(x1, y1);
	}
	glEnd();
}

void Display5() {
	double pi = 4 * atan(1.0);
	double ratia = 0.005;
	double t;
	double x, y;
	double xmin = -0.95;
	double ymax = 0.99;
	double a = 0.2;
	
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_TRIANGLES);
	int count = 0;
	glVertex2f(xmin, ymax);
	for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
		
		x = a / (4 * cos(t) * cos(t) - 3);
		y = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);
		// trebuie sa ma incadrez in limitele intiale
		if (x >= xmin && y <= ymax) {
			// pentru partea goala din mijloc
			if (y < 0.25)
				continue;
			// pentru a desena triunghiurile cu spatii intre ele
			if (count % 3 == 1) {

				glVertex2f(x, y);

				x = a / (4 * cos(t + ratia) * cos(t + ratia) - 3);
				y = (a * tan(t + ratia)) / (4 * cos(t + ratia) * cos(t + ratia) - 3);

				glVertex2f(x, y);

				glVertex2f(xmin, ymax);
			}
			
		}
		count += 1;
	}

	glEnd();
	ratia = 0.0001;
	glColor3f(0.2, 0.15, 0.88);
	glBegin(GL_LINE_LOOP);

	glVertex2f(xmin, ymax);
	// conturul 
	for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
		
		x = a / (4 * cos(t) * cos(t) - 3);
		y = (a * tan(t)) / (4 * cos(t) * cos(t) - 3);

		if (x >= xmin && y <= ymax) {
			glVertex2f(x, y);
		}
		
	}
	glEnd();


}

void Display6()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	
	double start = -3 * pi;
	double end = 3 * pi;

	double a = 0.1;
	double b = 0.2;

	double x1, y1;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = start; t <= end; t += ratia)
	{
		x1 = (a * t - b * sin(t));
		y1 = (a - b * cos(t));

		glVertex2f(x1, y1);

	}
	glEnd();
}

void Display7() {

	double pi = 4 * atan(1.0);
	double ratia = 0.05;

	double start = 0;
	double end = 2 * pi;

	double R = 0.1;
	double r = 0.3;

	double xmax = (R + r) * cos(r * start / R) - r * cos(start + r * start / R);
	double ymax = (R + r) * sin(r * start / R) - r * sin(start + r * start / R);

	double x1, y1;

	for (double t = start; t <= end; t += ratia)
	{
		x1 = (R + r) * cos(r * t / R) - r * cos(t + r * t / R);
		y1 = (R + r) * sin(r * t / R) - r * sin(t + r * t / R);

		if (x1 > xmax)
		{
			xmax = x1;
		}

		if (y1 > ymax)
		{
			ymax = y1;
		}
	}

	xmax = xmax + xmax / 2;
	ymax = ymax + ymax / 2;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = start; t <= end; t += ratia)
	{
		x1 = ((R + r) * cos(r * t / R) - r * cos(t + r * t / R)) / xmax;
		y1 = ((R + r) * sin(r * t / R) - r * sin(t + r * t / R)) / ymax;

		glVertex2f(x1, y1);

	}
	glEnd();

}
void Display8() {
	double pi = 4 * atan(1.0);
	double ratia = 0.05;

	double start = 0;
	double end = 2 * pi;

	double R = 0.1;
	double r = 0.3;

	double xmax = (R - r) * cos(r * start / R) - r * cos(start - r * start / R);
	double ymax = (R - r) * sin(r * start / R) - r * sin(start - r * start / R);

	double x1, y1;

	for (double t = start; t <= end; t += ratia)
	{
		x1 = (R - r) * cos(r * t / R) - r * cos(t - r * t / R);
		y1 = (R - r) * sin(r * t / R) - r * sin(t - r * t / R);

		if (x1 > xmax)
		{
			xmax = x1;
		}

		if (y1 > ymax)
		{
			ymax = y1;
		}
	}

	xmax = 2 * xmax;
	ymax = 2 * ymax;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = start; t <= end; t += ratia)
	{
		x1 = ((R - r) * cos(r * t / R) - r * cos(t - r * t / R)) / xmax;
		y1 = ((R - r) * sin(r * t / R) - r * sin(t - r * t / R)) / ymax;

		glVertex2f(x1, y1);

	}
	glEnd();
}

void Display9()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.0025;

	double start = -pi / 4;
	double end = pi / 4;

	double a = 0.4;

	double x1, y1, x2, y2;
	// se folosesc coordonate polare
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = start + ratia; t < end; t += ratia)
	{
		// x = r * cos(t) , y = r * sin(t)
		x1 = a * sqrt(2 * cos(2 * t)) * cos(t);
		y1 = a * sqrt(2 * cos(2 * t)) * sin(t);

		glVertex2f(x1, y1);
	}

	for (double t = end - ratia; t > start; t -= ratia)
	{
		x2 = -a * sqrt(2 * cos(2 * t)) * cos(t);
		y2 = -a * sqrt(2 * cos(2 * t)) * sin(t);

		glVertex2f(x2, y2);
	}
	glEnd();
}

void Display0()
{
	double pi = 4 * atan(1.0);
	double ratia = 0.05;

	double start = 0;
	double end = 2.9;

	double a = 0.02;

	double x1, y1;

	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (double t = start + ratia; t < end; t += ratia)
	{
		x1 = a * exp(1 + t) * cos(t);
		y1 = a * exp(1 + t) * sin(t);

		glVertex2f(x1, y1);
	}
	glEnd();
}


void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		Display3();
		break;
	case '4':
		Display4();
		break;
	case '5':
		Display5();
		break;
	case '6':
		Display6();
		break;
	case '7':
		Display7();
		break;
	case '8':
		Display8();
		break;
	case '9':
		Display9();
		break;
	case '0':
		Display0();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}