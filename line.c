
// C program for DDA line generation 
#include<iostream> 
#include <GL/glut.h>
//#include<GL/freeglut.h>
//#include<GL/gl.h>  
//Function for finding absolute value 
int abs (int n) 
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 
  
//DDA Function for line generation 
void DDA() 
{ 
	int flag=0;
	//glClearColor(0.0,0.0,0.0,0.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	
	int X0 = 20, Y0 = 20, X1 = 300, Y1 = 300;
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float) steps; 
    float Yinc = dy / (float) steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) 
    { 
    	//glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	glVertex2f(X,Y); 	// put pixel at (X,Y) 
	if(flag==30)
	{	
		X += Xinc+30;           // increment in x at each step 
		Y += Yinc+30;           // increment in y at each step 
		flag=0; 	
 	}
 	else
 	{
 		X+=Xinc+1;
 		Y+=Yinc+1;
 		flag++;
 	}			      	
    }
    glEnd();
    glFlush(); 
} 
 void Init()
{
  	/* Set clear color to white */
  	glClearColor(1.0,1.0,1.0,1.0);
  	
  	glColor3f(1.0,0.0,0.0);	//Color to use for for drawing objects - (R,G,B) values

  	gluOrtho2D(0 , 640 , 0 , 480);
}
// Driver program 
int main(int argc,char **argv) 
{    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HELLO");
    Init();
    glutDisplayFunc(DDA);
    glutMainLoop(); 
    //DDA(2, 2, 14, 16); 
    
    return 0; 
}  

