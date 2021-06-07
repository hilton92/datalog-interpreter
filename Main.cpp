/*
File: Main.cpp
Author: Benjamin Hilton
Date: Feb 2016
*/

#include <iostream>
#include "Lexer.h" 
#include "Parser.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include "Database.h"
#include <vector>

using namespace std;

//the arguments for execution
int main(int argc, char* argv[]) {
	string input = argv[1];
	string output = argv[2];
	//string input = "text1.txt";
	//string output = "text4.txt";
	Lexer my_lexer;
	Parser my_parser;
	my_parser.setOutputFile(output);
	my_lexer.setIO(input, output);
	my_lexer.Parse();
	
	//enable this line to print the output from the scanner
	//my_lexer.print();
	vector<Token> Token_List;
	Token_List = my_lexer.getVec();
	my_parser.setTokenList(Token_List);
	my_parser.datalogProg();
	if (my_parser.wasError()) {
		return 0;
	}

	//the interpreter part:
	vector<Predicate> SchemeList = my_parser.getSchemes();
	vector<Predicate> FactList = my_parser.getFacts();
	vector<Rule> RuleList = my_parser.getRules();
	vector<Predicate> QueryList = my_parser.getQueries();
	Database myDatabase;
	myDatabase.addSchemeVector(SchemeList);
	myDatabase.addFactVector(FactList);
	myDatabase.addRuleVector(RuleList);
	myDatabase.addQueryVector(QueryList);
	myDatabase.Process_program(output);
	return 0;

}
