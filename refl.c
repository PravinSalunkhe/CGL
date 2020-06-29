#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

float mat[4][3],r[3][3],ans[4][3];
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
		glVertex2f(x,y); // put pixel at (X,Y
		x += xinc;           // increment in x at each step 
		y += yinc;           // increment in y at each step 
	}
	
	glEnd();
glFlush();
}

void display()
{
	DDA(-500,0,500,0);	
	DDA(0,-500,0,500);
	DDA(100,100,400,100);
	DDA(400,100,400,400);
	DDA(400,400,100,400);
	DDA(100,400,100,100);
}
void origin()
{
	float sum=0;
	r[0][0]=-1;r[0][1]=0;r[0][2]=0;
	r[1][0]=0;r[1][1]=-1;r[1][2]=0;
	r[2][0]=0;r[2][1]=0;r[2][2]=1;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
		sum=0;
			for(int k=0;k<3;k++)
			{
				sum=sum+(mat[i][k]*r[k][j]);
			}
		ans[i][j]=sum;
		printf("\n%f",ans[i][j]);
		}
	}
	glColor3f(1.0,1.0,0.0);
	DDA(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
	DDA(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
	DDA(ans[2][0],ans[2][1],ans[3][0],ans[3][1]);
	DDA(ans[3][0],ans[3][1],ans[0][0],ans[0][1]);				
}	
void xaxis()
{
	float sum=0;
	r[0][0]=1;r[0][1]=0;r[0][2]=0;
	r[1][0]=0;r[1][1]=-1;r[1][2]=0;
	r[2][0]=0;r[2][1]=0;r[2][2]=1;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
		sum=0;
			for(int k=0;k<3;k++)
			{
				sum=sum+(mat[i][k]*r[k][j]);
			}
		ans[i][j]=sum;
		printf("\n%f",ans[i][j]);
		}
	}
	glColor3f(1.0,1.0,0.0);
	DDA(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
	DDA(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
	DDA(ans[2][0],ans[2][1],ans[3][0],ans[3][1]);
	DDA(ans[3][0],ans[3][1],ans[0][0],ans[0][1]);	
}
void yaxis()
{
	float sum=0;
	r[0][0]=-1;r[0][1]=0;r[0][2]=0;
	r[1][0]=0;r[1][1]=1;r[1][2]=0;
	r[2][0]=0;r[2][1]=0;r[2][2]=1;

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
		sum=0;
			for(int k=0;k<3;k++)
			{
				sum=sum+(mat[i][k]*r[k][j]);
			}
		ans[i][j]=sum;
		printf("\n%f",ans[i][j]);
		}
	}
	glColor3f(1.0,1.0,0.0);
	DDA(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
	DDA(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
	DDA(ans[2][0],ans[2][1],ans[3][0],ans[3][1]);
	DDA(ans[3][0],ans[3][1],ans[0][0],ans[0][1]);	
}		
void Init()
{
  	/* Set clear color to white */
  	glClearColor(0.0,0.0,0.0,0.0);
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values  	
}
void mykey(unsigned char key,int x,int y)
{
	if(key =='o')
	{
		printf("ORIGIN");
		origin();
	}
	if(key=='x')
	{
		printf("Xaxis");
		xaxis();
	}	
	if(key=='y')
	{
		printf("yaxis");
		yaxis();
	}	
}	
int main(int argc,char **argv)
{
	mat[0][0]=100;mat[0][1]=100;mat[0][2]=1;
	mat[1][0]=400;mat[1][1]=100;mat[1][2]=1;
	mat[2][0]=400;mat[2][1]=400;mat[2][2]=1;
	mat[3][0]=100;mat[3][1]=400;mat[3][2]=1;
	int ch;
	glutInit(&argc,argv); // Initialise GLUT library 

  	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   	// Set the initial display mode
  	
  	glutInitWindowPosition(0,0); // Set the initial window position and size
  	glutInitWindowSize(1000,1000);
  	
  	glutCreateWindow("ASSIGN-1"); // Create window with title DDA_Line
  	gluOrtho2D(-500, 500 , -500 , 500);
  	Init();
  	glutDisplayFunc(display);
  	//glutMainLoop();
  	cout<<"\nMENU\n1.reflection about origin\n2.reflection about xaxis\n3.reflection about yaxis\n4.reflection about arbitrary line\nenter::";
  	cin>>ch;
  	switch(ch)
  	{
  		case 1:
		  	Init();		 // Initialize drawing colors
		  	glutKeyboardFunc(mykey);
		  	glutMainLoop();
		  	break;
		case 2:
			Init();		 // Initialize drawing colors
		  	glutKeyboardFunc(mykey);
		  	glutMainLoop();
		  	break;
		case 3:		Init();		 // Initialize drawing colors
		  	glutKeyboardFunc(mykey);
		  	glutMainLoop();
		  	break;
		 case 4:
		 	//Init();		 // Initialize drawing colors
		  	//glutKeyboardFunc(arb);
		  	//glutMainLoop();
		  	break;
		  default :break;	
	}	  	 	 		  	
	return 0;
}










