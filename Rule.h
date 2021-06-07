/*
File: Rule.h
Author: Benjamin Hilton
Date: Feb 2016
*/



#ifndef RULE_H_
#define RULE_H_
#include <vector>
#include <string>
#include <fstream>
#include "Predicate.h"
using namespace std;
class Rule
{
public:
	Rule();
	~Rule();
	void addRuleleftSide(Predicate pred);
	void addRulerightSide(Predicate pred);
	void toString(ofstream& fout);
	void clear();
	Predicate getPredicate(int);
	int getrightSideSize();
	Predicate getLeftSide();
	string getRightSideID(int);
private:
	Predicate leftSide;
	vector<Predicate> rightSide;
};

#endif