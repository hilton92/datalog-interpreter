/*
File: Lexer.cpp
Author: Benjamin Hilton
Date: Jan 2016
*/

#include "Lexer.h"


Lexer::Lexer()
{
	current_line_number = 1;
}

Lexer::~Lexer()
{
}

vector<Token> Lexer::getVec() {
	return my_Tokens;
}


void Lexer::Parse() {
	//this is where the actual parsing will occur
	//a function readChar() will be called
	//when each token is read, a new token object will be created and pushed into the vector
	char input;
	input = readChar();
	while (!fin.eof()) {
		if (input == ' ') {
			input = readChar();
		}
		// begin in START state
		switch (input) {
		case ',':
		{
			Token comma(COMMA, current_line_number, ",");
			my_Tokens.push_back(comma);
			input = ' ';
			break;

		}
		case '.':
		{
			Token period(PERIOD, current_line_number, ".");
			my_Tokens.push_back(period);
			input = ' ';
			break;
		}
		case '?':
		{
			Token qmark(Q_MARK, current_line_number, "?");
			my_Tokens.push_back(qmark);
			input = ' ';
			break;
		}
		case '(':
		{
			Token leftp(LEFT_PAREN, current_line_number, "(");
			my_Tokens.push_back(leftp);
			input = ' ';
			break;
		}
		case ')':
		{
			Token rightp(RIGHT_PAREN, current_line_number, ")");
			my_Tokens.push_back(rightp);
			input = ' ';
			break;
		}
		case ':':
		{
			input = parseColon(input);
			break;
		}
		case '\'':
		{
			input = parseString(input);
			break;
		}
		case '\n':
			input = ' ';
			current_line_number++;
			break;
		case '\t':
			input = ' ';
			break;
		case '\r':
			input = ' ';
			break;
		case '\f':
			input = ' ';
			break;
		case '\v':
			input = ' ';
			break;
		case ' ':
			input = ' ';
			break;
		case '#':
			//comment line
			current_line_number++;
			while (1) {
				input = readChar();
				if (input == '\n' || fin.eof()) {
					input = ' ';
					break;
				}
			}
			break;
		default:
			//for IDs and keywords;
			input = parseID(input);
			break;
		}

	}
	Token EndofF(EofF, current_line_number, "");
	my_Tokens.push_back(EndofF);

}

char Lexer::parseString(char input) {

	string Strquote = "'";
	input = readChar();
	Strquote += input;
	while (input != '\'') {
		input = readChar();
		Strquote += input;
		if (input == '\n' || fin.eof()) {
			Token Error(ERROR, current_line_number, "ERROR");
			my_Tokens.push_back(Error);
			return input;
		}
	}
	Token stringg(STRING, current_line_number, Strquote);
	my_Tokens.push_back(stringg);
	input = ' ';
	return input;
}

char Lexer::parseColon(char input) {
	char next_char = readChar();
	if (next_char == '-') {
		Token colondash(COLON_DASH, current_line_number, ":-");
		my_Tokens.push_back(colondash);
		input = ' ';
	}
	//Colon-dash
	else {
		Token colon(COLON, current_line_number, ":");
		my_Tokens.push_back(colon);
		input = next_char;
	}
	return input;
}


char Lexer::parseID(char input) {
	//for IDs and keywords;
	if (fin.eof()) {
		Token EndofF(EofF, current_line_number, "");
		my_Tokens.push_back(EndofF);
		return input;
	}
	if (!isalpha(input)) {
		Token Error(ERROR, current_line_number, "ERROR");
		my_Tokens.push_back(Error);
		input = readChar();
		return input;
	}
	string str = "";
	str += input;
	input = readChar();
	while (isalnum(input)) {
		str += input;
		input = readChar();
	}
	if (str == "Facts") {
		Token facts(FACTS, current_line_number, "Facts");
		my_Tokens.push_back(facts);
		return input;
	}
	else if (str == "Schemes") {
		Token schemes(SCHEMES, current_line_number, "Schemes");
		my_Tokens.push_back(schemes);
		return input;
	}
	else if (str == "Rules") {
		Token rules(RULES, current_line_number, "Rules");
		my_Tokens.push_back(rules);
		return input;
	}
	else if (str == "Queries") {
		Token queries(QUERIES, current_line_number, "Queries");
		my_Tokens.push_back(queries);
		return input;
	}
	else {
		Token id(ID, current_line_number, str);
		my_Tokens.push_back(id);
		return input;
	}
}



char Lexer::readChar() {
	char c = ' ';
	fin.get(c);
	return c;
}

void Lexer::print() {
	map <token_type, string> printList;
	printList[COMMA] = "COMMA";
	printList[PERIOD] = "PERIOD";
	printList[Q_MARK] = "Q_MARK";
	printList[LEFT_PAREN] = "LEFT_PAREN";
	printList[RIGHT_PAREN] = "RIGHT_PAREN";
	printList[COLON] = "COLON";
	printList[ID] = "ID";
	printList[COLON_DASH] = "COLON_DASH";
	printList[RULES] = "RULES";
	printList[QUERIES] = "QUERIES";
	printList[FACTS] = "FACTS";
	printList[SCHEMES] = "SCHEMES";
	printList[STRING] = "STRING";
	printList[EofF] = "EOF";
	fout.open(outputFile);
	if (fout.is_open()) {
		for (int i = 0; i < my_Tokens.size(); i++) {
			if (my_Tokens[i].type == ERROR) {
				fout << "Input Error on line " << my_Tokens[i].line_number << endl;
				return;
			}
			fout << "(" << printList[my_Tokens[i].type] << ",\"" << my_Tokens[i].token_string << "\"," << my_Tokens[i].line_number << ")" << endl;
		}
		fout << "Total Tokens = " << my_Tokens.size();
		return;
	}
	else {
		cout << "Error";
	}
	return;
}

void Lexer::setIO(string in, string out) {
	inputFile = in;
	outputFile = out;
	fin.open(inputFile);
	return;
}
