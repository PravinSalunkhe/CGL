#include<GL/gl.h>
#include <GL/glut.h>
#include <math.h>

#include <iostream>
using namespace std;

struct Point 
{
	GLint x;
	GLint y;
};

Point p1, p2;

void draw_dda(Point p1, Point p2) 
{
	float dx=p2.x-p1.x;
	float dy=p2.y-p1.y;
	
	int steps=(abs(dx) > abs(dy)) ? (abs(dx)) : (abs(dy));	//calculate steps required for generating pixels
	
	float xinc=dx/(float)steps;	//calculate increment in x& y for each steps
	float yinc=dy/(float)steps;
	
	float x=p1.x;
	float y=p1.y;
	
	for(int i=0;i<=steps;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(abs(x),abs(y)); // put pixel at (X,Y) 
		x += xinc;           // increment in x at each step 
		y += yinc;           // increment in y at each step 
	}
	glFlush();
	
}

// My Mouse function

void myMouseFunc(int button, int state, int x, int y)
{
	glColor3f(1.0f, 1.0f, 0.0f);
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
	{
		p1.x = x;
		p1.y = 480 - y;
	}
	else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    	{
		p2.x = x;
		p2.y = 480 - y;
	}
	draw_dda(p1, p2);
	
	   fflush(stdout);
}

void init() 
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(1.0f);
	gluOrtho2D(0.0f, 640.0f, 0.0f, 480.0f);
}


int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
    
    //Defines 640 X 480 Window size
	glutInitWindowSize(640, 480);

	glutCreateWindow("Mouse Func");
    //Calls myMouseFunction
	glutMouseFunc(myMouseFunc);

	init();
	glutMainLoop();

	return 0;
}
