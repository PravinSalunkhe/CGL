
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
void DDA(float x0,float y0,float x1,float y1)
{
	float dx=x1-x0;
	float dy=y1-y0;
	int k=0,j=0;
	int steps=(abs(dx) > abs(dy)) ? (abs(dx)) : (abs(dy));	//calculate steps required for generating pixels
	
	float xinc=dx/(float)steps;	//calculate increment in x& y for each steps
	float yinc=dy/(float)steps;
	
	float x=x0;
	float y=y0;
	
	for(int i=0;i<=steps;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(abs(x),abs(y)); // put pixel at (X,Y) 
		glEnd();
		if(k<10 && k>=0)
		{
			x += xinc;           // increment in x at each step 
			y += yinc;           // increment in y at each step 
			k++;
		}
		else
		{
			x += xinc;           // increment in x at each step 
			y += yinc;           // increment in y at each step 
			k++;
			j=1;
		}	
		if(k==10)
		{
			i=i+5;
			x+=5*xinc;y+=5*yinc;k=-2;j=0;
			k++;
		}
		if(j==1)
		{
			i=i+5;
			x+=5*xinc;y+=5*yinc;j=0;k++;
		}	
					
	}
	glFlush();
}
void display()
{
	DDA(20,20,400,20);
	DDA(400,20,200,250);
	DDA(200,250,20,20);	
	DDA(500,450,500,30);
}			
void Init()
{
  	/* Set clear color to white */
  	glClearColor(1.0,1.0,1.0,0.0);
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
  	glutInitWindowSize(1000,800);
  	
  	glutCreateWindow("ASSIGN-1"); // Create window with title DDA_Line
  	gluOrtho2D(0 , 1000 , 0 , 800);
  	Init();		 // Initialize drawing colors
  	glutDisplayFunc(display);
  	glutMainLoop();
	return 0;
}


