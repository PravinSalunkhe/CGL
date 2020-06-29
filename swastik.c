#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

float mat[20][3];
typedef struct pixel
{
	GLubyte r;
	GLubyte g;
	GLubyte b;
}pixel;
pixel white,red;
void boundary_fill(float x,float y,struct pixel newcolor);
void draw()
{
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
		glVertex2f(55,55);
		glVertex2f(55,45);		
		glVertex2f(5,45);
		glVertex2f(5,5);
		glVertex2f(55,5);
		glVertex2f(55,-55);
		glVertex2f(45,-55);
		glVertex2f(45,-5);
		glVertex2f(45,-5);
		glVertex2f(5,-5);
		glVertex2f(5,-55);
		glVertex2f(-55,-55);
		glVertex2f(-55,-45);
		glVertex2f(-5,-45);
		glVertex2f(-5,-5);
		glVertex2f(-55,-5);
		glVertex2f(-55,55);
		glVertex2f(-45,55);
		glVertex2f(-45,5);
		glVertex2f(-5,5);
		glVertex2f(-5,55);
	glEnd();
	glFlush();
	boundary_fill(0,0,red);			
}
void boundary_fill(float x,float y,struct pixel newcolor)
{
     pixel c;
     glReadPixels(500+x,500+y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
     
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
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
}						
int main(int argc,char **argv)
{
	white.r=255;
	white.g=255;
	white.b=255;
	
	red.r=0;
	red.g=255;
	red.b=0;
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000,1000);
	glutInitWindowPosition(0,0);
	glutCreateWindow("CHESSBOARD ROTATION");
	gluOrtho2D(-1000,1000,-1000,1000);
	Init();
	glutDisplayFunc(draw);
	//glutKeyboardFunc(myKey);
	glutMainLoop();
	
	return 0;	
}	
