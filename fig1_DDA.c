#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

int n;

void LineDDA(int X1,int Y1,int X2,int Y2)
{
  	float dx=(X2-X1);
	float dy=(Y2-Y1);
	int steps;
	float xInc,yInc,x=X1,y=Y1;
	/* Find out whether to increment x or y */
	steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
	//if(steps<0)
	//	steps=steps*(-1);
	xInc=dx/(float)steps;
	yInc=dy/(float)steps;

	/* Plot the first point */
	glVertex2f(x,y);
	int k;
	
	//printf("\nSteps = %d , X-Inc = %f, Y-Inc = %f\n\n",steps,xInc,yInc);

	/* For every step, find an intermediate vertex */
	for(k=0;k<steps;k++)
	{
		x+=xInc+1;
		y+=yInc+1;
		//printf("%d %d\n",abs(x),abs(y));
		glVertex2f(abs(x), abs(y));
	}
	glFlush();
}

void figure(void)
{
	int x1,y1,x2,y2,x3,y3,x4,y4;
	int X1,Y1,X2,Y2,X3,Y3,X4,Y4;
	X1=0;
	Y1=0;
	X2=640;
	Y2=0;
	X3=640;
	Y3=480;
	X4=0;
	Y4=480;
	
	x1=X1;y1=Y1;
	x2=X2;y2=Y2;
	x3=X3;y3=Y3;
	x4=X4;y4=Y4;
	
	int i;
	glBegin(GL_POINTS);
	LineDDA((X1+X2)/2,Y1,(X1+X2)/2,Y4);
	LineDDA(X1,(Y1+Y4)/2,X2,(Y1+Y4)/2);
	for(i=0;i<n;i++)
	{
		LineDDA(X1,Y1,X2,Y2);
		LineDDA(X2,Y2,X3,Y3);
		LineDDA(X3,Y3,X4,Y4);
		LineDDA(X4,Y4,X1,Y1);
		
		X1=(x1+x2)/2;Y1=(y1+y2)/2;
		X2=(x2+x3)/2;Y2=(y2+y3)/2;
		X3=(x3+x4)/2;Y3=(y3+y4)/2;
		X4=(x4+x1)/2;Y4=(y4+y1)/2;
		
		x1=X1;y1=Y1;x2=X2;y2=Y2;x3=X3;y3=Y3;x4=X4;y4=Y4;
	}
	glEnd();
	glFlush();
}
void Init()
{
  	/* Set clear color to white */
  	glClearColor(0.0,0.0,0.0,0.0);
  	
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values

  	gluOrtho2D(0 , 640 , 0 , 480);
}
int main(int argc, char **argv)
{
	
  	printf("Enter depth of image:-\n");
  	scanf("%d",&n);
	
  	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowPosition(0,0); // Set the initial window position and size
  	glutInitWindowSize(640,480);
  	
  	glutCreateWindow("FIGURE_1"); // Create window with title DDA_Line
  	
  	Init(); // Initialize drawing colors

  	glutDisplayFunc(figure);	// Call the displaying function
  	
  	glutMainLoop();// Keep displaying until the program is closed
	return 0;
}
