/*
File: Parameter.cpp
Author: Benjamin Hilton
Date: Feb 2016
*/

#include "Parameter.h"

Parameter::Parameter()
{
}

Parameter::~Parameter()
{
}
//"setters"
void Parameter::addString(string Str) {
	String = Str;
}
void Parameter::addID(string id) {
	ID = id;
}

void Parameter::addline(int line) {
	_line = line;
}

void Parameter::clear() { //clear the parameter object 
	string String = "";
	string ID = "";
	int _line = -1;
}

string Parameter::getValue() { //a "getter"
	if (ID == "") {
		return String;
		cout << "string";
	}
	else {
		return ID;
		cout << "ID";
	}
}
int Parameter::getline() {
	return _line;
}