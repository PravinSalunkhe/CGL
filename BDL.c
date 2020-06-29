#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
int u,v,w,x;
void display();
void BDL(int x1,int y1,int x2,int y2);
void Init()
{
  	/* Set clear color to white */
  	
  	glClearColor(0.0,0.0,0.0,0.0);
  	
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values

  	gluOrtho2D(0 , 640 , 0 , 480);
}
void display()
{
	BDL(u,v,w,x);
}	
void BDL(int x1,int y1,int x2,int y2)
{	
	int dx;
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
	
	while((xk!=x2) && (yk!=y2))
	{
		
		if(m<=1)
		{	
			if(pk>0)
			{
				pk=pk+2*dy;
				xk=xk+1;
				yk=yk+1;
			}
			else
			{
				pk=pk+2*(dy-dx);
				xk=xk+1;
				yk=yk;
			}
		}
		else
		{
			if(pk>0)
			{
				pk=pk+2*dy;
				xk=xk+1;
				yk=yk+1;
			}
			else
			{
				pk=pk+2*(dy-dx);
				xk=xk;
				yk=yk+1;
			}	
		
		}
	glBegin(GL_POINTS);
	glVertex2f(abs(xk),abs(yk));
	glEnd();
	glFlush();
	}
	
}	
	

int main(int argc,char **argv)
{
	printf("\nENTER THE STARTING x CO-ordinate:- ");
	scanf("%d",&u);
	printf("\nENTER THE STARTING y co-ordinate of line:-");
	scanf("%d",&v);
	printf("\nENTER THE ENDING x CO-ordinate:-");
	scanf("%d",&w);
	printf("\nENTER THE ENDING y co-ordinate of line:-");
	scanf("%d",&x);
	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowPosition(0,0); // Set the initial window position and size
  	glutInitWindowSize(640,480);
  	
  	glutCreateWindow("ASSIGN-2"); // Create window with title DDA_Line
  	
  	Init();		 // Initialize drawing colors
  	glutDisplayFunc(display);
  	glutMainLoop();
	return 0;
}	
