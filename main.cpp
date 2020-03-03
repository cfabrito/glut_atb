#include <AntTweakBar.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

static float g_time = 0.0f;

static float g_size = 0.0f;
static float g_change = 1.0f;

float lerp(float t, float min, float max)
{
    return (1-t) * min + t * max;
}

void axis_system()
{
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 3, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 3);
	glEnd();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	TwWindowSize(w, h);
}

float frequency = 1.0;

void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(3.0,1.0,5.0, 
		      0.0,0.0,-1.0,
			  0.0f,1.0f,0.0f);

    float delta_time = (glutGet(GLUT_ELAPSED_TIME)/1000.f - g_time);

    g_time = glutGet(GLUT_ELAPSED_TIME) / 1000.f;

	axis_system();
	glColor3f(1.0, 1.0, 1.0);
    glutWireTeapot(sin(frequency * 2.0f * M_PI * g_time) * 0.5 + 1.0);

	TwDraw();
	// End of frame
	glutSwapBuffers();
}

void processKeys(int key, int xx, int yy) {

	if (TwEventSpecialGLUT(key, xx, yy))
		return;
}

void processKeyboard(unsigned char key, int xx, int yy) {

	if (TwEventKeyboardGLUT(key, xx, yy))
		return;
}

TwBar* bar;

void initATB()
{
	TwInit(TW_OPENGL, NULL);
	TwWindowSize(300, 100);

	bar = TwNewBar("Teapot");
	TwAddVarRW(bar, "Frequency", TW_TYPE_FLOAT, &frequency, "min=0.1 step=0.1");
}

int main(int argc, char **argv)
{
	// AntTweakBar must receive all GLUT events (keys, mouse, reshape)

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(300,100);
    glutInitWindowSize(800,800);

    glutCreateWindow("CG@DI");

	initATB();

    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);
    glutDisplayFunc(renderScene);

	glutSpecialFunc(processKeys);
	glutKeyboardFunc(processKeyboard);

	// Register ATB event handlers
	glutMouseFunc((GLUTmousebuttonfun)TwEventMouseButtonGLUT);
	glutMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);
	glutPassiveMotionFunc((GLUTmousemotionfun)TwEventMouseMotionGLUT);


// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);

// enter GLUT's main loop
	glutMainLoop();
	
	return 1;
}

