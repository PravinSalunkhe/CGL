//Assignment 7
//Roll no 23257

#include<GL/glut.h>
//#include<GL/gl.h>
//#include <GL/freeglut.h>
//#include<GL/glu.h>
#include<math.h>
#include<stdio.h>

GLfloat xRotated, yRotated, zRotated;

void init(void)
{
   glClearColor(0,0,0,0); 
}

void DrawCube(void)
{
   
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the drawing buffer.
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10);
    //Translate along z axis
    glRotatef(xRotated,1.0,0.0,0.0);
    // rotation about X axis
    glRotatef(yRotated,0.0,1.0,0.0);
    //rotation about Y axis
  glBegin(GL_QUADS);        // Draw The Cube Using quads
    glColor3f(0.0f,1.0f,0.0f);    // Color Green
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)
    
    glColor3f(1.0f,0.5f,0.0f);    // Color Orange
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Bottom)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Bottom)
    
    glColor3f(1.0f,0.0f,0.0f);    // Color Red    
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
    
    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)
    
    glColor3f(0.0f,0.0f,1.0f);    // Color Blue
    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Left)
    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f,-1.0f);    // Bottom Left Of The Quad (Left)
    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Left)
    
    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
  glEnd();            // End Drawing The Cube 
  glFlush();
}

void animation(void)
{
 
     yRotated += 0.01;
     xRotated += 0.01;
     DrawCube();
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) 
    		return;  //Nothing is visible then, so return
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    //Set a new projection matrix  
    glLoadIdentity();
    gluPerspective(50.0,(GLdouble)x/(GLdouble)y,0.5,20.0);  
    //Angle of view:40 degrees
    //aspect ratio
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
    //1st 2 are lower left co-ordinates 3 is width 4 is height
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    //we initizlilze the glut. functions
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("cube rotation");
    init();
    glutDisplayFunc(DrawCube);
    glutReshapeFunc(reshape);
    glutIdleFunc(animation);
    //Set the function for the animation.
    glutMainLoop();
    return 0;
}

