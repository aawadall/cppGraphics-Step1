#pragma once
#  include <stdio.h>
#  include <iostream>
#  include <string>
#  include <fstream>
using namespace std;
class vertix
{
private:
	float	x; // x coordinate
	float	y; // y coordinate
	float	z; // z coordinate
	float	w; // Fourth dimention 
	float	coord[4]; // Coordinates Array
public:
	vertix();
	vertix(float, float, float);
	vertix loadVertix(string);
	~vertix();
	float getX();
	float getY();
	float getZ();
	float getW();

	void displayVertix();
};

