
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
#  include <model.h>
//#include ""
using namespace std;

#pragma comment(lib, "glew32.lib")
#endif


void drawScene(void);
void resize(int, int);
void keyInput(unsigned char, int, int);
void setup(void);
// My Code 
FILE *fh;
int	 loadModel(char *); // This function will orchestrate loading the object file 
void dumpModel(string[]);	// List down all objects
void getVerticies(string[], string[] );

struct Vertix{
	char	tag;
	float	x;
	float	y;
	float	z;
	float	n;
	int		order;
};

struct vList
{
	Vertix	v[100];
	int		size;
};

vList	vx;
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//glutInitContextVersion(4, 2);
	glutInitContextVersion(2, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CMPUT511 - Assignment 1");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	setup();

	glutMainLoop();
}

void setup(void) 
{
	// My Code
	loadModel("CMPUT511 - Assignment 1");
	// My Code
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(15.0);
	//glBegin(GL_POLYGON);
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(1.000000, -1.000000, -1.000000);
		glVertex3f(1.000000, -1.000000, 1.000000);
		glVertex3f(-1.000000, -1.000000, 1.000000);
		glVertex3f(-1.000000, -1.000000, -1.000000);
		glVertex3f(1.000000, 1.000000, -0.999999);
		glVertex3f(0.999999, 1.000000, 1.000001);
		glVertex3f(-1.000000, 1.000000, 1.000000);
		glVertex3f(-1.000000, 1.000000, -1.000000);
	glEnd();
	glFlush(); 
}

void resize(int w, int h)
{
	glViewport(w/2, h/2, w, h);
	//glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
	switch(key) 
	{
	  // Press escape to exit.
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

int loadModel(char *fileName){
	using namespace std;
	cout << "Started loadModel()\n";
	int result = 0; // Good Value
	int idx = 0;
	string entry;
	string entries[100];
	string verticies[100];
	std::ifstream infile2(fileName);

	while (infile2)
	{
		getline(infile2, entry);
		cout << "Entry:" << entry << "\n";
		entries[idx++] =  entry; // += entry;
	}
	infile2.close();
	// 2- Load Verticies 
	cout << "Extract Verticies, size is: " << sizeof(verticies) << "\n";
	getVerticies(entries,  verticies);
	//cout << sizeof(verticies);
	// 3- Load Faces 
	cout << "Done Reading file " << fileName << " with " << idx << " entries \n";
	char test = 1;
	int idx2 = 0;
	while (test){
		cout << "Vertix: " << verticies[idx2] << " \n";
		test = verticies[idx2++][0];
	}
	
	cout << "End of loadModel()\n";
	return result;
}

void dumpModel(string model[]){
	cout << "Size of Model = " << sizeof(model)/sizeof(*model) << "\n";
	for (int idx = 0; idx < sizeof(model); idx++)
		cout << idx << ":" << model[idx] << "\n";
}

void getVerticies(string model[], string vertices[]){
	int idx2 = 0;
	for (int idx = 0; model[idx+1][0]; idx++)
		if (model[idx][0] == 'v')
			vertices[idx2++] = model[idx];
}
