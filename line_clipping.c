/*
SE-10
G-10
23257
PROBLEM STATEMENT:-  
	Draw the following pattern using any Line drawing algorithms.	
*/


#include<stdio.h>
#include<GL/glut.h>
//#include<math.h>
#include<iostream>
using namespace std;
struct c
{
	int a;
	int b;
	int l;
	int r;
};	
int n,f1=0;
float x1,y1,x2,y2;
float xl,yl,xh,yh;
void Init();
void display();
void cohen_line();
void myKey(unsigned char key,int x,int y);
int abs(int m)		//absolute function
{
	if(m<=0)
		return (m*(-1));
	else
		return m;
}


void DDA(float x0,float y0,float x1,float y1)
{
	float dx=x1-x0;
	float dy=y1-y0;
	
	int steps=(abs(dx) > abs(dy)) ? (abs(dx)) : (abs(dy));	//calculate steps required for generating pixels
	
	float xinc=dx/(float)steps;	//calculate increment in x& y for each steps
	float yinc=dy/(float)steps;
	
	float x=x0;
	float y=y0;
	glBegin(GL_POINTS);
	for(int i=0;i<=steps;i++)
	{
		glVertex2f(abs(x),abs(y)); // put pixel at (X,Y
		x += xinc;           // increment in x at each step 
		y += yinc;           // increment in y at each step 
	}
	
	glEnd();
glFlush();
}

void display()
{

	cout<<"clldsf";
	DDA(xl,yl,xh,yl);
	DDA(xh,yl,xh,yh);
	DDA(xh,yh,xl,yh);
	DDA(xl,yh,xl,yl);
	if(f1==0)
	{
		glColor3f(1,1,0);
		DDA(x1,y1,x2,y2);
	}	
	//glFlush();
	//glEnd();
}
struct c code(int x,int y)
{

	struct c p={0,0,0,0};
	if(y>yh)
	{p.a=1;}
	if(y<yl)
		{p.b=1;}
	if(x>xh)
		{p.r=1;}
	if(x<xl)
		{p.l=1;}
		//printf("\n%d%d%d%d",p.a,p.b,p.r,p.l);
		
	return p;	
}	
void cohen_line()
{
	float xi,yi;
	int flag;
	float m=(y1-y2)/(x1-x2);
	struct c c1;
	c1=code(x1,y1);
	struct c c2;
	c2=code(x2,y2);
	//printf("%d%d%d%d%d%d%d%d",c1.a,c1.b,c1.r,c1.l,c2.a,c2.b,c2.r,c2.l);
	while(1)
	{	
		if(c1.a==0 && c1.b==0 && c1.l==0 && c1.r==0 && c2.a==0 && c2.b==0 && c2.l==0 && c2.r==0)
		{
			break;
		}	
		else
		{
				if(((c1.a && c2.a) || (c1.b && c2.b) || (c1.r && c2.r) || (c1.l && c2.l)) !=0)
				{
					f1=1;
					break;	
				}
				else
				{
					if(c1.l ==1 || c2.l==1)
					{
						xi=xl;
						yi=y1+m*(xl-x1);
						if(c1.l==1)
						flag=0;
						else
						flag=1;
					}
					else if(c1.r==1 || c2.r==1)
					{
						xi=xh;
						yi=y1+m*(xh-x1);
						if(c1.r==1)
						flag=0;
						else
						flag=1;
					}		
					else if(c1.b==1 || c2.b==1)
					{
						yi=yl;
						xi=x1+(1/m)*(yl-y1);
						if(c1.b==1)
						flag=0;
						else
						flag=1;
					}			
					else if(c1.a==1 || c2.a==1)
					{
						yi=yh;
						xi=x1+(1/m)*(yh-y1);
						if(c1.a==1)
						flag=0;
						else
						flag=1;
					}
					struct c ci=code(xi,yi);
					if(flag==0)
						{
						x1=xi;y1=yi;
						c1=ci;	
						}
					else
						{
						x2=xi;y2=yi;
						c2=ci;
						}
					printf("\n%f%f",x1,y1);		
					printf("\n%d%d%d%d",ci.a,ci.b,ci.r,ci.l);	
						
				}		
			
		}
	}
	display();								
}		
void myKey(unsigned char key,int x,int y)
{
	if(key=='p')
	{
		printf("Hello");
		Init();
		cohen_line();	
	}
}				
void Init()
{
	cout<<"\nentered";
 	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);
}
int main(int argc,char **argv)
{
	printf("\nENTER THE LOWER WINDOW CO-ORDINATES::");
	scanf("%f%f",&xl,&yl);
	printf("\nENTER THE HIGHER WINDOW CO-ORDINATES::");
	scanf("%f%f",&xh,&yh);
	printf("\nENTER THE X AND Y CO-ODINATES OF THE LINE::");
	scanf("%f%f%f%f",&x1,&y1,&x2,&y2);
	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowPosition(0,0); // Set the initial window position and size
  	glutInitWindowSize(640,480);
  	
  	glutCreateWindow("ASSIGN-6"); // Create window with title DDA_Line
  	gluOrtho2D(0 , 640 , 0 , 480);
  	Init();		 // Initialize drawing colors
  	glutDisplayFunc(display);
  	glutKeyboardFunc(myKey);
  	  
  	glutMainLoop();
	return 0;
}


