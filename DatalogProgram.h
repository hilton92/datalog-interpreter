/*
File: DatalogProgram.h
Author: Benjamin Hilton
Data: Feb 2016
*/

#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_
#include <string>
#include <vector>
#include <fstream>
#include "Token.h"
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include <algorithm>

using namespace std;

class DatalogProgram //this class holds vectors, of the program items
{
public:
	DatalogProgram();
	~DatalogProgram();
	void addScheme(Predicate pred);
	void addFact(Predicate pred);
	void addRule(Rule my_rule);
	void addQuery(Predicate pred);
	void toString(string outputFile, bool wasError, string Errorstring);
	void printDomains(ofstream& fout);
	void addDomain(string my_string);
	vector<Predicate> getSchemes();
	vector<Predicate> getFacts();
	vector<Rule> getRules();
	vector<Predicate> getQueries();
protected:
	ofstream fout;
	vector<Predicate> Schemes;
	vector<Predicate> Facts;
	vector<Rule> Rules;
	vector<Predicate> Queries;
	vector<string> Domains;
};
#endif
