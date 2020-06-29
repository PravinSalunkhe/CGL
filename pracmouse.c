#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
using namespace std;

typedef struct pixel
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}pixel;
pixel black,red,green,blue,yellow,p;
int i,j=0,k=1,flag=0;
int m[10],n[10];
void display();
void Init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
}		
void DDA(int x1,int y1,int x2,int y2)
{
	float dx=x2-x1;
	float dy=y2-y1;
	
	int steps;
	if(abs(dx) > abs(dy))
		steps=abs(dx);
	else
		steps=abs(dy);
		
	float xi=dx/(float)steps;
	float yi=dy/(float)steps;
	
	float x=x1;float y=y1;
		
	for(i=0;i<=steps;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(abs(x),abs(y));
		glEnd();
		glFlush();
		x+=xi;
		y+=yi;
	}	
}
	
void display1(int x1,int y1,int x2,int y2)
{
	printf("\n%d\t%d\t%d\t%d",x1,y1,x2,y2);
	DDA(x1,y1,x2,y2);	
}
void boundary_fill(int x,int y,struct pixel nc,struct pixel bc)	
{
	pixel c;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
	if((c.r!=nc.r || c.g!=nc.g || c.b!=nc.b) && (c.r!=bc.r || c.g!=bc.g || c.b!=bc.b))
	{
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glColor3ub(nc.r,nc.g,nc.b);
		glEnd();
		glFlush();
		boundary_fill(x+1,y,nc,bc);
		boundary_fill(x-1,y,nc,bc);
		boundary_fill(x,y-1,nc,bc);
		boundary_fill(x,y+1,nc,bc);
	}	
}	
void display()
{
	DDA(50,50,250,50);
	DDA(50,100,250,100);
	DDA(50,50,50,100);
	DDA(100,50,100,100);
	DDA(150,50,150,100);
	DDA(200,50,200,100);
	DDA(250,50,250,100);
	
	boundary_fill(75,75,red,black);
	boundary_fill(125,75,blue,black);
	boundary_fill(175,75,green,black);
	boundary_fill(225,75,yellow,black);
}
void myMouseFunc(int button,int state,int x,int y)
{
	int a,b;
	switch(button)
	{
	case GLUT_LEFT_BUTTON:
				if(state==GLUT_DOWN)
				{
					a=x;b=480-y;
					if(flag==0)
					{
						
						glReadPixels(a,b,1,1,GL_RGB,GL_UNSIGNED_BYTE,&p);
						if(p.r==red.r && p.g==red.g && p.b==red.b)
						{	flag=1;glColor3f(red.r,red.g,red.b);}
						else if(p.r==blue.r && p.g==blue.g && p.b==blue.b)
						{	flag=1;glColor3f(blue.r,blue.g,blue.b);}	
					 	else if(p.r==green.r && p.g==green.g && p.b==green.b)
						{	flag=1;glColor3f(green.r,green.g,green.b);}
						else if(p.r==yellow.r && p.g==yellow.g && p.b==yellow.b)
						{	flag=1;glColor3f(yellow.r,yellow.g,yellow.b);}	
					}
					else if(flag==1)
					{
						m[j]=a;n[j]=b;
						printf(" %d %d ",m[j],n[j]);
						if(k!=1)
						{
							
							display1(m[j-1],n[j-1],m[j],n[j]);
							k++;
							j++;
						}
						else
						{
							k++;
							j++;
						}		
					}
					else
						return;
								
				}
				else if(state==GLUT_UP)
				{	printf("UP");
					return;}
					
					break;
	case GLUT_RIGHT_BUTTON :	
				if(state==GLUT_DOWN)
				{
					printf("right");
					if(flag==1)
					{
					display1(m[j-1],n[j-1],m[0],n[0]);
					flag=2;
					}
				}
				else						
					return;
				
				break;
	default:
		break;			
					
	}
}		
int main(int argc,char **argv)
{	
	black.r=0;
	black.g=0;
	black.b=0;
	
	red.r=255;
	red.g=0;
	red.b=0;
	
	blue.r=0;
	blue.g=0;
	blue.b=255;
	
	green.r=0;
	green.g=255;
	green.b=0;
	
	yellow.r=255;
	yellow.g=255;
	yellow.b=0;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("mouse practice");
	gluOrtho2D(0,640,0,480);
	Init();
	glutDisplayFunc(display);
	glutMouseFunc(myMouseFunc);
	glutMainLoop();
	return 0;	
}
	
	
	
			
