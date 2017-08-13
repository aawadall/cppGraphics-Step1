
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
#  include <math.h>
using namespace std;

#pragma comment(lib, "glew32.lib")
#endif

#define rPercesion  10   // Rotation Percesion
#define tPercesion  0.1 // Translation Percesion
#define zPercesion  0.1 // Zoom Percesion
#define degToRad 0.0174532925 // Degrees to rad multiplier
static GLint fogMode;
float density = 0.3;
bool isFog;
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
/* =============== Begin  Camera Definition ===============*/
class camera
	/* This class should hold the basic information and behavior
	   of a camera in an abstract way
	   This class should:
		* have the flag to toggle between Ortho and Prespective
		* have Camera Location
		* have Camera destination
		* have near and far defined
		* have up defined
	*/
{
private:
	char	viewType;	// v = Ortho / V = Prespective
	float	cameraX;	// Camera Location
	float 	cameraY;
	float	cameraZ;
	float	lookAtX;	// Camera Destination 
	float	lookAtY;
	float	lookAtZ;
	float	upX;		// Coordinates defining up
	float	upY;
	float	upZ;
	float	near;		// Near
	float	far;		// Far
	float	left;		// Viewing Window
	float	right;
	float	top;
	float	bottom;
	float	theta1,theta2,theta3;	// Camera Orientation holder
public:
	camera();
	camera(char,float,float,float,float,float,float,float,float,float); //,float,float); // Full constructor
	void setCamera(char,float,float,float,float,float,float,float,float,float);
	void setWindow(float,float,float,float,float,float); // Viewing Window
	void switchVt(char); // Switch View Type
	GLenum getVt(); // Get View Type
	void view();
	void translate(float,float,float);
	void rotate(float,char);
	void displayInformation();
};

camera::camera(){
}

camera::camera(	char	vt,
		float	cx,	float	cy,	float	cz,
		float	lax,	float	lay,	float	laz,
		float	ux,	float	uy,	float	uz)
		//float	n,	float	f)
{
	setCamera(vt, cx, cy, cz, lax, lay, laz, ux, uy, uz);

}

void camera::setCamera(	char	vt,
			float	cx,	float	cy,	float	cz,
			float	lax,	float	lay,	float	laz,
			float	ux,	float	uy,	float	uz)
{
	viewType = vt;	// v = Ortho / V = Prespective
	cameraX  = cx;	// Camera Location
	cameraY  = cy;
	cameraZ  = cz;
	lookAtX  = lax;	// Camera Destination 
	lookAtY  = lay;
	lookAtZ  = laz;
	upX      = ux;		// Coordinates defining up
	upY      = uy;
	upZ      = uz;
	//near     = n;		// Near
	//far      = f;
	theta1    = 0;
	theta2    = 0;
	theta3    = 0;
}
void camera::setWindow(float l,float r,float b,float t,float n,float f){ // Viewing Window

	near   = n;		// Near
	far    = f;		// Far
	left   = l;		// Viewing Window
	right  = r;
	top    = t;
	bottom = b;
	
}
void camera::switchVt(char vt){ // Switch View Type
	viewType = vt; 
}
GLenum camera::getVt(){ // Get View Type
	switch(viewType)
	{
		case 'v': return GL_MODELVIEW;
			break;
		case 'V': return GL_PROJECTION;
			break;
		default:  return GL_MODELVIEW;
			break;
	}
}

void camera::view(){ // Activate camera based on current settings
float mx[100000];
 //glMatrixMode(GL_MODELVIEW);
	if(isFog){
		glEnable(GL_FOG);  //fog must always be enabled
		   {
		      GLfloat fogColor[4] = {1, 1, 1, 0};  

		      fogMode = GL_EXP;  //initial fog mode
		      glFogi (GL_FOG_MODE, fogMode);
		      glFogfv (GL_FOG_COLOR, fogColor);  //set the fog color to grey
		      glFogf (GL_FOG_DENSITY, density);   //set the fog density
		      glHint (GL_FOG_HINT, GL_NICEST);  //nicest possible rendering
		      glFogf (GL_FOG_START, 1.0);  //start distance for linear fog
		      glFogf (GL_FOG_END, 5.0);  //end distance for linear fog
		   }
		   glClearColor(1, 1, 1, 0);  // set the background color = fog color
	}
	//glLoadIdentity();
	/*switch(viewType){
		case 'V':
			//glLoadIdentity();
			
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glGetFloatv(GL_MODELVIEW_MATRIX, mx);
			//glOrtho(left,right,bottom,top,near,far);	
			//glMatrixMode(GL_PROJECTION); //TODO check this part, cuasing view to vanish 
			
			gluLookAt(cameraX,cameraY,cameraZ,lookAtX,lookAtY,lookAtZ,upX,upY,upZ);
			break;
		case 'v':
		 	glMatrixMode(GL_MODELVIEW);
			glOrtho(left,right,bottom,top,near,far);
			//gluLookAt(cameraX,cameraY,cameraZ,lookAtX,lookAtY,lookAtZ,upX,upY,upZ);
			break;	
		default:
			glMatrixMode(GL_MODELVIEW);
			glOrtho(left,right,bottom,top,near,far);
			break;
		}*/
	glOrtho(left,right,bottom,top,near,far);
	gluLookAt(cameraX,cameraY,cameraZ,lookAtX,lookAtY,lookAtZ,upX,upY,upZ);
	
	
	// To Preserve Last state
	/*near   = n;		// Near
	far    = f;		// Far
	left   = l;		// Viewing Window
	right  = r;
	top    = t;
	bottom = b; */
	/*
	cameraX  = cx;	// Camera Location
	cameraY  = cy;
	cameraZ  = cz;
	lookAtX  = lax;	// Camera Destination 
	lookAtY  = lay;
	lookAtZ  = laz;
	upX      = ux;		// Coordinates defining up
	upY      = uy;
	upZ      = uz;
	*/
}

void camera::translate(float x, float y, float z){
	cameraX += x;
	cameraY += y;
	cameraZ += z;
	
	//left  += x;
	//right += x;
	//bottom+= y;
	//top   += y;
	//near  += z;
	//far   += z;
	
}

void camera::rotate(float argTheta, char direction){
	float distance = sqrt(pow((cameraX - lookAtX),2) + pow((cameraY - lookAtY),2) + pow((cameraZ - lookAtZ),2));
	if (viewType == 'V'){
		//glMatrixMode(GL_PROJECTION); //TODO check this part, cuasing view to vanish 
		//gluLookAt(cameraX,cameraY,cameraZ,lookAtX,lookAtY,lookAtZ,upX,upY,upZ);
		switch(direction){
			case 'L': // Roll Camera 
				theta1 += argTheta;
				//if (theta1 > 360) theta1 -= 360;
				//if (theta1 < 0	) theta1 += 360;
				upX = sin(theta1*degToRad);
				upY = cos(theta1*degToRad);
				// upZ should not be impacted
				//cout << "Up compontnents [" << upX << "," << upY << "," << upZ << "]\n";
				break;
			case 'T': // Tilt Camera
				theta2 += argTheta;
				//if (theta2 > 360) theta2 -= 360;
				//if (theta2 < 0  ) theta2 += 360;
				lookAtY = distance * cos(theta2*degToRad);
				lookAtZ = distance * sin(theta2*degToRad);
				//upY    += cos(theta2*degToRad);
				//upZ    += sin(theta2*degToRad);
				break;
			case 'A': // Pan Camera
				theta3 += argTheta;
				//if (theta3 > 360) theta3 -= 360;
				//if (theta3 < 0  ) theta3 += 360;
				lookAtX = distance * cos(theta3*degToRad);
				lookAtZ = distance * sin(theta3*degToRad);
			
			break;
			}
		//glMatrixMode(GL_PROJECTION);
		//gluLookAt(cameraX,cameraY,cameraZ,lookAtX,lookAtY,lookAtZ,upX,upY,upZ);
		}

	//cout << "Looking at: ("<< lookAtX<<","<<lookAtY<<","<<lookAtZ<<")\n";
}

void camera::displayInformation(){ // Display Camera Information
	/* 
        char	viewType;	// v = Ortho / V = Prespective
	float	cameraX;	// Camera Location
	float 	cameraY;
	float	cameraZ;
	float	lookAtX;	// Camera Destination 
	float	lookAtY;
	float	lookAtZ;
	float	upX;		// Coordinates defining up
	float	upY;
	float	upZ;
	float	near;		// Near
	float	far;		// Far
	float	left;		// Viewing Window
	float	right;
	float	top;
	float	bottom;
	float	theta1,theta2,theta3;	// Camera Orientation holder
	*/
	cout << "Camera Information:\n";
	cout << "Eye    Coordinates [" << cameraX << "\t," << cameraY << "\t," << cameraZ << "\t]\n";
	cout << "Center Coordinates [" << lookAtX << "\t," << lookAtY << "\t," << lookAtZ << "\t]\n";
	cout << "Up Vector          [" << upX << "\t," << upY << "\t," << upZ << "\t]\n";
	cout << "Camera Orientation [" << theta1 << "\t," << theta2  << "\t," << theta3 << "\t](in Degrees)\n";
	cout << "Viewing Window [Left:" << left << "\tRight: " << right << "\tBottom: " << bottom << "\tTop:"<< top << "]\n";
	cout << "               [Near:" << near << "\tFar  : " << far << "]\n";
	cout << "Camera Mode: "	;
	if (viewType == 'V')	
		cout << "Prespective\n";
	else	
		cout << "Orthogonal\n";
}
/* =============== End of Camera Definition ===============*/
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
	//camera  cam1;
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
	void resetTranslate(); // Reset Translate 
	void scale(float); // Scale Model 
	void resetScale();
	void doNothing(); // To call all transformations before current transformation
	void dumpModel(); // Dump model into an object file
	void dumpModel(char*);
	void setCenter();
	void displayInformation(); // Dump Model Information 
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
	vArray[vCount++] = vertix(0,0,0);
	VertixOrder[VOCount++] = 0;
        // Build an array of object entries (General Array)
        while (infile2)
        {
                getline(infile2, entry);
                //entries[idx++] = entry; 
                // Load Verticies
                if (entry[0] == 'v'){
                        vArray[vCount++] = vertix(v.loadVertix(entry));
                        vArray[vCount - 1] = v;
                       // vArray[vCount - 1].displayVertix();
                }
                // Load /faces
                if (entry[0] == 'f')
                        vOrder(entry);
        }
        infile2.close();
        //cout << "Vertix Order List:\n";
        //for (int idx = 0; idx < VOCount; idx++)
        //        cout << " , " << VertixOrder[idx];
       // cout << "\n";
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

        glBegin(GL_LINE_LOOP);
        //glBegin(GL_TRIANGLE_FAN);
        //glBegin(GL_LINES);
        //glBegin(GL_LINE_STRIP);
	glColor3f(0,0 , 0);
        	for (int idx = 0; idx < VOCount; idx++){
                	glVertex3f(vArray[VertixOrder[idx]].getX(), vArray[VertixOrder[idx]].getY(), vArray[VertixOrder[idx]].getZ() );
		//	vArray[VertixOrder[idx]].displayVertix();
		}
        glEnd();


}
void model::vOrder(string entry){ //Builds Vertix Order Array out of the f entry 
        //cout << "Constructing Vertix Order Array (" << entry << ")\n";
        //vertix vx;
        char *token, *ntoken;
        const char *cline;
        char *line;
	int vidx=0;
        if (entry[0] == 'f'){
                cline = entry.c_str();
                line = (char *)cline;

                token = strtok_r(line, " ", &ntoken);
                token = strtok_r(NULL, " ", &ntoken); // token has the vertix index 
		//token = strtok_r(NULL, " ", &ntoken); // Skip first entry 
                while (token){
			if(vidx++<3)
                        	VertixOrder[VOCount++] = (int)strtod(token, NULL);
			else
                        	{
                        	//VertixOrder[VOCount++] = VertixOrder[VOCount-1];
				VertixOrder[VOCount++] = (int)strtod(token, NULL);
				}
				//VertixOrder[VOCount++] = -1;
                        if (token)
                                token = strtok_r(NULL, " ", &ntoken);
                }
        }
}
void model::translate(float x,float y,float z){ // Model Translate Function
	
	//doNothing();
	modelX += x;
	modelY += y;
	modelZ += z;
	cout << "translating model by (" << modelX << "," << modelY << "," << modelZ << ")\n";
	//glLoadIdentity();
	glTranslatef(modelX,modelY,modelZ);
/*
	for(int idx=0;idx< vCount;idx++)
		vArray[idx].translate(x,y,z);
*/
}

void model::rotate(float alpha, float beta, float gamma){ // Roatet Model using Euler Angles

		ralpha += alpha;
		rbeta  += beta;
		rgamma += gamma;
		cout << "RotatingModel by (" << ralpha << "," << rbeta << "," << rgamma <<")\n"; 
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		glRotatef(rgamma,0,0,1);
		glRotatef(rbeta ,0,1,0);
		glRotatef(ralpha,1,0,0);

}

void model::resetRotate(){
	ralpha = 0;
	rbeta = 0;
	rgamma = 0;
	glLoadIdentity();
	glRotatef(0,1,0,0);
	glRotatef(0,0,1,0);
	glRotatef(0,0,0,1);
}

void model::resetTranslate(){
	modelX = 0;
	modelY = 0;
	modelZ = 0;

	glTranslatef(0,0,0);
}
void model::scale(float s){
	modelScale *= s;
	//glMatrixMode(GL_MODELVIEW);
	//doNothing();
	glLoadIdentity();
	glScalef(modelScale,modelScale,modelScale);
	//cout << "Model Scale: " << modelScale << "\n";
}

void model::resetScale(){
	modelScale = 1;
	glLoadIdentity();
	glScalef(modelScale,modelScale,modelScale);
}
void model::doNothing(){
        glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	rotate(0,0,0);
	translate(0,0,0);
	scale(1);
}

void model::dumpModel(){
	dumpModel("output.obj");
}
void model::dumpModel(char *fName){
 	ofstream modelFile;
  	modelFile.open(fName);
	cout << "Dumping Model on File: " << fName << "\n";
	// o entry = Filename
	modelFile << "o " << fName << "\n";
	// v entries
	for (int idx=0;idx<vCount;idx++)
		modelFile << "v " << vArray[idx].getX() << " " << vArray[idx].getY() << " " << vArray[idx].getZ() << " " << vArray[idx].getW() << "\n"; 
	// f entries
	for (int idx=0; idx < VOCount;idx++)
		if (VOCount - idx > 2)
			modelFile << "f " << VertixOrder[idx++] << " " <<VertixOrder[idx++] << " " << VertixOrder[idx] << "\n";
		else if(VOCount - idx > 1)
			modelFile << "f " << VertixOrder[idx++] << " " <<VertixOrder[idx] << "\n";
	modelFile.close();
}

void model::setCenter(){
	// Get Mean values for X, Y and Z and set Center based on such values
	//float tempX = 0;
	//float tempY = 0;
	//float tempZ = 0;

	float maxX = 0;
	float maxY = 0;
	float maxZ = 0;
	float minX = 0;
	float minY = 0;
	float minZ = 0;
	
	float xScale,yScale,zScale,fScale=1;

	for (int idx=0;idx< vCount; idx++){
		// Prepare Scaling Data
		if (maxX < vArray[idx].getX())
			maxX = vArray[idx].getX();
		if (minX > vArray[idx].getX())
			minX = vArray[idx].getX();
		if (maxY < vArray[idx].getY())
			maxY = vArray[idx].getY();
		if (minY > vArray[idx].getY())
			minY = vArray[idx].getY();
		if (maxZ < vArray[idx].getZ())
			maxZ = vArray[idx].getZ();
		if (minZ > vArray[idx].getZ())
			minZ = vArray[idx].getZ();
		// Prepare Positioning Data
		//tempX += vArray[idx].getX()/vCount;
		//tempY += vArray[idx].getY()/vCount;
		//tempZ += vArray[idx].getZ()/vCount;
	}
	//translate(tempX,tempY,tempZ);	
	//cout << "Centred at (" << tempX <<"," << tempY<<"," << tempZ<<")\n";
	//glTranslatef(modelX, modelY, modelZ);
	xScale = maxX - minX;
	yScale = maxY - minY;
	zScale = maxZ - minZ;	
	if (fScale < xScale)
		fScale = xScale;
	if (fScale < yScale)
		fScale = yScale;
	if (fScale < zScale)
		fScale = zScale;
	//cout << "Scale: "<< 1/fScale << " X: " << xScale << " Y: " << yScale << " Z: " << zScale << "\n";
	scale(1/fScale);
	translate(-1/(maxX - minX), -1/(maxY - minY), -1/( maxZ - minZ)-2);
	//translate(0,0,-2);
	//doNothing();	
	//drawModel();					 
}

void model::displayInformation(){ // Display Model Information
	/* 
        int     vCount;         // Number of verticies 
        int     VOCount;
	float	ralpha;		// Rotation Axis
	float	rbeta;
	float	rgamma;
	float	modelX;		// Model Center 
	float	modelY;
	float	modelZ;
	float	modelScale; 
	*/
	cout << "Model Information:\n";
	cout << "Model Coordinates [" << modelX << "," << modelY << "," << modelZ << "]\n";
	cout << "Model Orientation [" << ralpha << "," << rbeta  << "," << rgamma << "](in Degrees)\n";
	cout << "Model Scale: " << modelScale << " , VertixCount: " << vCount << " VO Count: " << VOCount << "\n";
}
/* =============== End of Model  Definition ===============*/

void drawScene(void);
void resize(int, int);
void keyInput(unsigned char, int, int);
void arrawKeyInput(int , int, int);
void setup(void);
// My Code 
//FILE *fh;
model  m;
camera cam1;

int	 loadModel(char *); // This function will orchestrate loading the object file 
void dumpModel(string[]);	// List down all objects
void getVerticies(string[], string[] );


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	//glutInitContextVersion(4, 2);
	glutInitContextVersion(2, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	// Camera Code
	cam1 = camera(	'v',
			0, 0, 0, // Eye
			0, 0,-1,  // Center
			0, 1, 0); // Up
	cam1.setWindow(-1 ,1 ,-1, 1 ,1 ,100); 
	// Camera
	isFog = false;
	m = model(argv[1]);
	m.setCenter();
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("CMPUT511 - Assignment 1");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(arrawKeyInput);
	setup();

	glutMainLoop();
}

void setup(void) 
{
	glClearColor(1, 1, 1, 0.0);
	//glClearColor(1.0, 1.0, 1.0, 0.0);
}

void drawScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	//glPointSize(15.0);
	m.drawModel();
	m.doNothing(); 
	cam1.view();
	//
	//glMatrixMode(cam1.getVt());
	//glOrtho(left,right,bottom,top,near,far);
	//gluLookAt(cameraX,cameraY,cameraZ,lookAtX,lookAtY,lookAtZ,upX,upY,upZ);
	//
	glFlush(); 
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
	/*
	glOrtho(-1,1,-1,1,1,1);
	glMatrixMode(GL_MODELVIEW);
	*/
	//glLoadIdentity();
	m.doNothing();
	cam1.view();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y)
{
	/*	
	float rPercesion = 10;   // Rotation Percesion
	float tPercesion = 0.1; // Translation Percesion
	float zPercesion = 0.1; // Zoom Percesion
	*/
	//glMatrixMode(cam1.getVt());
	switch(key) 
	{
	  // Press q to exit.
		case 'q':
			exit(0);
			break;
	  // Camera Controls

		case 'D': // Dolly +ve == X 
			cam1.translate(rPercesion,0,0);
			break;		
		case 'd': // Dolly -ve
			cam1.translate(-rPercesion,0,0);
			break;
		case 'C': // Crane +ve == Y
			cam1.translate(0,rPercesion,0);
			break;		
		case 'c': // Crane -ve
			cam1.translate(0,-rPercesion,0);
			break;
		case 'I': // Zoom +ve == Z
			cam1.translate(0,0,rPercesion);
			break;		
		case 'i': // Zoom -ve
			cam1.translate(0,0,-rPercesion);
			break;
		case 'L': // Roll Camerta +ve
			cam1.rotate(rPercesion,'L');
			break;
		case 'l': // Roll Camerta -ve
			cam1.rotate(-rPercesion,'L');
			break;
		case 'T': // Tilt Camerta +ve
			cam1.rotate(rPercesion,'T');
			break;
		case 't': // Tilt Camerta -ve
			cam1.rotate(-rPercesion,'T');
			break;	
		case 'A': // Pan Camerta +ve
			cam1.rotate(rPercesion,'A');
			break;
		case 'a': // PAn Camerta -ve
			cam1.rotate(-rPercesion,'A');
			break;
	  // Model Controls 
		
		case 'N': // Translate Depth +
			m.translate(0,0,tPercesion);
			break;
		case 'n': // Translate Depth -
			m.translate(0,0,-tPercesion);
			break;
		case 'Y': // Yaw - Rotate Left Model 
			m.rotate(0,rPercesion,0);
			break;
		case 'y': // -ve Yaw - Rotate Right Model 
			m.rotate(0,-rPercesion,0);
			//cout << "Yaw\n";
			break;
		case 'P': // Pitch - Rotate Down Model 
			m.rotate(rPercesion,0,0);
			break;
		case 'p': // -ve Pitch - Rotate up Model 
			m.rotate(-rPercesion,0,0);
			break;
		case 'R': // Roll - Rotate Around Z Axis   
			m.rotate(0,0,rPercesion);
			break;
		case 'r': // -ve Roll - Rotate Around Z Axis   
			m.rotate(0,0,-rPercesion);
			break;
		case 'x': // Rest Rotation Axis 
			m.resetRotate();
			m.resetTranslate();
			m.resetScale();
			m.setCenter();
			cam1.setCamera(	'v',0, 0, 0, 0, 0,-1, 0, 1, 0);
			cam1.setWindow(-1 ,1 ,-1, 1 ,1 ,100);
			cout << "Reset Scene\n";
			//m.drawModel();
			break;
		case '+': // Scale Big
			m.scale(1+zPercesion);
			break;
		case '-': // Scale Small
			m.scale(1-zPercesion);
			break;
	// Required Controls
		case 'w': // Write model into output.obj
			m.dumpModel("output.obj");
			break;
		case 'v': // Orthographic View
			cam1.switchVt('v');
			break;
		case 'V': // Prespective View 
			cam1.switchVt('V');
			break;
		case 'f': // Orthographic View
			isFog = false;
			break;
		case 'F': // Prespective View 
			isFog = true;
			break;
	// Other Controls
		case '?': // Display Model and Camera information
			
			m.displayInformation();
			cam1.displayInformation(); 

			break;
		default:
			cout << "Key Pressed: " << key << "\n";
			break;
	}
	//m.doNothing();
	glutPostRedisplay();
	//drawScene();
}


void arrawKeyInput(int key, int x, int y)
{
	/*
	float rPercesion = 10;   // Rotation Percesion
	float tPercesion = 0.1; // Translation Percesion
	float zPercesion = 0.1; // Zoom Percesion
	*/
	//glLoadIdentity();	
	//glMatrixMode(cam1.getVt());
	//m.doNothing();	
	switch(key)
	{
		case GLUT_KEY_UP:
			m.translate(0,tPercesion,0);
			break;
		case GLUT_KEY_DOWN:
			m.translate(0,-tPercesion,0);
			break;
		case GLUT_KEY_LEFT:
			m.translate(-tPercesion,0,0);
			break;
		case GLUT_KEY_RIGHT:
			m.translate(tPercesion,0,0);
			break;
		default:
			cout << "Special Key Pressed: " << key << "\n";
			break;
	}
	//m.doNothing();
	glutPostRedisplay();
}

