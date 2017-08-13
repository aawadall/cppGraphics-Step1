#include "vertix.h"
#include <string>
using namespace std;

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
		//cout << "Entry Used [" << entry << "]\n";
		token = strtok(line, " ");
		token = strtok(NULL, " ");
		//token = strtok_r(line, " ",&ntoken);
		//token = strtok_r(NULL, " ", &ntoken);
		while (token){
			//cout << "Token:" << token << "\n";
			coord[idx++] = (float)strtod(token, NULL);
			if (token)
				token = strtok(NULL, " ");
				//token = strtok_r(NULL, " ",&ntoken);
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
