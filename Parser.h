/*
File: Parser.h
Author: Benjamin hilton
Date: Feb 2016
*/


//this class will hold the recursive descent
#ifndef PARSER_H_
#define PARSER_H_
#include <vector>
#include <map>
#include <string>
#include "Token.h" //stores the struct and enums
#include <stdexcept>
#include <iostream>
#include "Parameter.h"
#include "Predicate.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include <exception>
#include <fstream>


using namespace std;
class Parser
{
public:
	Parser();
	~Parser();
	void setTokenList(vector<Token> list);
	void datalogProg();
	bool wasError();
	void setOutputFile(string output);
	vector<Predicate> getSchemes();
	vector<Predicate> getFacts();
	vector<Rule> getRules();
	vector<Predicate> getQueries();
protected:
	string outputfile = "text4.txt";
	bool parseError = false;
	Predicate pred;
	Parameter parm;
	DatalogProgram prog;
	Rule my_rule;
	//vector<string> stackVec;
	//these have to do with the vector
	vector<Token> TokenList;
	Token currentToken;
	int current_place = 0;
	//recursive functions
	void nextToken();
	void schemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	void predicateList();
	void predicate();
	void parameterList();
	void parameter();
	void M(token_type my_enum);
	void Match(token_type my_enum);
};

#endif
