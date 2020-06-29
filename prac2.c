#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
float a,b,radius;
void Init()
{
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
}
int sign(float arg)
{
	if(arg>0)
		return 1;
	else if(arg==0)
		return 0;
	else
		return -1;
}
void BLD(int x1,int y1,int x2,int y2)
{
	float dx,dy,temp;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	int s1=sign(x2-x1);
	int s2=sign(y2-y1);
	int xk=x1,yk=y1,pk,i=0,exchange=0;
	if(dy>dx)
	{
		temp=dx;
		dx=dy;
		dy=temp;
		exchange=1;
	}
	glBegin(GL_POINTS);
		glVertex2f(xk,yk);
	glEnd();
	pk=2*dy-dx;
	while(i<=dx)
	{
		
		if(pk>=0)
		{
			pk=pk+2*(dy-dx);
			if(exchange==0)
			yk=yk+s2;
			else
			xk=xk+s1;
		}
		else
		{
			pk=pk+2*dy;
			if(exchange==0)
			yk=yk;
			else
			xk=xk;
		}		
		if(exchange==0)
		xk=xk+s1;
		else
		yk=yk+s2;
		glBegin(GL_POINTS);
		glVertex2f(xk,yk);
		glEnd();
		i++;
	}
	glFlush();
}					
void mid(float cx,float cy,float r)
{
	float xk,yk,pk;
	glBegin(GL_POINTS);
		glVertex2f(cx,cy+r);
	glEnd();
	xk=0;yk=r;
	pk=1-r;
	while(xk<yk)
	{
		if(pk<0)
		{
			pk=pk+2*xk+1;
			xk=xk+1;
			yk=yk;
		}
		else
		{
			pk=pk+2*(xk-yk)+1;
			xk=xk+1;
			yk=yk-1;
		}		
			glBegin(GL_POINTS);
			glVertex2f(cx+xk,cy+yk);
			glVertex2f(cx-xk,cy+yk);
			glVertex2f(cx+xk,cy-yk);
			glVertex2f(cx-xk,cy-yk);
			glVertex2f(cx+yk,cy+xk);
			glVertex2f(cx-yk,cy+xk);
			glVertex2f(cx+yk,cy-xk);
			glVertex2f(cx-yk,cy-xk);
			glEnd();
							
	}
glFlush();	
}		
void display()
{
	mid(a,b,radius);
	mid(a,b,2*radius);
	BLD(a-sqrt(3)*radius,b-radius,a+sqrt(3)*radius,b-radius);
	BLD(a+sqrt(3)*radius,b-radius,a,b+2*radius);
	BLD(a,b+2*radius,a-sqrt(3)*radius,b-radius);	
}			
int main(int argc , char **argv)
{
	printf("\nENTER THE CENTER OF THE CIRCLE:-\nX co-ordinate:- ");	//getting center of circle
	scanf("%f",&a);
	printf("\nY co-ordinate:- ");
	scanf("%f",&b);
	printf("\nENTER THE RADIUS OF THE CIRCLE:-");	//getting radius of circle
	scanf("%f",&radius);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(1000,800);
	glutCreateWindow("Practice");
	gluOrtho2D(0,1000,0,800);
	Init();
	glutDisplayFunc(display);
	glutMainLoop();
	
}


	
