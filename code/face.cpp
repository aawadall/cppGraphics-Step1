#include "face.h"
#include <string.h>


face::face()
{
}


face::~face()
{
}

face::face(string entry, vertix v[]){

	cout << "starting face("<< entry  <<")\n";
	vertix vx;
	char *token, *ntoken;
	const char *cline;
	char *line;
	vCount = 0;

	// TODO:
	// Parse vertixIdx string


	// 1- Test that the first entry is a character f
	if (entry[0] == 'f'){
		cline = entry.c_str();
		line = (char *)cline;

		cout << "cline:\t" << cline << "\nline:\t" << line << "\n";
		//cout << "Entry Used [" << entry << "]\n";
		token = strtok(line, " " );
		token = strtok(NULL, " " ); // token has the vertix index 
		//token = strtok_r(line, " ", &ntoken);
		//token = strtok_r(NULL, " ", &ntoken); // token has the vertix index 
		while (token){
			cout << "Token:" << token << "\n";
			
				vList[vCount++] = vertix(vx);
				vList[vCount - 1] = v[(int)strtod(token, NULL)];
				vertixIdx[vCount-1] = (int)strtod(token, NULL);
			//vertixIdx[vCount++] = (int)strtod(token, NULL);
			if (token)
				token = strtok(NULL, " ");
				//token = strtok_r(NULL, " ", &ntoken);
		}

		
		// lookup Vertix ID
		// Copy Vertix details into local vertix list 

	}
	cout << "Done Loading Face using string \n";
}
face::face(vertix v[],int c){
	vCount = 0;
	vertix t;
	for (int idx = 0; idx < c; idx++){
		vList[vCount] = vertix(v[idx]);
		vList[vCount++] = v[idx];
	}
}

vertix face::getVertix(int idx){
	return vList[idx];
}

int face::getVCount(){
	return vCount;
}

void face::displayFace(){
	//cout << "Display Face Details \n";


	glBegin(GL_POLYGON);
	//glBegin(GL_LINE_LOOP);
	//glColor3f(color[0],color[1],color[2]);
	glColor3f(0, 0, 0);
	//cout << "Color (" << color[0]<< "," << color[1] << "," << color[2] << ")\n";
	for (int idx = 0; idx < vCount; idx++){
			glVertex3f(vList[idx].getX(),
				vList[idx].getY(),
				vList[idx].getZ());
			//cout << "Drawing Vertix (" << vList[idx].getX() << "," << vList[idx].getY() << "," << vList[idx].getZ() << ")\n";
		}
	
	glEnd();
	
}
void face::setColor(float c0, float c1, float c2){
	color[0] = c0;
	color[1] = c1;
	color[2] = c2;
}
float face::getColor(int idx){
	return color[idx];
}
