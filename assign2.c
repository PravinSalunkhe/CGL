#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
void Init();
void display();
void display1();
void circle(int a,int b,int radius);
void BDL(int x1,int y1,int x2,int y2);
int cx,cy,r;
int main(int argc,char **argv)
{
	printf("\nENTER THE CENTER OF THE CIRCLE:-");
	scanf("%d",&cx);
	scanf("%d",&cy);
	printf("\nENTER THE RADIUS OF THE CIRCLE:-");
	scanf("%d",&r);
	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowPosition(0,0); // Set the initial window position and size
  	glutInitWindowSize(640,480);
  	
  	glutCreateWindow("ASSIGN-2"); // Create window with title DDA_Line
  	
  	Init();		 // Initialize drawing colors
  	glutDisplayFunc(display);
  	//glutDisplayFunc(display1);
  	glutMainLoop();
  	return 0;
}  	

void Init()
{
  	/* Set clear color to white */
  	
  	glClearColor(0.0,0.0,0.0,0.0);
  	
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values

  	gluOrtho2D(0,640,0,480);
}

void display()
{
	int a=cx;int b=(cy+r);int c=(cx+(sqrt(3)*r*0.5));int d=(cy-0.5*r);int e=(cx-(sqrt(3)*r*0.5));int f=(cy-0.5*r);	
	circle(cx,cy,r);
	//r=r/2;
	circle(cx,cy,r*0.5);
	BDL(a,b,c,d);
	BDL(a,b,e,f);
	BDL(e,f,c,d);
	
	//BDL(40,40,300,300);
	//BDL(cx,cy+r,(cx+(sqrt(3)*r/2)),(cy-0.5*r));
	//BDL((cx+(sqrt(3)*r/2)),(cy-0.5*r),(cx-(sqrt(3)*r/2)),(cy-0.5*r));
	//BDL((cx-(sqrt(3)*r/2)),(cy-0.5*r),cx,cy+r);
}

void display1()
{
	int a=cx-1*1.732,b=cy-0.5*r,c=cx+1.7320,d=cy-0.5*r,e=cx,f=cy+r;
	BDL(a,b,c,d);
	BDL(a,b,e,f);
	BDL(e,f,c,d);
}


void circle(int a,int b,int radius)
{
	int x=0;
	int y=radius;
	int pk=1-radius;
	glBegin(GL_POINTS);
	glVertex2f(abs(x),abs(y));
	glEnd();
	glFlush();
	int xk=x;int yk=y;
	while(xk<yk)
	{
		if(pk<0)
		{
			xk=xk+1;
			yk=yk;
			
			glBegin(GL_POINTS);
			glVertex2f(a+xk,b+yk);
			glVertex2f(a-xk,b+yk);
			glVertex2f(a+xk,b-yk);
			glVertex2f(a+yk,b+xk);
			glVertex2f(a-yk,b+xk);
			glVertex2f(a+yk,b-xk);
			glVertex2f(a-xk,b-yk);
			glVertex2f(a-yk,b-xk);
			glEnd();
			glFlush();
						
			pk=pk+2*xk + 1;
		}	
	
		else if(pk>=0)
		{
			xk=xk+1;
			yk=yk-1;
			glBegin(GL_POINTS);
			glBegin(GL_POINTS);
			glVertex2f(a+xk,b+yk);
			glVertex2f(a-xk,b+yk);
			glVertex2f(a+xk,b-yk);
			glVertex2f(a+yk,b+xk);
			glVertex2f(a-yk,b+xk);
			glVertex2f(a+yk,b-xk);
			glVertex2f(a-xk,b-yk);
			glVertex2f(a-yk,b-xk);
			glEnd();
			glFlush();
						
			
			pk=pk+2*xk-2*yk +1;
		}
	}	

}	

void BDL(int x1,int y1,int x2,int y2)
{	
	int dx,flag;
	dx=x2-x1;
	int dy;
	dy=y2-y1;
	int m=dy-dx;
		
	int xk,yk;
	xk=x1;yk=y1;
	int pk=2*dy-dx; 
	
	glBegin(GL_POINTS);
	glVertex2f(abs(xk),abs(yk));
	glEnd();
	glFlush();
	
		
		
	if(m<=1)
	{	
		while(xk<=x2)
		{
			if(pk>0)
			{
				pk=pk+2*dy-2*dx;
				yk=yk+1;
			}
			else
			{
				pk=pk+2*dy;
				yk=yk;
			}
			xk=xk+1;
		glBegin(GL_POINTS);
		glVertex2f(abs(xk),abs(yk));
		glEnd();
		glFlush();
		}	
	}
	else
	{
		while(yk<=y2)
		{
			if(pk>0)
			{
				pk=pk+2*dy-2*dx;
				xk=xk+1;
			}
			else
			{
				pk=pk+2*dy;
				xk=xk;
			}
			yk=yk+1;	
		}	
	glBegin(GL_POINTS);
	glVertex2f(abs(xk),abs(yk));
	glEnd();
	glFlush();
	}
}	
	

