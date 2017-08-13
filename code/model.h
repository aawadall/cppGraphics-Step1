#pragma once
#include "vertix.h"
#include "face.h"
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
	vertix	vArray[10000];	//Verticies Array
	int		vCount;		// Number of verticies 
	face	fArray[1000];
	int		fCount;
	int		VertixOrder[10000]; // Vertix Order Array
	int		VOCount;
public:
	model();
	model(char *); // Use this constructor to load the model from a file 
	~model();
	void pushVertix(float, float, float);
	void pushVertix(vertix);
	vertix getVertix(int);
	face getFace(int);
	int getVCount();
	int getFCount();
	void setFaceColor(int, float, float, float);
	void drawModel();
	void vOrder(string);
};

