/*
File: Predicate.cpp
Author: Benjamin Hilton
Date: Feb 2016
*/

#include "Predicate.h"

Predicate::Predicate()
{
}


Predicate::~Predicate()
{
}

Scheme Predicate::getScheme() {
	Scheme SCHEME_;
	vector<string> returnString;
	for (int i = 0; i < parameterList.size(); i++) {
		returnString.push_back(parameterList[i].getValue());
	}
	SCHEME_.addScheme(returnString);
	return SCHEME_;
}

string Predicate::getID() {
	return ID.getValue();
}
Tuple Predicate::getList() {
	Tuple returnString;
	for (int i = 0; i < parameterList.size(); i++) {
		returnString.push_back(parameterList[i].getValue());
	}
	return returnString;
}

void Predicate::addString(Parameter Id) {
	ID = Id;
}
void Predicate::addParameter(Parameter paralist) {
	parameterList.push_back(paralist);
}
void Predicate::erase() {
	parameterList.clear();
	ID.clear();
}
void Predicate::toString(ofstream& fout) {
	fout << ID.getValue() << "(";
	for (int i = 0; i < parameterList.size(); i++) {
		if (i > 0) {
			fout << ",";
		}
		fout << parameterList[i].getValue();

	}
	fout << ")";
	



}