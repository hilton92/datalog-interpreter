/*
File: Lexer.h
Author: Benjamin Hilton
Date: Jan 2016
*/


#ifndef LEXER_H_
#define LEXER_H_

#include <string>
#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include "Parser.h"
#include "Token.h"
using namespace std;

class Lexer
{
protected:
	string outputFile = "text2.txt";
	string inputFile = "text1.txt";
	char readChar();
	ifstream fin;
	ofstream fout;
	int current_line_number;
	vector<Token> my_Tokens;

public:
	Lexer();
	~Lexer();
	void Parse();
	void print();
	vector<Token> getVec();
	char parseID(char input);
	char parseString(char input);
	char parseColon(char input);
	void setIO(string in, string out);

};
#endif
