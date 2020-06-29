/*
SE-10
23257
PROBLEM STATEMENT:- Draw the polygons by using the mouse. Choose colors by clicking on the designed color pane. Use window port to draw. (Use DDA algorithm for line drawing)
*/

//#include<GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
//#include <GL/freeglut.h>
//#include<stdio.h>
//#include<math.h>
//#include<GL/glu.h>
//#include<string.h>
using namespace std;
int m[10],n[10];
int k=1,i=0,flag=0;
void boundary_fill(float x,float y,struct pixel l);
typedef struct pixel
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}pixel;
pixel red,blue,white,green,yellow,p;
int abs(int m)		//absolute function
{
	if(m<=0)
		return (m*(-1));
	else
		return m;
}
void DDA(int x0,int y0,int x1,int y1)
{
	float dx=x1-x0;
	float dy=y1-y0;
	
	int steps=(abs(dx) > abs(dy)) ? (abs(dx)) : (abs(dy));	//calculate steps required for generating pixels
	
	float xinc=dx/(float)steps;	//calculate increment in x& y for each steps
	float yinc=dy/(float)steps;
	
	float x=x0;
	float y=y0;
	
	for(int i=0;i<=steps;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(x,y); // put pixel at (X,Y) 
		x += xinc;           // increment in x at each step 
		y += yinc;           // increment in y at each step 
	}
}
void boundary_fill(float x,float y,struct pixel newcolor)
{
     pixel c;
     glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
     
     if((c.r!=white.r || c.g!=white.g || c.b!=white.b) && (c.r!=newcolor.r || c.g!=newcolor.g || c.b!=newcolor.b))
     {
         
          glBegin(GL_POINTS);
          glVertex2d(x,y);
          glColor3ub(newcolor.r,newcolor.g,newcolor.b);
          glEnd();
          glFlush();
          boundary_fill(x,y+1,newcolor);
          boundary_fill(x-1,y,newcolor);
          boundary_fill(x,y-1,newcolor);
          boundary_fill(x+1,y,newcolor);
     }
    
} 
	
		
void Init()
{
  	/* Set clear color to red */
  	glClearColor(0.0,0.0,0.0,0.0);
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(0.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values

  	
}
void display1(int x1,int y1,int x2,int y2)
{
	glColor3f(1.0, 1.0, 1.0);
	DDA(x1,y1,x2,y2);
	glEnd();	
	glFlush();
	glutSwapBuffers();
	fflush(stdout);
}	
void display()
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POINTS);
	DDA(50,50,250,50);
	DDA(50,100,250,100);
	DDA(50,50,50,100);
	DDA(100,50,100,100);
	DDA(150,50,150,100);
	DDA(200,50,200,100);
	DDA(250,50,250,100);
	glEnd();
	glFlush();
	boundary_fill(75,75,red);
	boundary_fill(125,75,blue);
	boundary_fill(175,75,green);
	boundary_fill(225,75,yellow);
	glColor3f(1.0, 1.0,0.0);
}
void myMouseFunc(int button, int state, int x, int y)
{
	int a,b,e,d;
	switch(button)
	{
		case GLUT_LEFT_BUTTON :
					if(state==GLUT_DOWN)
					{
						if(flag==1)
						{
							printf(" FILL ");
							a=x;b=480-y;
						     	glReadPixels(a,b,1,1,GL_RGB,GL_UNSIGNED_BYTE,&p);
								return;
						}		     							
						printf("DOWN");
						m[i] = x;
						n[i] = 480 - y;
						printf(" %d %d ",m[i],n[i]);
						if(k!=1)
						{
							display1(m[i-1],n[i-1],m[i],n[i]);		
							k++;
							i++;
						}
						else
						{
							k++;
							i++;
						}
					}		
					else
					{
						printf("UP");
						if(flag==1)
						{

					     			printf(" fill 2 ");
					     			d=x;e=480-y;
					     			if(p.r==red.r && p.g==red.g && p.b==red.b)
					     				boundary_fill(d,e,red);
					     			else if(p.r==blue.r && p.g==blue.g && p.b==blue.b)
					     				boundary_fill(d,e,blue);	
					     			else if(p.r==green.r && p.g==green.g && p.b==green.b)
					     				boundary_fill(d,e,green);
					     			else if(p.r==yellow.r && p.g==yellow.g && p.b==yellow.b)
					     				boundary_fill(d,e,yellow);		
						else
							return;	
						}
					}							
					break;
		case GLUT_RIGHT_BUTTON :
					if(state==GLUT_DOWN)
					{
						display1(m[i-1],n[i-1],m[0],n[0]);
						printf("right");
						flag=1;	
					}			
								
					break;
		default:
			break;				
	}
	
}

int main(int argc, char **argv) 
{
	white.r=255;
	white.g=255;
	white.b=255;
	
	red.r=255;
	red.g=0;
	red.b=0;
	
	blue.r=0;
	blue.g=255;
	blue.b=255;
	
	green.r=0;
	green.g=255;
	green.b=0;
	
	yellow.r=255;
	yellow.g=255;
	yellow.b=0;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
    
    //Defines 640 X 480 Window size
	glutInitWindowSize(640, 480);

	glutCreateWindow("Mouse Func");
	gluOrtho2D(0 , 640 , 0 , 480);
	Init();
	glutDisplayFunc(display);
	glColor3f(1.0, 1.0, 1.0);
	glutMouseFunc(myMouseFunc);
	glutMainLoop();

	return 0;
}
