/*
SE-10
G-10
23257
PROBLEM STATEMENT:-  
	Draw the following pattern using any Line drawing algorithms.	
*/


#include<stdio.h>
#include<GL/glut.h>

int n,width,height;

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
		glVertex2f(abs(x),abs(y)); // put pixel at (X,Y) 
		x += xinc;           // increment in x at each step 
		y += yinc;           // increment in y at each step 
	}
	glFlush();
}

void display()
{
	int a1,b1,a2,b2,a3,b3,a4,b4;
	int m1,n1,m2,n2,m3,n3,m4,n4;
	a1=10;
	b1=10;
	a2=a1+620;
	b2=10;
	a3=a1+620;
	b3=b1+460;
	a4=10;
	b4=b1+460	;
	
	m1=a1;n1=b1;
	m2=a2;n2=b2;
	m3=a3;n3=b3;
	m4=a4;n4=b4;
	glBegin(GL_POINTS);

	DDA((a1+a2)/2,b1,(a1+a2)/2,b4);		//getting axes lines
	DDA(a1,(b1+b4)/2,a2,(b1+b4)/2);	
	for(int i=0;i<n;i++)
	{
		DDA(a1,b1,a2,b2);	//side 1
		DDA(a2,b2,a3,b3);	//side 2
		DDA(a3,b3,a4,b4);	//side 3
		DDA(a4,b4,a1,b1);	//side 4
		
		a1=(m1+m2)/2;b1=(n1+n2)/2;	//calculating mid points
		a2=(m2+m3)/2;b2=(n2+n3)/2;
		a3=(m3+m4)/2;b3=(n3+n4)/2;
		a4=(m4+m1)/2;b4=(n4+n1)/2;
		
		m1=a1;n1=b1;m2=a2;n2=b2;m3=a3;n3=b3;m4=a4;n4=b4;
		
	}
	glEnd();
	glFlush();
}	
		
void Init()
{
  	/* Set clear color to white */
  	glClearColor(0.0,0.0,0.0,0.0);
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values

  	
}
int main(int argc,char **argv)
{
	printf("\nENTER THE DEPTH OF THE DIAGRAM:-");
	scanf("%d",&n);
	
	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowPosition(0,0); // Set the initial window position and size
  	glutInitWindowSize(640,480);
  	
  	glutCreateWindow("ASSIGN-1"); // Create window with title DDA_Line
  	gluOrtho2D(0 , 640 , 0 , 480);
  	Init();		 // Initialize drawing colors
  	glutDisplayFunc(display);
  	glutMainLoop();
	return 0;
}


/*OUTPUT:-

admin1@pravin-27:~$ g++ assign1.c -lglut -lGLU -lGL
admin1@pravin-27:~$ ./a.out

ENTER THE DEPTH OF THE DIAGRAM:-5
admin1@pravin-27:~$ 

*/
