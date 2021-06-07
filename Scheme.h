/*
File: Scheme.h
Author: Benjamin Hilton
Date: March 2016*/
#include <vector>
#include <string>
using namespace std;
#ifndef SCHEME_H_
#define SCHEME_H_

class Scheme
{
public:
	Scheme();
	~Scheme();
	void addScheme(vector<string> attributes);
	vector<string> getScheme();
private:
	vector<string> my_attributes;
};

#endif
