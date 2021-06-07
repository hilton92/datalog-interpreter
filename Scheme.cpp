/*
File: Scheme.cpp
Author: Benjamin Hilton
Date: March 2016*/


#include "Scheme.h"



Scheme::Scheme()
{
}


Scheme::~Scheme()
{
}

void Scheme::addScheme(vector<string> attributes) {
	my_attributes = attributes;
}

vector<string> Scheme::getScheme() {
	return my_attributes;
}