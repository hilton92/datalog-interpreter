/*
File: Relation.h
Author: Benjamin Hilton
Date: March 2016*/
#include "Tuple.h"
#include <string>
#include "Scheme.h"
#include <set>
#include <map>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>
using namespace std;
#ifndef RELATION_H_
#define RELATION_H_
class Relation
{
public:
	Relation();
	~Relation();
	Relation select(vector<string> inputVec);
	Relation project(vector<string> inputVec);
	Relation project2(vector<string>);
	Relation rename(vector<string> inputVec);
	Relation Union(set<Tuple>);
	void addName(string new_name);
	void addScheme(Scheme new_Scheme);
	void addTuple(Tuple new_Tuple);
	void addTuples(set<Tuple>);
	vector<string> getJoinScheme(vector<string>, vector<int>&, vector<int>&);
	void joinPT2(bool&, int &counter, Tuple &new_Tuple, Tuple element, Tuple element2, vector<int> indexVec, vector<int> indexVec2);
	Relation join(Relation);
	string getName();
	Scheme getScheme();
	int getSchemeSize();
	int getNo_ofTuples();
	set<Tuple> getTuples();
	void printRelation(ofstream & fout);
private:

	string name;
 	Scheme myScheme;
	set<Tuple> my_tuples;
	
};
#endif
