#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>

// -------------------- GLOBAL VARIABLES --------------------

// Window parameters
#define TITLE "Hello OpenGL!"
int SCREEN_X = 1024;
int SCREEN_Y = 768;

// Triangle vertices (2D coordinates)
double V1x = -0.5;
double V1y = -0.5;
double V2x = 0.5;
double V2y = -0.5;
double V3x = 0.0;
double V3y = 0.5;

// Scene state
int mode = 1; // 1 = triangle, 2 = cube
int X = 0;
int Y = 0;
float Z = 0;
int dx = 0;
int dy = 0;

// Rendering options
bool projection = 0;   // 0 = orthographic, 1 = perspective
bool wireframe = 0;    // toggle wireframe mode
bool aBlending = 0;    // toggle alpha blending
bool fog = 0;          // toggle fog effect

GLuint index = glGenLists(1);


// -------------------- INITIALIZATION --------------------

/**
 * @brief Initializes OpenGL state including background color, depth testing, viewport, and projection.
 */
void init()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glViewport(0, 0, SCREEN_X, SCREEN_Y);
	glEnable(GL_DEPTH_TEST);
}

/**
 * @brief Sets up projection matrix based on current projection mode (orthographic or perspective).
 */
void initProjectionMode()
{
	float aspect = SCREEN_X / (float)SCREEN_Y;
	glViewport(0, 0, SCREEN_X, SCREEN_Y);

	//select the projection matrix and clear it out
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (projection == 0)
		glOrtho(-aspect, aspect, -1, 1, -20, 20);
	else if (projection == 1)
		gluPerspective(120, aspect, 0.1, 20.0);
}

/**
 * @brief GLUT reshape callback for window resizing.
 *
 * @param x New window width.
 * @param y New window height.
 */
void reshapeFunc(int x, int y) {
	SCREEN_X = x;
	SCREEN_Y = y;
	initProjectionMode();
}


// -------------------- DRAWING FUNCTIONS --------------------

/**
 * @brief Draws a colored triangle using the global vertex coordinates.
 */
void drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2f(V1x, V1y);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2f(V2x, V2y);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2f(V3x, V3y);
	glEnd();
}

/**
 * @brief Draws a cube with semi-transparent colored faces.
 */
void drawCube()
{
	glBegin(GL_QUADS);
	// Front face
	glColor4f(1.0, 0.0, 0.0, 0.5f);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	
	// Right face
	glColor4f(0.0, 1.0, 0.0, 0.5f);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	
	// Left face
	glColor4f(0.0, 0.0, 1.0, 0.5f);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	
	// Bottom face
	glColor4f(1.0, 1.0, 0.0, 0.5f);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	
	// Top face
	glColor4f(1.0, 0.0, 1.0, 0.5f);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	
	// Back face
	glColor4f(0.0, 1.0, 1.0, 0.5f);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glEnd();
}
	

// -------------------- CALLBACKS --------------------

/**
 * @brief Idle function for GLUT. Rotates the animation angle and triggers redisplay.
 */
void idlefunc() { 
	Z += 0.1;
	glutPostRedisplay(); 
}

/**
 * @brief Display callback for drawing the triangle scene.
 */
void displayTriangle()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawTriangle();
	glutSwapBuffers();
}


/**
 * @brief Display callback for drawing the cube scene with rotation and additional objects.
 */
void displayCube()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-dx, 0.0f, 1.0f, 0.0f);
	glRotatef(dy, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Compile cube into display list
	glNewList(index, GL_COMPILE);
	drawCube();
	glEndList();

	glCallList(index);

	// Draw a rotating smaller cube
	glPushMatrix();
	glTranslated(0.5, 0.5, -0.5);
	glScaled(0.5, 0.5, 0.5);
	glRotatef(Z, 0.0f, 0.0f, 1.0f);
	drawCube();

	glPopMatrix();
	
	// Add a sphere
	glTranslated(-0.5, 0.5, -0.5);
	//glColor3f(1.0, 0.0, 1.0);
	glutSolidSphere(0.3, 50, 50);

	glutSwapBuffers();
}

/**
 * @brief Handles keyboard input for quitting, switching modes, and toggling effects.
 *
 * @param key Pressed key.
 * @param x Mouse X (unused).
 * @param y Mouse Y (unused).
 */
void exitKey(unsigned char key, int x, int y)
{
	switch (key) {
		case 'q':		// Quit
			glDeleteLists(index, 1);
			exit(0);
			break;
		case 27:		// ESC
			exit(0);
			break;
		case '1':		// Switch to triangle
			mode = 1;
			glutDisplayFunc(displayTriangle);
			break;
		case '2':		// Switch to cube
			mode = 2;
			glutDisplayFunc(displayCube);
			break;
		case '3':		// Toggle projection
			projection = !projection;
			initProjectionMode();
			break;
		case '4':		// Toggle wireframe
			wireframe = !wireframe;
			if (wireframe)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			else
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			break;
		case '5':		// Toggle alpha blending
			aBlending = !aBlending;
			if (aBlending) {
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}
			else
				glDisable(GL_BLEND);
			break;
		case '6':		// Toggle fog
			fog = !fog;
			if (fog) {
				glEnable(GL_FOG);
				GLfloat fogColor[] = { 0.5f, 0.5f, 0.5f, 1 }; glFogfv(GL_FOG_COLOR, fogColor);
				glFogi(GL_FOG_MODE, GL_LINEAR);
				glFogf(GL_FOG_START, 0.4f);
				glFogf(GL_FOG_END, 0.8f);
			}
			else
				glDisable(GL_FOG);
			break;
	}
}

/**
 * @brief Handles mouse input to move triangle vertices.
 *
 * @param button Mouse button pressed.
 * @param state Button state (GLUT_DOWN/GLUT_UP).
 * @param x Mouse X position.
 * @param y Mouse Y position.
 */
void moveVertex(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mode ==1)
	{
		V1x = (((double)x / (double)SCREEN_X) - 0.5)*(SCREEN_X / (float)SCREEN_Y)*2;
		V1y = ((-1)*(((double)y / (double)SCREEN_Y) - 0.5))*2;
	}
	else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN && mode ==1)
	{
		V2x = (((double)x / (double)SCREEN_X) - 0.5)*(SCREEN_X / (float)SCREEN_Y) * 2;
		V2y = ((-1)*(((double)y / (double)SCREEN_Y) - 0.5)) * 2;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && mode ==1)
	{
		V3x = (((double)x / (double)SCREEN_X) - 0.5)*(SCREEN_X / (float)SCREEN_Y) * 2;
		V3y = ((-1)*(((double)y / (double)SCREEN_Y) - 0.5)) * 2;
	}
	
}

/**
 * @brief Rotates the model or updates triangle vertices during mouse motion.
 *
 * @param x Current mouse X position.
 * @param y Current mouse Y position.
 */
void rotateModel(int x, int y)
{
	if (mode == 1) {
		V1x = (((double)x / (double)SCREEN_X) - 0.5)*(SCREEN_X / (float)SCREEN_Y) * 2;
		V1y = ((-1)*(((double)y / (double)SCREEN_Y) - 0.5)) * 2;
	}
	else if (mode == 2) {
		dx = X - x;
		dy = Y - y;
	}
}


// -------------------- MAIN --------------------

/**
 * @brief Main function: Initializes GLUT, sets callbacks, and enters main loop.
 */
void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_X, SCREEN_Y);
	glutCreateWindow(TITLE);
	init();
	glutDisplayFunc(displayTriangle);
	glutKeyboardFunc(exitKey);
	glutMouseFunc(moveVertex);
	glutMotionFunc(rotateModel);
	glutReshapeFunc(reshapeFunc);
	glutIdleFunc(idlefunc);
	glutMainLoop();
}
