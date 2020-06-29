/*SE-10
  G-10
  23257
  PROBLEM STATEMENT::	
  Implement translation, sheer, rotation and scaling transformations on equilateral triangle and rhombus.
*/
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265
#include <stdio.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include<GL/glu.h>

float shear_x[3][3],shear_y[3][3],mat[3][3],ans[3][3],ans1[3][3],ans2[3][3],rot[3][3],trans[3][3],trans1[3][3],s[3][3];
float n,a,b,sum;
int flag,i,j,k,val = 180/PI;
int sign(float arg);

void init() 
{ 
	glViewport(0,0,640,480);  
	glMatrixMode(GL_PROJECTION);  
	glLoadIdentity();  
	gluOrtho2D(0.0,640.0,0.0,480.0);  
	glMatrixMode(GL_MODELVIEW);   
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
				
void display()
{
	BLD(50,50,100,50);
	BLD(100,50,75,50+sqrt(50*50-25*25));
	BLD(75,50+sqrt(50*50-25*25),50,50);
	
}
void shear_func()
{	
	shear_x[0][0]=1;shear_x[0][1]=0;shear_x[0][2]=0;
	shear_x[1][0]=n;shear_x[1][1]=1;shear_x[1][2]=0;
	shear_x[2][0]=0;shear_x[2][1]=0;shear_x[2][2]=1;
	
	shear_y[0][0]=1;shear_y[0][1]=n;shear_y[0][2]=0;
	shear_y[1][0]=0;shear_y[1][1]=1;shear_y[1][2]=0;
	shear_y[2][0]=0;shear_y[2][1]=0;shear_y[2][2]=1;
	
		for(i=0;i<3;i++)
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
		if(flag==0)
		{
			for(i=0;i<3;i++)
				{
					for(j=0;j<3;j++)
					{
					sum=0;
						for(k=0;k<3;k++)
						{
							sum=sum+(ans[i][k]*shear_x[k][j]);
						}
						ans1[i][j]=sum;
					}
				}
		}
		if(flag==1)
		{
			for(i=0;i<3;i++)
				{
					for(j=0;j<3;j++)
					{
					sum=0;
						for(k=0;k<3;k++)
						{
							sum=sum+(ans[i][k]*shear_y[k][j]);
						}
						ans1[i][j]=sum;
					}
				}
		}				
		for(i=0;i<3;i++)
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
	BLD(ans2[0][0],ans2[0][1],ans2[1][0],ans2[1][1]);
	BLD(ans2[1][0],ans2[1][1],ans2[2][0],ans2[2][1]);
	BLD(ans2[2][0],ans2[2][1],ans2[0][0],ans2[0][1]);
}
void scale()
{	
	s[0][0]=a;s[0][1]=0;s[0][2]=0;
	s[1][0]=0;s[1][1]=b;s[1][2]=0;
	s[2][0]=0;s[2][1]=0;s[2][2]=1;
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
		sum=0;
			for(k=0;k<3;k++)
			{
				sum=sum+(mat[i][k]*s[k][j]);
			}
			ans[i][j]=sum;
		}
	}
	BLD(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
	BLD(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
	BLD(ans[2][0],ans[2][1],ans[0][0],ans[0][1]);
	
}	
void rotate()
{				
	rot[0][0]=cos(n*val);rot[0][1]=sin(n*val);rot[0][2]=0;
	rot[1][0]=-1*sin(n*val);rot[1][1]=cos(n*val);rot[1][2]=0;
	rot[2][0]=0;rot[2][1]=0;rot[2][2]=1;
	
	trans[0][0]=1;trans[0][1]=0;trans[0][2]=0;
	trans[1][0]=0;trans[1][1]=1;trans[1][2]=0;
	trans[2][0]=-50;trans[2][1]=-50;trans[2][2]=1;
	
	trans1[0][0]=1;trans1[0][1]=0;trans1[0][2]=0;
	trans1[1][0]=0;trans1[1][1]=1;trans1[1][2]=0;
	trans1[2][0]=50;trans1[2][1]=50;trans1[2][2]=1;
	
	for(i=0;i<3;i++)
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
		for(i=0;i<3;i++)
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
		for(i=0;i<3;i++)
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
			
	BLD(ans2[0][0],ans2[0][1],ans2[1][0],ans2[1][1]);
	BLD(ans2[1][0],ans2[1][1],ans2[2][0],ans2[2][1]);
	BLD(ans2[2][0],ans2[2][1],ans2[0][0],ans2[0][1]);
}	
void translate()
{	
	trans[0][0]=1;trans[0][1]=0;trans[0][2]=0;
	trans[1][0]=0;trans[1][1]=1;trans[1][2]=0;
	trans[2][0]=a;trans[2][1]=b;trans[2][2]=1;
	
	for(i=0;i<3;i++)
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
	BLD(ans[0][0],ans[0][1],ans[1][0],ans[1][1]);
	BLD(ans[1][0],ans[1][1],ans[2][0],ans[2][1]);
	BLD(ans[2][0],ans[2][1],ans[0][0],ans[0][1]);	
		
}	
	
void myKey(unsigned char key,int x,int y)
{
	if(key =='s')
	{
		printf("SHEARING");
		shear_func();
		glFlush();	
	}
	if(key=='r')
	{
		printf("ROTATION");
		rotate();
		glFlush();
	}	
	if(key=='t')
	{
		printf("TRANSLATE");
		translate();
		glFlush();
	}	
	if(key=='l')
	{
		printf("SCALE");
		scale();
		glFlush();
	}	
}	
int main(int argc, char** argv)
{
	
	int ch;
	glutInit(&argc,argv);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("ASSIGN-6");
	init();
	glClear(GL_COLOR_BUFFER_BIT);
		
mat[0][0]=50;mat[0][1]=50;mat[0][2]=1;
mat[1][0]=100;mat[1][1]=50;mat[1][2]=1;
mat[2][0]=75;mat[2][1]=(50+sqrt(50*50-25*25));mat[2][2]=1;

	trans[0][0]=1;trans[0][1]=0;trans[0][2]=0;
	trans[1][0]=0;trans[1][1]=1;trans[1][2]=0;
	trans[2][0]=-50;trans[2][1]=-50;trans[2][2]=1;
	
	trans1[0][0]=1;trans1[0][1]=0;trans1[0][2]=0;
	trans1[1][0]=0;trans1[1][1]=1;trans1[1][2]=0;
	trans1[2][0]=50;trans1[2][1]=50;trans1[2][2]=1;
	do
	{
	printf("\n2-D TRANSFORMATIONS\nMENU\n1.X-SHEAR\n2.Y-SHEAR\n3.ROTATION\n4.TRANSLATION\n5.SCALINg\n6.EXIT\nENTER UR CHOICE:-");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			printf("\nENTER THE AMOUNT OF X-shear");
			scanf("%f",&n);
			flag=0;	
			glutDisplayFunc(display);
			glutKeyboardFunc(myKey);
			glFlush();
			glutMainLoop();
			break;
		case 2:
			printf("\nENTER THE AMOUNT OF Y-shear");
			scanf("%f",&n);
			flag=1;
			glutDisplayFunc(display);
			glutKeyboardFunc(myKey);
			
			glFlush();
			glutMainLoop();
			break;
		case 3:
			printf("\nENTER THE ANGLE OF ROTATION(IN DEGREES)::");
			scanf("%f",&n);
			glutDisplayFunc(display);
			glutKeyboardFunc(myKey);
			
			glFlush();
			glutMainLoop();
			break;
		case 4:	
			printf("\nENTER THE AMOUNT OF X TRANSLATION::");
			scanf("%f",&a);
			printf("\nENTER THE AMOUNT OF Y TRANSLATION::");
			scanf("%f",&b); 
			glutDisplayFunc(display);
			glutKeyboardFunc(myKey);
			glFlush();
			glutMainLoop();
			break;
		case 5:
			printf("\nENTER THE AMOUNT OF X SCALING::");
			scanf("%f",&a);
			printf("\nENTER THE AMOUNT OF Y SCALING::");
			scanf("%f",&b); 
			glutDisplayFunc(display);
			glutKeyboardFunc(myKey);
			glFlush();
			glutMainLoop();
			break;
	}
	}while(ch!=6);									
	return 0;
	
}
