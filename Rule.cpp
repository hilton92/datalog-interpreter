/*
File: Rule.cpp
Author: Benjamin Hilton
Date: Feb 2016
*/

#include "Rule.h"

Rule::Rule()
{
}

Rule::~Rule()
{
}
void Rule::clear() {
	rightSide.clear();
	leftSide.erase();
}

string Rule::getRightSideID(int index) {
	return rightSide[index].getID();
}

Predicate Rule::getLeftSide() {
	return leftSide;
}
int Rule::getrightSideSize() {
	return rightSide.size();
}
void Rule::addRuleleftSide(Predicate pred) {
	leftSide = pred;
}
void Rule::addRulerightSide(Predicate pred) {
	rightSide.push_back(pred);
}
Predicate Rule::getPredicate(int index) {
	return rightSide[index];
}

void Rule::toString(ofstream& fout) {
	leftSide.toString(fout);
	fout << " :- ";
	for (int i = 0; i < rightSide.size(); i++) {
		if (i > 0) {
			fout << ",";
		}
		rightSide[i].toString(fout);
	}
}