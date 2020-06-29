/*PROBLEM STATEMENT:: Implement any one of the following animation assignments, 
i) Clock with pendulum 
ii) National Flag hoisting 
iii) Vehicle/boat locomotion 
iv) Falling Water drop into the water and generated waves after impact 
Kaleidoscope views generation (at least 3 colorful patterns)
x degree =180/pi rad
x rad=pi/180 degree
*/
/*
SE-10
G-10
23257
PROBLEM STATEMENT:-  
	Draw the following pattern using any Line drawing algorithms.	
*/


#include<stdio.h>
#include<GL/glut.h>
# define PI 3.1415926
#include<math.h>
void Init();	//function delarations
void display();
void display1();
void circle(int a,int b,int radius);
void BDL(int x1,int y1,int x2,int y2);
void DrawCircle(float cx, float cy, float r, int num_segments);
void animation();
int cx,cy,r;


void Init()
{
  	/* Set clear color to white */
  	
  	glClearColor(1.0,1.0,1.0,1.0);
  	glClear(GL_COLOR_BUFFER_BIT);
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values	
  	
}

void display()
{
	glBegin(GL_QUADS);
	glVertex2f(50,50);
	glVertex2f(200,50);
	glVertex2f(200,200);
	glVertex2f(50,200);
	glEnd();
	DrawCircle(75,25,25,20000);
	DrawCircle(175,25,25,20000);
	glBegin(GL_LINES);
		glVertex2f(75,25);
		glVertex2f(75,50);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(75,25);
		glVertex2f(75,0);
	glEnd();	
	glFlush();
		
}
void DrawCircle(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * PI * float(i) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}


void animation()
{
	float i=0.1,angle=0,j=1,x,y;
	angle=(PI/180);
	while(i<400)
	{
		Init();		
		glBegin(GL_QUADS);
		glVertex2f(50+i,50);
		glVertex2f(200+i,50);
		glVertex2f(200+i,200);
		glVertex2f(50+i,200);
		glEnd();
		DrawCircle(75+i,25,25,20000);
		DrawCircle(175+i,25,25,20000);
		glBegin(GL_LINES);
		glVertex2f(75+i,25);
		glVertex2f(75+i+25*cos(angle*j),25+25*sin(angle*j));
		glEnd();
		glBegin(GL_LINES);
		glVertex2f(75+i,25);
		glVertex2f(75+i-25*cos(180+(angle*j)),0-25*sin(180+(angle*j)));
		glEnd();
		glFlush();
		i+=0.1;
		if(j==360)
		j=0;
		j++;
	}	
}

void myKey(unsigned char key,int x,int y)
{
	if(key=='a')
	{
		animation();
		glFlush();		
	}
}
int main(int argc,char **argv)
{
	glutInit(&argc, argv); 
      
   					 // Display mode which is of RGB (Red Green Blue) type 
   	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
      
   					 // Declares window size 
  	glutInitWindowSize(640,480); 
      
    					// Declares window position which is (0, 0) 
    					// means lower left corner will indicate position (0, 0) 
  	glutInitWindowPosition(0, 0);  
  
  	glutCreateWindow("ASSIGN-9"); // Create window with title DDA_Line
  	gluOrtho2D(0,640,0,480);
  	Init();		 // Initialize drawing colors
  	glutDisplayFunc(display);
    	glutKeyboardFunc(myKey);
  	glutMainLoop();
  	return 0;
}  				

