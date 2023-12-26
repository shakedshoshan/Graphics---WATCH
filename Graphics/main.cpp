#define _CRT_SECURE_NO_WARNINGS

#include "GLUT.h"
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <stdio.h>

const int GSIZE = 200;
const double PI = 3.14;

const int H = 600;
const int W = 600;

double ground[GSIZE][GSIZE] = { 0 };

double eyex = 0, eyey = 20, eyez = 20;
double dx = 0, dz = 0, dy = 0;
double alpha = PI / 2;
double offset = 0;

// ego-motion
double speed = 0;
double sight_angle = PI, angular_speed = 0;
double dirx = sin(sight_angle), dirz = cos(sight_angle), diry = 0;
double pitch = 0, oldY = 0;

BOOL slider_is_moving = false;



// dark blue
float mamb2[4] = { 0.0,0.0,0.3 };
float mdiff2[4] = { 0.2,0.1,0.5 };
float mspec2[4] = { 0.9,0.9,0.9 };


float lamb[4] = { 0.3,0.3,0.3 };
float ldiff[4] = { 0.6,0.7,0.7 };
float lspec[4] = { 0.7,0.7,0.7 };
float lpos[4] = { 4,7,1,0 };

float lamb1[4] = { 0.4,0.4,0.4 };
float ldiff1[4] = { 0.7,0.7,0.3 };
float lspec1[4] = { 0.6,0.6,0.6 };
float lpos1[4] = { -5,-1,3,0 };



void init()
{
	glClearColor(0.8, 0.8, 1, 0); // set background color
	glEnable(GL_DEPTH_TEST); // test of near/far surface

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lamb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, ldiff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lspec);
	glLightfv(GL_LIGHT0, GL_POSITION, lpos);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lamb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ldiff1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lspec1);
	glLightfv(GL_LIGHT1, GL_POSITION, lpos1);
}

void DrawCylinderStrip(int num_pts, double r, double g, double b) 
{
	double alpha, teta = 2 * PI / num_pts;


	// silver
	float mamb1[4] = { 0.3,0.3,0.3 };
	float mdiff1[4] = { 0.8,0.8,0.8 };
	float mspec1[4] = { 0.7,0.7,0.7 };


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mamb1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiff1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspec1);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	for (alpha = 0; alpha < 2 * PI/1.1; alpha += teta)
	{
		glBegin(GL_POLYGON);
		//glColor3d(r,g,b);
		glNormal3d(sin(alpha), 0, cos(alpha));
		glVertex3d(sin(alpha), 1, cos(alpha)); // 1
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta)); // 2
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta)); // 3
		glVertex3d(sin(alpha), 0, cos(alpha)); // 4
		glEnd();
	}
}

void DrawCylinder(int num_pts, double r, double g, double b)
{
	double alpha, teta = 2 * PI / num_pts;

	// gold
	float mamb3[4] = { 0.5,0.4,0.0 };
	float mdiff3[4] = { 0.8,0.6,0.4 };
	float mspec3[4] = { 0.7,0.6,0.1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mamb3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiff3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspec3);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		glBegin(GL_POLYGON);
		//glColor3d(fabs(sin(alpha)), 1 - fabs(sin(2 * alpha)), fabs(cos(alpha)));
		glNormal3d(sin(alpha), 0, cos(alpha));
		glVertex3d(sin(alpha), 1, cos(alpha)); // 1
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta)); // 2
		//glColor3d(0.5 * fabs(sin(alpha)), 1 - fabs(sin(2 * alpha)), fabs(0.5 * cos(alpha)));
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta)); // 3
		glVertex3d(sin(alpha), 0, cos(alpha)); // 4
		glEnd();
	}
}

void DrawCircle(int num_pts, double r, double g, double b)
{
	double alpha, teta = 2 * PI / num_pts;

	// gold
	float mamb3[4] = { 0.5,0.4,0.0 };
	float mdiff3[4] = { 0.8,0.6,0.4 };
	float mspec3[4] = { 0.7,0.6,0.1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mamb3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiff3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspec3);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	glBegin(GL_POLYGON);
	glColor3d(r, g, b);
	for (alpha = 0; alpha < PI * 2; alpha += teta)
	{
		glNormal3d(0, 1, 0);
		glVertex3d(sin(alpha), cos(alpha), 0.0); // 1

	}
	glEnd();
}


void DrawCenterCircle(int num_pts, double r, double g, double b)
{
	double alpha, teta = 2 * PI / num_pts;

	// dark blue
	float mamb2[4] = { 0.0,0.0,0.3 };
	float mdiff2[4] = { 0.2,0.1,0.5 };
	float mspec2[4] = { 0.9,0.9,0.9 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mamb2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mdiff2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mspec2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

	glBegin(GL_POLYGON);
	//glColor3d(r, g, b);
	for (alpha = 0; alpha < PI * 2; alpha += teta)
	{
		glNormal3d(0, 1, 0);
		glVertex3d(sin(alpha), cos(alpha), 0.0); // 1
	}
	glEnd();

	

}

void DrawTriangle() {
	glColor3d(0, 0, 0);
	glLineWidth(2);
	glBegin(GL_POLYGON);
	glVertex3d(-1,0,0);
	glVertex3d(0, 1, 0);
	glVertex3d(1, 0, 0);
	glEnd();
}

void DrawWatchHead() {


	double alpha, teta = 2 * PI / 360;
	int c = 0;
	// hours lines
	glPushMatrix();
	glTranslated(-1, 16.6, 7.3);
	glScaled(1.8,1.8,1.8);
	glRotated(115, 1, 0, 0);
	glColor3d(0, 0, 0);
	glLineWidth(3);
	for (alpha = 0; alpha < PI * 2; alpha += teta)
	{
		glBegin(GL_LINE_STRIP);
		//glRotated(90, 0, 0, 1);
		if (c % 30 == 0) {
			glVertex3d(sin(alpha)*0.85, cos(alpha)*0.85, 0.0);
			glVertex3d(sin(alpha)*0.7, cos(alpha)*0.7, 0.0);
		}
		glEnd();
		c += 1;

	}
	glPopMatrix();



	// hand of hour
	glPushMatrix();
	glTranslated(-1, 16.508, 7.311);
	glRotated(115, 1, 0, 0);
	glRotated(180 + pitch * 30 , 0, 0, 1);
	glScaled(0.05,1.15,0.05);
	DrawTriangle();
	glPopMatrix();

	// hand of minuts
	glPushMatrix();
	glTranslated(-1, 16.508, 7.311);
	glRotated(115, 1, 0, 0);
	glRotated(180 + pitch * 360, 0, 0, 1);
	glScaled(0.05, 0.86, 0.05);
	DrawTriangle();
	glPopMatrix();

	
	
	// blue body
	glPushMatrix();
	glTranslated(-1, 16.505, 7.311);
	glRotated(115, 1, 0, 0);
	glRotated(180 , 0, 0, 1);
	glScaled(1.8, 1.8, 1.8);
	DrawCenterCircle(60, 0, 0, 0.9);
	glPopMatrix();

	
}

void DrawWatch() {

	//strip

	glPushMatrix();
	glTranslated(0, 13, 5);
	glRotated(90, 0, 0, 1);
	glRotated(75, 0, 1, 0);
	glScaled(4, 2, 4);
	DrawCylinderStrip(60, 0.0, 0.0, 0.0);
	glPopMatrix();

	
	//head
	glPushMatrix();
	glTranslated(-1, 16.2, 7.2);
	glRotated(25, 1, 0, 0);
	glScaled(2, 0.4, 2);
	DrawCylinder(60, 1,1,0);
	glPopMatrix();


	glPushMatrix();
	glTranslated(-1, 16.5, 7.311);
	glRotated(115, 1, 0, 0);
	glScaled(2, 2, 2);
	DrawCircle(60,0, 0, 0.9);
	glPopMatrix();

	DrawWatchHead();







}

void DrawSlider()
{
	glColor3d(1, 1, 0);
	// background
	glBegin(GL_POLYGON);
	glVertex2d(0, 0);
	glVertex2d(0, 100);
	glVertex2d(100, 100);
	glVertex2d(100, 0);
	glEnd();

	glLineWidth(2);
	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(0, 50);
	glVertex2d(100, 50);
	glEnd();


	glMatrixMode(GL_MODELVIEW); // matrix of world
	glLoadIdentity(); // start transformations here

	glPushMatrix();
	glTranslated(-pitch * 180 / (PI*6), 0, 0); // move in dgrees
	// slider button

	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2d(48, 40);
	glVertex2d(48, 60);
	glVertex2d(52, 60);
	glVertex2d(52, 40);
	glEnd();

	glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, W, H); // left+bottom and width+hight
	glMatrixMode(GL_PROJECTION); // glFrustum sets for 3D
	glLoadIdentity();
	// camera model
	glFrustum(-1, 1, -1, 1, 0.7, 300);
	// eyex, eyey, eyez, centerx, centery, centerz, topx, topy, topz
	gluLookAt(eyex, eyey, eyez,
		eyex + dirx, eyey - 0.5, eyez + dirz, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
	DrawWatch();
	glPopMatrix();



	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	// controls sub-window
	glViewport(0, 0, 600, 100);
	// Now we switch to Orthogonal projection, so we must change the projections matrix
	glMatrixMode(GL_PROJECTION); // vision matrix
	glLoadIdentity(); // start transformations here
	glOrtho(0, 100, 0, 100, -1, 1);
	glDisable(GL_DEPTH_TEST); // return to principles of graphics 2D

	DrawSlider();


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glutSwapBuffers();
}


void idle()
{
	sight_angle += angular_speed;
	dirx = sin(sight_angle);
	dirz = cos(sight_angle);

	eyex += (speed * dirx);
	eyez += (speed * dirz);
	eyey += dy;
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		angular_speed += 0.0002;
		break;
	case GLUT_KEY_RIGHT:
		angular_speed -= 0.0002;
		break;
	case GLUT_KEY_UP:
		speed += 0.001;
		break;
	case GLUT_KEY_DOWN:
		speed -= 0.001;
		break;
	case GLUT_KEY_PAGE_UP:
		dy += 0.01;
		break;
	case GLUT_KEY_PAGE_DOWN:
		dy -= 0.01;
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	double angle_in_degrees = pitch * 180 / PI;
	printf("%d ,  %d ,   %1f\n", x, y, angle_in_degrees);
	bool clickInSlider = x + angle_in_degrees > 290 && x + angle_in_degrees < 310  && y > 540 && y <  560;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && clickInSlider) // drag slider
	{
		slider_is_moving = true;
		oldY = W - x;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		slider_is_moving = false;
}

void mouseDrag(int x, int y)
{
	double dy = (W - x) - oldY;

	if (slider_is_moving && W - x < 600 && W - x>0)
	{
		pitch += dy * PI / 180; // transform dy to radian
		oldY = (W - x);

	}
}
void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Exam");

	glutDisplayFunc(display); // display is the refresh function
	glutIdleFunc(idle);
	glutSpecialFunc(special); // for "home", "insert" arrows keys ...
	glutMouseFunc(mouse);
	glutMotionFunc(mouseDrag);

	init();

	glutMainLoop();
}
