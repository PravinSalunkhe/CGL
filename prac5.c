#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;
float xl,yl,xh,yh,xa,xb,ya,yb,f1=0,flag;
typedef struct c
{
	int a;int b;int r;int l;
}c;	
struct c code(float x,float y)
{
	c p={0,0,0,0};
	if(y>yh)
		p.a=1;
	if(y<yl)
		p.b=1;
	if(x<xl)
		p.l=1;
	if(x>xh)
		p.r=1;
	return p;	
}					 

void Init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
}	
void DDA(float x1,float y1,float x2,float y2)
{
	float dx,dy,xk,yk,xinc,yinc;
	dx=x2-x1;
	dy=y2-y1;
	int steps= ( (abs(dx)) > (abs(dy)) ? (abs(dx)) : (abs(dy)));
	xinc=dx/(float)steps;
	yinc=dy/(float)steps;
	
	xk=x1;yk=y1;
	for(int i=0;i<=steps;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(abs(xk),abs(yk));
		glEnd();
		xk=xk+xinc;
		yk=yk+yinc;
	}
	glFlush();
}
void display()
{
	
	DDA(xl,yl,xh,yl);
	DDA(xh,yl,xh,yh);
	DDA(xh,yh,xl,yh);
	DDA(xl,yh,xl,yl);
	
	if(f1==0)
	{
		glColor3f(1.0,1.0,0.0);	
		DDA(xa,ya,xb,yb);
	}		
}
void cohen()
{
	float xi,yi;
	float m=(yb-ya)/(xb-xa);
	c c1=code(xa,ya);
	c c2=code(xb,yb);
	
	while(1)
	{
		if(c1.a ==0 && c1.b ==0 && c1.r==0 && c1.l==0 && c2.a==0 && c2.b==0 && c2.r==0 && c2.l==0)
		{
			printf("\ncase 1");
			return;
		}
		else if(((c1.a && c2.a) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l))!=0)
		{
			f1=1;		
			cout<<"\nCASE 2";
			return;
		}
		else
		{
			if((c1.l || c2.l) !=0)
			{
				cout<<"\nCASE 3l";
				xi=xl;
				yi=ya+m*(xl-xa);
				if(c1.l==1)
					flag=0;
				else
					flag=1;
			}
			else if((c1.r || c2.r) !=0)
			{
				cout<<"\nCASE 3r";
				xi=xh;
				yi=ya+m*(xh-xa);
				if(c1.r==1)
					flag=0;
				else
					flag=1;
			}
			else if((c1.b || c2.b) !=0)
			{
				cout<<"\nCASE 3b";
				yi=yl;
				xi=xa+(1/m)*(yl-ya);
				if(c1.b==1)
					flag=0;
				else
					flag=1;
			}
			else
			{
				cout<<"\nCASE 3a";
				yi=yh;
				xi=xa+(1/m)*(yh-ya);
				if(c1.a==1)
					flag=0;
				else
					flag=1;
			}
			c ci=code(xi,yi);
			if(flag==0)
			{
				cout<<"\nNEW IN1";
				xa=xi;ya=yi;
				c1=ci;
			}
			else
			{
				cout<<"\nNEW IN2";
				xb=xi;yb=yi;
				c2=ci;
			}		
											
		}		
	}	
}		
void mykey(unsigned char key,int x,int y)
{
	if(key =='c')
	{
		cout<<"\nHELLO";
		Init();
		cohen();
		display();
	}	
}
	
int main(int argc,char **argv)
{
	cout<<"\nENTER THE LOWER CORDINATES OF WINDOW::";
	cin>>xl>>yl;
	cout<<"\nENTER THE HIGHER CORDINATES OF WINDOW::";
	cin>>xh>>yh;
	cout<<"\nENTER THE STARTING POINT OF LINE::";
	cin>>xa>>ya;
	cout<<"\nENTER THE END POINT OF LINE::";
	cin>>xb>>yb;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Line Clipping");
	gluOrtho2D(0,640,0,480);
	Init();
	glutDisplayFunc(display);
	glutKeyboardFunc(mykey);
	glutMainLoop();
	
}	
