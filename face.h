#pragma once
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#  include <stdio.h>
#  include <iostream>
#  include <string>
#  include <fstream>
#include "vertix.h"
using namespace std;

class face
{
private :
	vertix vList[10];
	int vCount;
	int vertixIdx[10];
	float color[3];
public:
	face();
	face(vertix[],int); // Load list of verticies into face 
	face(string, vertix []); // parse a string of verticies into face using vertix array 
	~face();
	vertix getVertix(int);
	int getVCount();
	void displayFace();
	void setColor(float, float, float);
	float getColor(int);
};

