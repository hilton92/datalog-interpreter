/*
File: Predicate.h
Author: Benjamin Hilton
Date: Feb 2016
*/


#ifndef PREDICATE_H_
#define PREDICATE_H_
#include <vector>
#include <string>
#include "Parameter.h"
#include <fstream>
#include "Tuple.h"
#include "Scheme.h"
using namespace std;
class Predicate
{
public:
	Predicate();
	~Predicate();
	void addString(Parameter ID);
	void addParameter(Parameter paralist);
	void erase();
	void toString(ofstream& fout);
	string getID();
	Tuple getList();
	Scheme getScheme();
private:
	Parameter ID;
	vector<Parameter> parameterList;
};
#endif

