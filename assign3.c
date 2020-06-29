/*
SE-10
G-10
23257
PROBLEM SATEMENT:-

			Draw a 4X4 chessboard rotated 45˚ with the horizontal axis. Use Bresenham algorithm to draw all the lines. Use seed fill algorithm to fill white squares of the rotated chessboard.
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include<stdio.h>
#include<math.h>
#include<GL/glu.h>
#include<string.h>
int sign(float arg);
void boundary_fill(float x,float y);
float trans[3][3];
float trans1[3][3];
float rot[3][3];
float ans[4][3];
float ans1[4][3];
float ans2[4][3];
float mat[4][3];
float root=(1/sqrt(2));

typedef struct pixel
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}pixel;
pixel white,grey;	
void init() 
{ 
	glViewport(0,0,640,480);  
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	gluOrtho2D(0.0,640.0,0.0,480.0);  
	glMatrixMode(GL_MODELVIEW);   
}

void BLD(int x1,int y1,int x2,int y2)
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
		temp=dx;	//swap dx and  dy
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

void chess()
{
	int i;
	BLD(ans2[0][0],ans2[0][1],ans2[1][0],ans2[1][1]);		//plot outer chess square
	BLD(ans2[3][0],ans2[3][1],ans2[2][0],ans2[2][1]);
	BLD(ans2[0][0],ans2[0][1],ans2[3][0],ans2[3][1]);
	BLD(ans2[1][0],ans2[1][1],ans2[2][0],ans2[2][1]);
	i=1;

	for(i=1;i<=8;i++)		//for plotting inner squares
	{
		BLD(ans2[0][0]+i*37*root,ans2[0][1]+i*37*root,ans2[3][0]+i*37*root,ans2[3][1]+i*37*root);
		BLD(ans2[0][0]-i*37*root,ans2[0][1]+i*37*root,ans2[1][0]-i*37*root,ans2[1][1]+i*37*root);
	}
}
void rotate()
{
	float factor=37;
	
	rot[0][0]=root;rot[0][1]=root;rot[0][2]=0;
	rot[1][0]=-1*root;rot[1][1]=root;rot[1][2]=0;
	rot[2][0]=0;rot[2][1]=0;rot[2][2]=1;
	
	mat[0][0]=320;mat[0][1]=20;mat[0][2]=1;
	mat[1][0]=616;mat[1][1]=20;mat[1][2]=1;
	mat[2][0]=616;mat[2][1]=316;mat[2][2]=1;
	mat[3][0]=320;mat[3][1]=316;mat[3][2]=1;
	
	trans[0][0]=1;trans[0][1]=0;trans[0][2]=0;
	trans[1][0]=0;trans[1][1]=1;trans[1][2]=0;
	trans[2][0]=-320;trans[2][1]=-20;trans[2][2]=1;
	
	trans1[0][0]=1;trans1[0][1]=0;trans1[0][2]=0;
	trans1[1][0]=0;trans1[1][1]=1;trans1[1][2]=0;
	trans1[2][0]=320;trans1[2][1]=20;trans1[2][2]=1;
	
	int i,j,k;
	float sum;
	for(i=0;i<4;i++)
		{
			for(j=0;j<3;j++)
			{
			sum=0;
				for(k=0;k<3;k++)
				{
					sum=sum+(mat[i][k]*trans[k][j]);
				}
				ans[i][j]=sum;
			}
		}
		for(i=0;i<4;i++)
		{
			for(j=0;j<3;j++)
			{
			sum=0;
				for(k=0;k<3;k++)
				{
					sum=sum+(ans[i][k]*rot[k][j]);
				}
				ans1[i][j]=sum;
			}
		}
		for(i=0;i<4;i++)
		{
			for(j=0;j<3;j++)
			{
			sum=0;
				for(k=0;k<3;k++)
				{
					sum=sum+(ans1[i][k]*trans1[k][j]);
				}
				ans2[i][j]=sum;
			}
		}	
		
}	

void display(void)
{
	int i;
	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(1.0,1.0,1.0);
  	rotate();
	chess();
	float a=ans2[0][0],b=ans2[0][1]+1;
	for(i=1;i<=8;i++)
	{
		for(int j=1;j<=4;j++)
		{
			boundary_fill(a,b);
			a=a+37*2*root;
			b=b+37*2*root +1;
		}
		b=ans2[0][1]+37*root +1;
		if(i==1 || i==3 || i==5 ||i==7)
		a=ans2[0][0]-37*root;	
		else
		a=ans2[0][0];
	}
}

void boundary_fill(float x,float y)
{
     pixel c;
     glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
     
     if((c.r!=white.r || c.g!=white.g || c.b!=white.b) && (c.r!=grey.r || c.g!=grey.g || c.b!=grey.b))
     {
         
          glBegin(GL_POINTS);
          glVertex2d(x,y);
          glColor3ub(grey.r,grey.g,grey.b);
          glEnd();
          glFlush();
          boundary_fill(x,y+1);
          boundary_fill(x-1,y);
          boundary_fill(x,y-1);
          boundary_fill(x+1,y);
     }
    
} 

int main(int argc, char** argv)
 {
	white.r=255;
	white.g=255;
	white.b=255;
	
	grey.r=156;
	grey.g=156;
	grey.b=156;
	
	printf("%f",root);
	
	glutInit(&argc,argv);

	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("CHESS BOARD");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
	
	glutDisplayFunc(display);
	glFlush();
	glutMainLoop();

	return 0;
	
}
