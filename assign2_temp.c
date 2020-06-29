/*
SE-10
G-10
23257
PPROBLEM STATEMENT:-  
	Draw inscribed and Circumscribed circles in the triangle as shown as an example below (Use any Circle drawing and Line drawing algorithms.
	
*/
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
void Init();	//function delarations
void display();
void display1();
void circle(int a,int b,int radius);
void BDL(int x1,int y1,int x2,int y2);
int sign(float arg);
int cx,cy,r;

int main(int argc,char **argv)
{
	printf("\nENTER THE CENTER OF THE CIRCLE:-\nX co-ordinate:- ");	//getting center of circle
	scanf("%d",&cx);
	printf("\nY co-ordinate:- ");
	scanf("%d",&cy);
	printf("\nENTER THE RADIUS OF THE CIRCLE:-");	//getting radius of circle
	scanf("%d",&r);
	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowPosition(0,0); // Set the initial window position and size
  	glutInitWindowSize(640,480);
  	glutCreateWindow("ASSIGN-2"); // Create window with title DDA_Line
  	gluOrtho2D(0,640,0,480);
  	Init();		 // Initialize drawing colors
  	glutDisplayFunc(display);
  	glutMainLoop();
  	return 0;
}  	

void Init()
{
  	/* Set clear color to white */
  	
  	glClearColor(0.0,0.0,0.0,0.0);
  	
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values
}

void display()
{
	int a=cx;int b=(cy+r);int c=(cx+(sqrt(3)*r*0.5));int d=(cy-0.5*r);int e=(cx-(sqrt(3)*r*0.5));int f=(cy-0.5*r);	
	circle(cx,cy,r);	//outer circle
	circle(cx,cy,r*0.5);	//inner circle
	BDL(cx,cy+r,(cx+(sqrt(3)*r/2)),(cy-0.5*r));				//triangle sides
	BDL((cx+(sqrt(3)*r/2)),(cy-0.5*r),(cx-(sqrt(3)*r/2)),(cy-0.5*r));
	BDL((cx-(sqrt(3)*r/2)),(cy-0.5*r),cx,cy+r);	
}

void circle(int a,int b,int radius)		//midpoint circle drawing algorithm
{
	int x=0;
	int y=radius;
	int pk=1-radius;	//initial paramter
	glBegin(GL_POINTS);
	glVertex2f(abs(x),abs(y));
	glEnd();
	glFlush();
	int xk=x;int yk=y;
	while(xk<yk)		//1/8th of the octant
	{
		if(pk<0)	//if decision parameter is negative
		{
			xk=xk+1;	//inc x
			yk=yk;
			
			glBegin(GL_POINTS);
			glVertex2f(a+xk,b+yk);	//plot symmetric points in other octants
			glVertex2f(a-xk,b+yk);
			glVertex2f(a+xk,b-yk);
			glVertex2f(a-xk,b-yk);
			glVertex2f(a+yk,b+xk);
			glVertex2f(a-yk,b+xk);
			glVertex2f(a+yk,b-xk);
			glVertex2f(a-yk,b-xk);
			glEnd();
			glFlush();
						
			pk=pk+2*xk + 1;	//new parameter
		}	
	
		else if(pk>=0)		//if decision parameter is negative
		{
			xk=xk+1;	//inc both x and y
			yk=yk-1;
			glBegin(GL_POINTS);
			glVertex2f(a+xk,b+yk);	//plot symmetric points in other octants
			glVertex2f(a-xk,b+yk);
			glVertex2f(a+xk,b-yk);
			glVertex2f(a-xk,b-yk);
			glVertex2f(a+yk,b+xk);
			glVertex2f(a-yk,b+xk);
			glVertex2f(a+yk,b-xk);
			glVertex2f(a-yk,b-xk);
			glEnd();
			glFlush();
						
			
			pk=pk+2*(xk-yk) +1;	//new parameter
		}
	}	

}	
/*void BDL(int x1,int y1,int x2,int y2)		//techmax algo
{	
	int s1,s2,exchange,y,x,i;
	float dx,dy,g,temp;
	dx=abs(x2-x1);		//calculate dx and dy
	dy=abs(y2-y1);
	x=x1;
	y=y1;
	s1=sign(x2-x1);		//calling sign function
	s2=sign(y2-y1);
	if(dy>dx)		//if m>1,exchange dx and dy
	{
		temp=dx;
		dx=dy;
		dy=temp;
		exchange=1;
	}
	else
	{
		exchange=0;
	}
	g=2*dy-dx;		//initial decision parameter
	i=1;
	while(i<=dx)
	{
		glBegin(GL_POINTS);
		glVertex2f(abs(x),abs(y));	//plot point
		glEnd();
		glFlush();
		while(g>=0)
		{
			if(exchange==1)		//if m>1
				x=x+s1;
			else
				y=y+s2;		//if m<1
			
			g=g-2*dx;
		}
		if(exchange==1)			//if m>1
			y=y+s2;
		else
			x=x+s1;			//if m<1
		g=g+2*dy;
		i++;
	}
}*/
void BDL(int x1,int y1,int x2,int y2)
{	
	float dx;
	dx=abs(x2-x1);
	float dy;
	dy=abs(y2-y1);
	float m=(dy/dx);
	int s1=sign(x2-x1);		//calling sign function
	int s2=sign(y2-y1);	
	int xk,yk,i;
	xk=x1;yk=y1;
	float pk;
	
	glBegin(GL_POINTS);
	glVertex2f(xk,yk);
	glEnd();
	glFlush();
		
	if(m<=1)
	{	i=0;
		pk=2*dy-dx;
		while(i<=dx)
		{
			if(pk>0)
			{
				pk=pk+2*dy-2*dx;
				yk=yk+s2;
			}
			else
			{
				pk=pk+2*dy;
				yk=yk;
			}
			xk=xk+s1;
		glBegin(GL_POINTS);
		glVertex2f(xk,yk);
		i++;
		}
			
	}
	else
	{	i=0;
		pk=2*dx-dy;
		while(i<=dy)
		{
			if(pk>0)
			{
				pk=pk+2*dx-2*dy;
				xk=xk+s1;
			}
			else
			{
				pk=pk+2*dx;
				xk=xk;
			}
			yk=yk+s2;		
		glBegin(GL_POINTS);
		glVertex2f(xk,yk);
		i++;
		}
		
	}
	glEnd();
	glFlush();
}	
int sign(float arg)	//sign function
{
	if(arg<0)
		return -1;	//<0
	else if(arg==0)
		return 0;	//=0
	else
		return 1;	//>0
}									
		
			
	
