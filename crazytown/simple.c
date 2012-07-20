// The OpenGL libraries, make sure to include the GLUT and OpenGL frameworks
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <stdlib.h>

// This is just an example using basic glut functionality.
// If you want specific Apple functionality, look up AGL

void init() // Called before main loop to set up the program
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
}

static int binary;
static const int freq = 300;

// Called at the start of the program, after a glutPostRedisplay() and during idle
// to display a frame
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  if (binary)
    glColor3f(1.0f,1.0f,1.0f); 
  else 
    glColor3f(1.0f,0.0f,0.0f); 

  glBegin(GL_QUADS);
  glVertex3f(  1.0f, -1.0f, 0.2f);     
  glVertex3f(  1.0f, 1.0f, 0.2f);     
  glVertex3f( -1.0f, 1.0f, 0.2f);     
  glVertex3f( -1.0f, -1.0f, 0.2f);     
  glEnd();            

  if (binary)
    glColor4f(1.0f,0.0f,0.0f,0.5f); 
  else 
    glColor4f(1.0f,1.0f,1.0f,0.5f); 
  /*
  glBegin(GL_TRIANGLES);                      // Drawing Using Triangles
  glVertex3f( 0.0f, 1.0f, 0.1f);              // Top
  glVertex3f(-1.0f,-1.0f, 0.1f);              // Bottom Left
  glVertex3f( 1.0f,-1.0f, 0.1f);              // Bottom Right  
  glEnd();                            // Finished Drawing The Triangle

  if (binary)
    glColor3f(0.0f,0.0f,0.0f); 
  else 
    glColor3f(1.0f,0.0f,0.0f); 
*/
  glRasterPos2f(-0.15f, 0);

  //GLUT_BITMAP_8_BY_13
  //GLUT_BITMAP_9_BY_15
  //GLUT_BITMAP_TIMES_ROMAN_10
  //GLUT_BITMAP_TIMES_ROMAN_24
  //GLUT_BITMAP_HELVETICA_10
  //GLUT_BITMAP_HELVETICA_12
  //GLUT_BITMAP_HELVETICA_18

  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'O');
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'M');
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'G');


  glutSwapBuffers();
}

// Called every time a window is resized to resize the projection matrix
void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //  glFrustum(-0.1, 0.1, -float(h)/(10.0*float(w)), float(h)/(10.0*float(w)), 0.2, 9999999.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void timerFunc(int value) {
  binary = (value % 2);

  glutTimerFunc(freq,
		timerFunc,
		value+1);
}

void endFunc(int value) {
  exit(1);
}

void keyboardFunc(unsigned char key, int x, int y) {
  if (key == 27) // ESC
    exit(1);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv); // Initializes glut

  // Sets up a double buffer with RGBA components and a depth component
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

  // Sets the window size to 512*512 square pixels

  // Sets the window position to the upper left
  glutInitWindowPosition(0, 0);

  // Creates a window using internal glut functionality
  glutCreateWindow("Hello!");

  glutFullScreen();

  // passes reshape and display functions to the OpenGL machine for callback
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutIdleFunc(display);

  init();

  glutKeyboardFunc(keyboardFunc);
		   

  glutTimerFunc(freq,
		timerFunc,
		0);

  glutTimerFunc(7000,
		endFunc,
		0);

  // Starts the program.
  glutMainLoop();
  return 0;
}

