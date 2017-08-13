
#ifdef __APPLE__
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <stdio.h>
#  include <iostream>
#  include <string>
#  include <fstream>
#  include <math.h>
#  include <model.cpp>

using namespace std;

#pragma comment(lib, "glew32.lib")
#endif


void drawScene(void);
void drawScene(model);
void resize(int, int);
void keyInput(unsigned char, int, int);
void setup(void);

model m;
float gx,gy,gz;

int main(int argc, char **argv)
{
	m = model(argv[1]);
	gx = 0;
	gy = 0;
	gz = 22;

	glutInit(&argc, argv);
	glutInitContextVersion(3, 0);
	//glutInitContextVersion(4, 2);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Model Viewer: ");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	setup();
	glutPostRedisplay();
	glutMainLoop();
}

void setup(void) 
{
	
	// My Code
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void drawScene(void)
{
	glutPostRedisplay();
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	//glPointSize(15.0);
	//glBegin(GL_LINE_STRIP);

	m.drawModel();

	glFlush();
}


void resize(int w, int h)
{
	//glViewport(w/2+gx, h/2, w, h);
	glViewport(w/2 + gx , h/2 + gy, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0, 5.0, 0, 5.0, -10.0, 10.0);
	//gluLookAt(gx, gy, -gz, 0, 0, 10, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	//gluLookAt(gx, gy, -gz, 0, 0, 10, 0, 1, 0);
	gluLookAt(10 + 10 * cos(gx / 10), 10 + 10 * sin(gy / 10), -gz, 0, 0, 1, 0, 1, 0);
	glLoadIdentity();
	glutPostRedisplay();
}

void keyInput(unsigned char key, int x, int y)
{
	switch(key) 
	{
	  // Press escape to exit.
		case 27:
			exit(0);
			break;
		case 50:
			gy = gy - 0.5;
			 
			break;
		case 56:
			gy = gy + 0.5;
			break;
		case 52: // rotate left
			//cout << "Left: " << gx << "\n";
			gx =  gx - 0.5;
			drawScene();
			break;
		case 54: // rotate right
			//cout << "right:" << gx << "\n";
			gx =  gx + 0.5;
			drawScene();
			break;
		case 43: // z +
			//cout << "right:" << gx << "\n";
			gz = gz + 0.5;
			drawScene();
			break;
		case 45: // z - 
			//cout << "right:" << gx << "\n";
			gz = gz - 0.5;
			drawScene();
			break;
		default:
			cout << "Key Pressed:\t" << (int) key << "\n";
			break;
	}
	cout << "Center (" << gx << "," << gy << "," << gz <<")\n";
	glMatrixMode(GL_MODELVIEW);
	//glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 5.0, 0, 5.0, -3.0, 10.0);
	//gluLookAt(10+10*cos(gx), 10+10*sin(gy), -gz, 0, 0, 10, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluLookAt( 10 * cos(gx/10),  10 * sin(gy/10), -gz, 0, 0, 1, 0, 1, 0);
	cout << "Camera @ (" << 10 * cos(gx / 10) << "," << 10 * sin(gy / 10) << "," << -gz << ")\n";
	
	
	//glutPostRedisplay();
	glutDisplayFunc(drawScene);
}

