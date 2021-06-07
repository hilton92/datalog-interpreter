/*
File: Parameter.h
Author: Benjamin Hilton
Date: Feb 2016
*/

#ifndef PARAMETER_H_
#define PARAMETER_H_
#include <string>
#include <iostream>
using namespace std;

class Parameter
{
public:
	Parameter();
	~Parameter();
	void addString(string Str);
	void addID(string ID);
	void addline(int line);
	string getValue();
	int getline();
	void clear();
private:
	string String;
	string ID;
	int _line;
};
#endif

