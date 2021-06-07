/*
File: Token.h
Author: Benjamin Hilton
Date: Feb 2016
*/
#ifndef TOKEN_H_
#define TOKEN_H_
#include <string>
using namespace std;

enum token_type { OTHER, SPACE, NEWLINE, QUOTE, COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, ID, STRING, EofF, SCHEMES, FACTS, RULES, QUERIES, HASHTAG, ERROR };
struct Token {
	int line_number;
	token_type type;
	string token_string;
	Token(token_type my_type, int line, string tokenstr) {
		type = my_type;
		line_number = line;
		token_string = tokenstr;
	}
	Token() {};
	~Token() {};
};
#endif