#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
# define sin60 0.866025404
# define cos60 0.5
using namespace std;
int i=0,f1;
int x1,y1,x2,y2,x3,y3;
void koch(int x1,int y1,int x2,int y2,int n);
void Init()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
	glLineWidth(3);
}
void line()
{
	i=0;f1=0;
	cout<<"\nenter the x and y cordinate of 1st point::";
	cin>>x1>>y1;
	cout<<"\nenter the x and y cordinate of 2nd point::";
	cin>>x2>>y2;
	
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
	glFlush();
	

}
void mykey(unsigned char key,int x,int y)
{
	
	if(key=='p')
	{
		if(i<5 && f1==0)
		{
			koch(x1,y1,x2,y2,i);
			i++;
		}
		else if(i<5 && f1==1)
		{
			 koch(x1,y1,x3,y3,i);
			 koch(x3,y3,x2,y2,i);
			 koch(x2,y2,x1,y1,i);    
			 i++;
		}
		else
			return;
	}
}		
void triangle()
{	i=0;f1=1;
 	cout<<"\n\n\tTRIANGLE : \n";
        cout<<"\n\tEnter Co-ords (X1,Y1) >> ";
        cin>>x1>>y1;
        cout<<"\n\tEnter Co-ords (X2,Y2) >> ";
        cin>>x2>>y2;
        cout<<"\n\tEnter Co-ords (X3,Y3) >> ";
        cin>>x3>>y3;
        
        glBegin(GL_LINE_LOOP);
                glVertex2d(x1,y1);
                glVertex2d(x2,y2);
                glVertex2d(x3,y3);
              
        glEnd();
        glFlush();
}		
void koch(int x1,int y1,int x2,int y2,int n)
{
	glColor3f(1.0,0.0,0.0);
	float x[5],y[5];
	float lx=(x2-x1)/3,ly=(y2-y1)/3;
	float p,q;
	x[0]=x1;y[0]=y1;
	x[1]=x1+lx;y[1]=y1+ly;
	x[3]=x1+2*lx;y[3]=y1+2*ly;
	x[4]=x2;y[4]=y2;
	
	p=x[3]-x[1];q=y[3]-y[1];
	
	x[2]=p*cos60-q*sin60;y[2]=p*sin60+q*cos60;
	x[2]=x[2]+x[1];   y[2]=y[2]+y[1];       
	if(n>0)
	{
		koch(x[0],y[0],x[1],y[1],n-1);
		koch(x[1],y[1],x[2],y[2],n-1);
		koch(x[2],y[2],x[3],y[3],n-1);
		koch(x[3],y[3],x[4],y[4],n-1);
	}
	else
	{
		glBegin(GL_LINE_STRIP);
			glVertex2f(x[0],y[0]);
			glVertex2f(x[1],y[1]);
			glVertex2f(x[2],y[2]);
			glVertex2f(x[3],y[3]);
			glVertex2f(x[4],y[4]);
		glEnd();
		glFlush();
	}		
}		
	
void menu(int ch)
{
	switch(ch)
	{
		case 1:
			line();
			break;
		case 2:	
			triangle();
			break;
		case 3:
			exit(0);
	}					
}
int main(int argc,char **argv)
{
	printf("\t\t\tKOCH CURVE\t\t");
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(640,480);
	glutCreateWindow("Koch curve");
	gluOrtho2D(0,640,0,480);
	Init();
	//glutDisplayFunc(Display);
	glutCreateMenu(menu);
	glutAddMenuEntry("LINE",1);
	glutAddMenuEntry("TRIANGLE",2);
	glutAddMenuEntry("EXIT",3);
	glutAttachMenu(GLUT_LEFT_BUTTON);
	glutKeyboardFunc(mykey);
	glutMainLoop();
	
}
	

