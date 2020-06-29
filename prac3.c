#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
typedef struct pixel
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}pixel;
pixel white,grey;	
void rotate();
void fill();
float rot[3][3];
float set1[20][3],ans[20][3];
float root=(20/sqrt(2));
void Init()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
}	
void DDA(int x1,int y1,int x2,int y2)
{
	float dx,dy;
	dx=x2-x1;
	dy=y2-y1;
	int steps=(abs(dx) > abs(dy)) ? (abs(dx)) : (abs(dy));
	float xinc=dx/(float)steps;
	float yinc=dy/(float)steps;
	float x=x1;float y=y1;
	
	for(int i=0;i<=steps;i++)
	{
		glBegin(GL_POINTS);
		glVertex2f(x,y);
		glEnd();
		glFlush();
		x=x+xinc;
		y=y+yinc;
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
	
void draw()
{
	int factor =20;
	int x=320,y=120;
	float a,b;
	DDA(320,120,400,120);
	DDA(320,120,320,200);
	for(int i=0;i<4;i++)
	{
		DDA(320+factor,120,320+factor,200);
		DDA(320,120+factor,400,120+factor);
		factor=factor+20;
	}
	factor=0;
	for(int i=0;i<4;i++)
	{
		if(i==0 ||i==2)
		{
			a=320;b=120+factor;
		}
		
		else
		{
			a=320+20;b=120+factor;
		}
		for(int j=0;j<4;j+=2)
		{
			a=a+j*20;
			boundary_fill(a+1,b+1);	
					
		}
		factor+=20;
	}
				
}
void rotate()
{
	int xinc=0,yinc=0,i,j,k;
	float sum;
	for(i=0;i<10;i=i+2)
	{
		set1[i][0]=320+xinc;set1[i][1]=120;set1[i][2]=1;
		set1[i+1][0]=320+xinc;set1[i+1][1]=200;set1[i+1][2]=1;
		xinc=xinc+20;
	}
	for(i=10;i<20;i=i+2)
	{
		set1[i][0]=320;set1[i][1]=120+yinc;set1[i][2]=1;
		set1[i+1][0]=400;set1[i+1][1]=120+yinc;set1[i+1][2]=1;
		yinc=yinc+20;
	}		
	rot[0][0]=(1/sqrt(2));rot[0][1]=(1/sqrt(2));rot[0][2]=0;
	rot[1][0]=(-1/sqrt(2));rot[1][1]=(1/sqrt(2));rot[1][2]=0;
	rot[2][0]=-320*(1/sqrt(2))+120*(1/sqrt(2))+320;rot[2][1]=-320*(1/sqrt(2))-120*(1/sqrt(2))+120;rot[2][2]=1;
	
	for(i=0;i<20;i++)
	{
		for(j=0;j<3;j++)
		{
		sum=0;
			for(k=0;k<3;k++)
			{
				sum=sum+(set1[i][k]*rot[k][j]);
			}
		ans[i][j]=sum;
		}
	}
	for(i=0;i<20;i++)
		printf("\n%f\t%f\t%f",ans[i][0],ans[i][1],ans[i][2]);
		
	Init();	
	
	glColor3f(1,1,1);		
	for(i=0;i<20;i+=2)
	{
		DDA(ans[i][0],ans[i][1],ans[i+1][0],ans[i+1][1]);
	}
		
}
void fill()
{
	float a,b;	
	rotate();
	for(int i=10;i<17;i=i+2)
	{
		for(int j=0;j<4;j=j+2)
		{
			if(i==10 || i==14)
				{
				a=ans[i][0]+j*root;b=ans[i][1]+j*root;
				}
			else
				{
				a=ans[i][0]+(j+1)*root;b=ans[i][1]+(j+1)*root;
				}
					
			boundary_fill(a,b+1);
		}
	}

}	
void myKey(unsigned char key,int x,int y)
{
	if(key=='r')
	{
		Init();
		fill();
	}
	else
		return;	
}		
					
int main(int argc,char **argv)
{
	white.r=255;
	white.g=255;
	white.b=255;
	
	grey.r=156;
	grey.g=156;
	grey.b=156;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("CHESSBOARD ROTATION");
	gluOrtho2D(0,640,0,480);
	Init();
	glutDisplayFunc(draw);
	glutKeyboardFunc(myKey);
	glutMainLoop();
	
	return 0;	
}	
