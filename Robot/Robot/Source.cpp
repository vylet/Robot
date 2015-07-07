/*
Harshit Mehta      2011A8PS312P
Atul Mittal        2011B4A7861P

*/


#include <GL/glut.h>
#include <math.h>

#define COLOR_PLANE 0.45
#define COLOR_TORSO 0.6

#define COLOR_HEAD 0.7

#define COLOR_UPPER_ARM 0.55
#define COLOR_LOWER_ARM 0.55
#define COLOR_HAND 0.1

#define COLOR_THIGH 0.6
#define COLOR_LOWER_LEG 0.6
#define COLOR_FOOT 0.4

#define TORSO_X 16
#define TORSO_Y 30
#define TORSO_Z 10

#define HEAD_X 10
#define HEAD_Y 10
#define HEAD_Z 8

#define UPPER_ARM_X 3
#define UPPER_ARM_Y 13
#define UPPER_ARM_Z 3

#define LOWER_ARM_X 2
#define LOWER_ARM_Y 10
#define LOWER_ARM_Z 2

#define HAND_X 1.5
#define HAND_Y 6
#define HAND_Z 6

#define THIGH_X 7
#define THIGH_Y 15
#define THIGH_Z 7

#define LOWER_LEG_X 5
#define LOWER_LEG_Y 15
#define LOWER_LEG_Z 5

#define FOOT_X 6
#define FOOT_Y 2
#define FOOT_Z 8

GLboolean wireframe = false;
GLfloat theta[] = {0.0,0.0};
GLfloat pos = 0;

void init (void)	{
	glutInitWindowPosition (10, 10);						// Set top-left display-window position.
	glutInitWindowSize (800, 800);							// Set display-window width and height.
	glutCreateWindow ("Robot");	// Create display window.
	glClearColor (1.0, 1.0, 1.0, 0.0); 						// Set display-window color to white.
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
}

void drawCuboid (GLfloat len_x, GLfloat len_y, GLfloat len_z) {
  glPushMatrix();
  glScalef(len_x, len_y, len_z);

  if(wireframe)	{
	  glColor3f(0, 0, 0);
	  glutWireCube(1.0f); 
  }
  else {
	  glutSolidCube(1.0f); 
  }
  glPopMatrix();
}

void drawSphere (GLfloat radius) {
  glPushMatrix();

  if(wireframe)	{
	  glColor3f(0, 0, 0);
	  glutWireSphere(radius,5,5); 
  }
  else {
	  glutSolidSphere(radius,20,20); 
  }
  glPopMatrix();
}

void drawCircleL (GLfloat radius){
    glBegin(GL_TRIANGLE_FAN);
	GLfloat angle,x1= 0.5, y1 = 0.5, x2,y2;
    glVertex2f(x1,y1);
    for (angle=1.0f;	angle<361.0f;	angle+=0.2)
    {
    x2 = x1+sin(angle)*radius;
    y2 = y1+cos(angle)*radius;
    glVertex2f(x2,y2);
    }
    glEnd();
}

void drawCircleR (GLfloat radius){
    glBegin(GL_TRIANGLE_FAN);
	GLfloat angle,x1= -0.5, y1 = 0.5, x2,y2;
    glVertex2f(x1,y1);
    for (angle=1.0f;	angle<361.0f;	angle+=0.2)
    {
    x2 = x1+sin(angle)*radius;
    y2 = y1+cos(angle)*radius;
    glVertex2f(x2,y2);
    }
    glEnd();
}

void drawRobot ()	{
	// clear buffers, reset transformation matrix, and set the color 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear buffers
	glLoadIdentity();

// view transformation
	gluLookAt(0,0,65,    0,0,0,    0,1,0);
//	gluLookAt(30,10,65,    0,0,0,    0,1,0);

//floor
	glPushMatrix();
	glColor3f(1,0.5,0);
	glTranslatef(0, -TORSO_Y/2 - THIGH_Y -LOWER_LEG_Y- FOOT_Y- 3.05, 0);
	drawCuboid(150,1,500);
	glPopMatrix();

//roof
	glPushMatrix();
	glColor3f(COLOR_PLANE,COLOR_PLANE,COLOR_PLANE);
	glTranslatef(0, TORSO_Y/2 +THIGH_Y +LOWER_LEG_Y+ FOOT_Y +3.05, 0);
	drawCuboid(150,1,500);
	glPopMatrix();

//right wall
	glPushMatrix();
	glColor3f(COLOR_PLANE + 0.3,COLOR_PLANE + 0.3,COLOR_PLANE + 0.3);
	glTranslatef(75, 0, 0);
	drawCuboid(1,100,500);
	glPopMatrix();

//left wall
	glPushMatrix();
	glTranslatef(-75, 0, 0);
	drawCuboid(1,100,500);
	glPopMatrix();

// Draw torso
	glTranslatef(0,0,pos);                  
	glPushMatrix();  
//Draw torso
    glColor3f(COLOR_TORSO,COLOR_TORSO,COLOR_TORSO); 
	drawCuboid(TORSO_X,TORSO_Y,TORSO_Z);   
// Draw left upper arm
	glColor3f(COLOR_UPPER_ARM,COLOR_UPPER_ARM,COLOR_UPPER_ARM); 
	glTranslatef(TORSO_X/2 + UPPER_ARM_X/2 + 1, UPPER_ARM_Y, 0);	                           
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glTranslatef(0, -UPPER_ARM_Y/2, 0);
	glPushMatrix();
	drawCuboid(UPPER_ARM_X,UPPER_ARM_Y,UPPER_ARM_Z);


// Draw left lower arm
	glColor3f(COLOR_LOWER_ARM,COLOR_LOWER_ARM,COLOR_LOWER_ARM);
	glTranslatef(0,-UPPER_ARM_Y/2 - LOWER_ARM_Y/2-1,0);                              
	glPushMatrix();	
	drawCuboid(LOWER_ARM_X,LOWER_ARM_Y,LOWER_ARM_Z);

// Draw left hand
	glColor3f(COLOR_HAND,COLOR_HAND,COLOR_HAND);
	glTranslatef(0,-LOWER_ARM_Y/2 - HAND_Y/2-1,0);
	drawCuboid(HAND_X,HAND_Y,HAND_Z);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();

// Draw right upper arm
	glColor3f(COLOR_UPPER_ARM,COLOR_UPPER_ARM,COLOR_UPPER_ARM); 
	glTranslatef(-TORSO_X/2 - UPPER_ARM_X/2 - 1, UPPER_ARM_Y, 0);	                           
	glRotatef(theta[1], 1.0, 0.0, 0.0);
	glTranslatef(0, -UPPER_ARM_Y/2, 0);
	glPushMatrix();
	drawCuboid(UPPER_ARM_X,UPPER_ARM_Y,UPPER_ARM_Z);


// Draw right lower arm
	glColor3f(COLOR_LOWER_ARM,COLOR_LOWER_ARM,COLOR_LOWER_ARM); 
	glTranslatef(0,-UPPER_ARM_Y/2 - LOWER_ARM_Y/2-1,0);                           
	glPushMatrix();
	drawCuboid(LOWER_ARM_X,LOWER_ARM_Y,LOWER_ARM_Z);


// Draw right hand
	glColor3f(COLOR_HAND,COLOR_HAND,COLOR_HAND);
	glTranslatef(0,-LOWER_ARM_Y/2 - HAND_Y/2-1,0);										
	drawCuboid(HAND_X,HAND_Y,HAND_Z);

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

    glPushMatrix();

// Draw head
	glColor3f(COLOR_HEAD,COLOR_HEAD,COLOR_HEAD);
	glTranslatef(0,+TORSO_Y/2 + HEAD_Y/2+1,0);
	drawCuboid(HEAD_X,HEAD_Y,HEAD_Z);

// Draw nose
	glColor3f(0.1,0.1,0.1);
	glBegin(GL_POLYGON);
	glVertex2f(0,2);
	glVertex2f(-1,-0.5);
	glVertex2f(+1,-0.5);
	glEnd();
	
// making right ear
	glPushMatrix();
	glTranslatef(-HEAD_X/2 - 0.9,2.0,0);
	glColor3f(0.45,0.45,0.45);
	drawCuboid(.9,5,.5);
	glTranslatef(-1,0,0);
	glColor3f(0.25,0.25,0.25);
	drawCuboid(.9,3,.5);
	glTranslatef(-.9,4,0);
	glColor3f(0.15,0.15,0.15);
	drawCuboid(.5,8,.5);
	glTranslatef(0,4,0);
	glColor3f(1,0.1,0.1);
	drawSphere (1);
	glPopMatrix();


// making left ear
	glPushMatrix();
	glTranslatef(HEAD_X/2 + 0.9,2.0,0);
	glColor3f(0.45,0.45,0.45);
	drawCuboid(.9,5,.5);
	glTranslatef(1,0,0);
	glColor3f(0.25,0.25,0.25);
	drawCuboid(.9,3,.5);
	glTranslatef(.9,4,0);
	glColor3f(0.15,0.15,0.15);
	drawCuboid(.5,8,.5);
	glTranslatef(0,4,0);
	glColor3f(1,0.1,0.1);
	drawSphere (1);
	glPopMatrix();

//making left eye
	glPushMatrix();
    glTranslatef(-3,+3.5,0.5);
 
    glColor3f(0.3,0.3,1.0);
	drawCircleL(1.4);
    
    glColor3f(0,0,0);
	drawCircleL(1.3);	

    glColor3f(.30,.30,1.0);
	drawCircleL(0.6);

	glPopMatrix();

// making right eye
	glPushMatrix();
	glTranslatef(3,+3.5,0.5);

    glColor3f(0.3,0.3,1.0);
	drawCircleR(1.4);
    
    glColor3f(0,0,0);
	drawCircleR(1.3);	

    glColor3f(.30,.30,1.0);
	drawCircleR(0.6);

	glPopMatrix();

//draw mouth
	glPushMatrix();
	glTranslatef(0,-1.5,0);
	glColor3f(0,0,0);
	drawCuboid(6,0.15,1);
	glTranslatef(0,-0.7,0);
	drawCuboid(6,0.15,1);
	glPopMatrix();
	glPopMatrix();

//Go to lower body
	glPushMatrix();
	glTranslatef(0,-TORSO_Y/2 - THIGH_Y/2-1,0);
	

//Draw left thigh
	glPushMatrix();
	glTranslatef(TORSO_X/6+THIGH_X/2 ,0,0);
	glColor3f(COLOR_THIGH,COLOR_THIGH,COLOR_THIGH);  
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	drawCuboid(THIGH_X,THIGH_Y,THIGH_Z);

//Draw left lower leg
	glPushMatrix();
	glTranslatef(0,-THIGH_Y/2 -LOWER_LEG_Y/2 - 1,0);
	glColor3f(COLOR_LOWER_LEG,COLOR_LOWER_LEG,COLOR_LOWER_LEG); 
	drawCuboid(LOWER_LEG_X,LOWER_LEG_Y,LOWER_LEG_Z);

//Draw left foot
	glPushMatrix();
	glTranslatef(0,-LOWER_LEG_Y/2 - FOOT_Y/2 - 1,+FOOT_Z/2);
	glColor3f(COLOR_FOOT,COLOR_FOOT,COLOR_FOOT);
	drawCuboid(FOOT_X,FOOT_Y,FOOT_Z);
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

//Draw right thigh
	glPushMatrix();
	glTranslatef(-TORSO_X/6-THIGH_X/2 ,0,0);
	glColor3f(COLOR_THIGH,COLOR_THIGH,COLOR_THIGH); 
	glRotatef(theta[1], 1.0, 0.0, 0.0);
	drawCuboid(THIGH_X,THIGH_Y,THIGH_Z);

//Draw right lower leg
	glPushMatrix();
	glTranslatef(0,-THIGH_Y/2 -LOWER_LEG_Y/2 - 1,0);
	glColor3f(COLOR_LOWER_LEG,COLOR_LOWER_LEG,COLOR_LOWER_LEG); // lower leg
	drawCuboid(LOWER_LEG_X,LOWER_LEG_Y,LOWER_LEG_Z);

//Draw right foot
	glPushMatrix();
	glTranslatef(0,-LOWER_LEG_Y/2 - FOOT_Y/2 - 1,+FOOT_Z/2);
	glColor3f(COLOR_FOOT,COLOR_FOOT,COLOR_FOOT);
	drawCuboid(FOOT_X,FOOT_Y,FOOT_Z);
	
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	//glPopMatrix();


// Show origin
/*
	glColor3f(0, 0, 0);		
	glPointSize(3);
    glBegin(GL_POINTS);
	glVertex3i (0,0,0);
	glEnd();
*/
	glFlush();
	glutSwapBuffers();
}

void myReshape1(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(130.0, GLfloat(w)/h, 10, 100);
  //glOrtho(-5, +5, -10, +10, -20, +20); 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void keyBoard(unsigned char key, int x, int y)	{
	if( key == (unsigned char)'W' || key == (unsigned char)'w'){
		wireframe = !wireframe;
	}
	GLfloat l = theta[0], r = theta[1];
	if( key == (unsigned char)'F' || key == (unsigned char)'f'){
		if(l == 0 && r == 0){
			l = -30; r = 30;
		}
		else if(l == 30 && r == -30){
			l = -30; r = 30;
		}
		else{
			l = 30; r = -30;
		}
		pos++;
	}
	if( key == (unsigned char)'B' || key == (unsigned char)'b'){
		if(l == 0 && r == 0){
			l = 30; r = -30;
		}
		else if(l == 30 && r == -30){
			l = -30; r = 30;
		}
		else{
			l = 30; r = -30;
		}
		pos--;
	}
	theta[0] = l;
	theta[1] = r;
	glutPostRedisplay();
}

int main (int argc, char** argv)
{
	glutInit (&argc, argv);									// Initialize GLUT.
	init ( );												// Execute initialization procedure.
	glutReshapeFunc(myReshape1);
	glutDisplayFunc (drawRobot);
	glutKeyboardFunc (keyBoard);					
	glutMainLoop ( );										// Display everything and wait.
}

