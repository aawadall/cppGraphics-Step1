
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
#  include <cstring>
#  include <fstream>

using namespace std;

#pragma comment(lib, "glew32.lib")
#endif

/* =============== Begin  Vertix Definition ===============*/
class vertix
{
private:
        float   coord[4]; // Coordinates Array
public:
        vertix();
        vertix(float, float, float);
        vertix loadVertix(string);
        ~vertix();
        float getX();
        float getY();
        float getZ();
        float getW();
	void  translate(float,float,float);

        void displayVertix();
};

vertix::vertix()
{
        coord[0] = 0;
        coord[1] = 0;
        coord[2] = 0;
        coord[3] = 1;
}

vertix::vertix(float ix, float iy, float iz)
{
        coord[0] = ix;
        coord[1] = iy;
        coord[2] = iz;
        coord[3] = 1;
}

vertix vertix::loadVertix(string entry){
        vertix v;
        char *token, *ntoken;
        const char *cline;
        char *line;
        int idx = 0;
        // 1- Test that the first entry is a character v
        if (entry[0] == 'v'){
                cline = entry.c_str(); // char[entry.size() + 1];
                line = (char *)cline;
                token = strtok_r(line, " ",&ntoken);
                token = strtok_r(NULL, " ", &ntoken);
                while (token){
                        coord[idx++] = (float)strtod(token, NULL);
                        if (token)
                                token = strtok_r(NULL, " ",&ntoken);
                }

        }
        // not sure what to do with exception hanlding here 
        return v;
}

vertix::~vertix()
{
}

float vertix::getX(){
        return coord[0];
}

float vertix::getY(){
        return coord[1];
}

float vertix::getZ(){
        return coord[2];
}

float vertix::getW(){
        return coord[3];
}

void vertix::displayVertix(){
        cout << "Displaying Vertix\n";
        cout << "X:\t" << coord[0] << "\tY:\t" << coord[1] << "\tZ:\t" << coord[2] << "\n";
        cout << "W:\t" << coord[3] << "\n";
}

void vertix::translate(float x, float y, float z){ // ranslate Vertix
	coord[0]+= x;
	coord[1]+= y;
	coord[2]+= z;
}
/* =============== End of Vertix Definition ===============*/
/* =============== Begin  Model  Definition ===============*/
class model
        /* This class should be made of:
                * Array of verticies
                * Array of faces
                * List of methods to:
                 o Pull the Array of Verticies
                 o Pull the array of Faces
                 o Translate 
                 o Roate
                 o Scale
        */
{
private:
        vertix  vArray[100000];  //Verticies Array
        int     vCount;         // Number of verticies 
        int     VertixOrder[100000]; // Vertix Order Array
        int     VOCount;
	float	ralpha;		// Rotation Axis
	float	rbeta;
	float	rgamma;
	float	modelX;		// Model Center 
	float	modelY;
	float	modelZ;
	float	modelScale; 	// Scale
public:
        model();
        model(char *); // Use this constructor to load the model from a file 
        ~model();
        void pushVertix(float, float, float);
        void pushVertix(vertix);
        vertix getVertix(int);
        int getVCount();
        void drawModel();
        void vOrder(string);
	void translate(float,float,float); // Model Translate Function
	void rotate(float , float , float ); // Roatet Model using Euler Angles
	void resetRotate(); // Reset Rotation Axis
	void scale(float); // Scale Model 
};

model::model()
{
        //vArray[] = vertix();
        vCount = 0;
}
model::model(char *fileName)
{
        // model constructor using File Name as input 
        vCount = 0; // initialize vCount to 0
        VOCount = 0;
	ralpha = 0;
	rbeta = 0;
	rgamma = 0;
	modelX=0;
	modelY=0;
	modelZ=0;
	modelScale=1;
        // Attempt to load model file using the file name attached 

        cout << "Model Constructor using File name("<< fileName <<") Called\n";

        int result = 0; // Good Value
        int idx = 0;
        string entry;
        std::ifstream infile2(fileName);
        vertix v;

        // Build an array of object entries (General Array)
        while (infile2)
        {
                getline(infile2, entry);
                //entries[idx++] = entry; 
                // Load Verticies
                if (entry[0] == 'v'){
                        vArray[vCount++] = vertix(v.loadVertix(entry));
                        vArray[vCount - 1] = v;
                        vArray[vCount - 1].displayVertix();
                }
                // Load /faces
                if (entry[0] == 'f')
                        vOrder(entry);
        }
        infile2.close();
        cout << "Vertix Order List:\n";
        for (int idx = 0; idx < VOCount; idx++)
                cout << " , " << VertixOrder[idx];
        cout << "\n";
}
model::~model()
{
}

void model::pushVertix(float x, float y, float z){
        vertix t =  vertix(x, y, z);
        pushVertix(t);
}

void model::pushVertix(vertix t){
        vArray[vCount ++] = vertix(t);
        //vCount++;
}

vertix model::getVertix(int idx){
        return vArray[idx];
}

int model::getVCount(){
        return vCount;
}


void model::drawModel(){
        glMatrixMode(GL_MODELVIEW);
        //glBegin(GL_LINE_LOOP);
        glColor3f(0, 0, 0);
        //glBegin(GL_TRIANGLES);
        glColor3f(0,0 , 0);
        glBegin(GL_LINE_LOOP);
        //glBegin(GL_POLYGON);

        for (int idx = 0; idx < VOCount; idx++){
                glVertex3f(vArray[VertixOrder[idx]].getX(), vArray[VertixOrder[idx]].getY(), vArray[VertixOrder[idx]].getZ() );
        	//glColor3f((float)idx/100,(float) (idx%10)/100 , 0);
		}

        glEnd();
        glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(-25,25,-25,25,-25,25);
	//gluLookAt(0,0,-50,0,0,50,0,1,0);

}
void model::vOrder(string entry){ //Builds Vertix Order Array out of the f entry 
        cout << "Constructing Vertix Order Array (" << entry << ")\n";
        //vertix vx;
        char *token, *ntoken;
        const char *cline;
        char *line;

        if (entry[0] == 'f'){
                cline = entry.c_str();
                line = (char *)cline;

                token = strtok_r(line, " ", &ntoken);
                token = strtok_r(NULL, " ", &ntoken); // token has the vertix index 
                while (token){
                        VertixOrder[VOCount++] = (int)strtod(token, NULL);
                        if (token)
                                token = strtok_r(NULL, " ", &ntoken);
                }
        }
}
void model::translate(float x,float y,float z){ // Model Translate Function
	//glMatrixMode(GL_MODELVIEW);
	modelX += x;
	modelY += y;
	modelZ += z;
	//glLoadIdentity();
	glTranslatef(modelX,modelY,modelZ);
/*
	for(int idx=0;idx< vCount;idx++)
		vArray[idx].translate(x,y,z);
*/
}

void model::rotate(float alpha, float beta, float gamma){ // Roatet Model using Euler Angles
	//glMatrixMode(GL_MODELVIEW);
	for(int idx=0;idx< vCount;idx++){
		ralpha += alpha;
		rbeta  += beta;
		rgamma += gamma;
		//glLoadIdentity();
		glRotatef(rgamma,0,0,1);
		glRotatef(rbeta ,0,1,0);
		glRotatef(ralpha,1,0,0);
	}
		//cout << "Roate Called\n";
		//vArray[idx].translate(x,y,z);
}

void model::resetRotate(){
	ralpha = 0;
	rbeta = 0;
	rgamma = 0;
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glRotatef(0,1,0,0);
	glRotatef(0,0,1,0);
	glRotatef(0,0,0,1);
}

void model::scale(float s){
	modelScale *= s;
	//glMatrixMode(GL_MODELVIEW);
	glScalef(modelScale,modelScale,modelScale);
	
}
/* =============== End of Model  Definition ===============*/

void drawScene(void);
void resize(int, int);
void keyInput(unsigned char, int, int);
void setup(void);
// My Code 
//FILE *fh;
model m;
int	 loadModel(char *); // This function will orchestrate loading the object file 
void dumpModel(string[]);	// List down all objects
void getVerticies(string[], string[] );


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//glutInitContextVersion(4, 2);
	glutInitContextVersion(2, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	m = model(argv[1]);

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
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	//glPointSize(15.0);
	m.drawModel();
	glFlush(); 
}

void resize(int w, int h)
{
	glViewport(2, 2, w, h);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
	glOrtho(-1,1,-1,1,1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
	float percesion = 1;
	switch(key) 
	{
	  // Press escape to exit.
		case 27:
			exit(0);
			break;
	  // Camera Controls
/*
		case 'l':
			glMatrixMode(GL_MODELVIEW);
			break;
		case 'k':
			glMatrixMode(GL_PROJECTION);
			gluLookAt(0,0,20,0,0,-20,0,1,0);
			break;
*/
			
	  // Model Controls 
		case '6': // Translate Right
			m.translate(1,0,0);
			break;
		case '4': // Translate Left
			m.translate(-1,0,0);
			break;
		case '8': // Translate Up
			m.translate(0,1,0);
			break;
		case '2': // Translate Down
			m.translate(0,-1,0);
			break;
		case '9': // Translate Depth +
			m.translate(0,0,1);
			break;
		case '3': // Translate Depth -
			m.translate(0,0,-1);
			break;
		case 'y': // Yaw - Rotate Left Model 
			m.rotate(0,percesion,0);
			break;
		case 't': // -ve Yaw - Rotate Right Model 
			m.rotate(0,-percesion,0);
			break;
		case 'p': // Pitch - Rotate Down Model 
			m.rotate(percesion,0,0);
			break;
		case 'o': // -ve Pitch - Rotate up Model 
			m.rotate(-percesion,0,0);
			break;
		case 'r': // Roll - Rotate Around Z Axis   
			m.rotate(0,0,percesion);
			break;
		case 'e': // -ve Roll - Rotate Around Z Axis   
			m.rotate(0,0,-percesion);
			break;
		case '0': // Rest Rotation Axis 
			m.resetRotate();
			break;
		case '+': // Scale Big
			m.scale(1.1);
			break;
		case '-': // Scale Small
			m.scale(0.9);
			break;
		default:
			cout << "Key Pressed: " << key << "\n";
			break;
	}
	glutPostRedisplay();
	//drawScene();
}

