/*
File: Parser.cpp
Author: Benjamin Hilton
Date: Feb 2016
*/

#include "Parser.h"

Parser::Parser()
{
}

Parser::~Parser()
{
}
vector<Predicate> Parser::getSchemes() {
	return prog.getSchemes();
}
vector<Predicate> Parser::getFacts() {
	return prog.getFacts();
}
vector<Rule> Parser::getRules() {
	return prog.getRules();
}
vector<Predicate> Parser::getQueries() {
	return prog.getQueries();
}

//sets the output string
void Parser::setOutputFile(string output) {
	outputfile = output;
}
//can return if there was an error in the parser
bool Parser::wasError() {
	return parseError;
}
//inputs the Token vector from the scanner
void Parser::setTokenList(vector<Token> list) {
	TokenList = list;
}
//goes to the next token
void Parser::nextToken() {
	if (current_place < TokenList.size()) {
		currentToken = TokenList[current_place];
	}
	current_place++;
}


void Parser::datalogProg() {
	string Errorstring = "";
	nextToken();
	try {
		M(SCHEMES); M(COLON); scheme(); schemeList();
		M(FACTS); M(COLON); factList();
		M(RULES); M(COLON); ruleList();
		M(QUERIES); M(COLON); query(); queryList();
		M(EofF);

	}
	catch (invalid_argument& e){
		Errorstring = e.what();
		parseError = true;
		prog.toString(outputfile, parseError, Errorstring);
	}
	
}
void Parser::schemeList() {
	if (currentToken.type == ID) {
		scheme();
		schemeList();
	}
	else {
		//epsilon
	}
}
void Parser::factList() {
	if (currentToken.type == ID) {
		fact();
		factList();
	}
	else {
		//epsilon
	}
}
void Parser::ruleList() {
	if (currentToken.type == ID) {
		rule();
		ruleList();
	}
	else {
		//epsilon
	}
}
void Parser::queryList() {
	if (currentToken.type == ID) {
		query();
		queryList();
	}
	else {
		//epsilon
	}
}
void Parser::scheme() {
	predicate();
	prog.addScheme(pred);
	pred.erase();
	parm.clear();
}
void Parser::fact() {
	predicate(); M(PERIOD);
	prog.addFact(pred);
	pred.erase();
	parm.clear();
		
}
void Parser::rule() {
	predicate(); my_rule.addRuleleftSide(pred);
	pred.erase(); parm.clear(); M(COLON_DASH);
	predicate(); my_rule.addRulerightSide(pred);
	pred.erase(); parm.clear(); predicateList();
	M(PERIOD); prog.addRule(my_rule); my_rule.clear();
	
}
void Parser::query() {
	predicate(); M(Q_MARK);
	prog.addQuery(pred);
	pred.erase();
	parm.clear();
}
void Parser::predicateList() {
	if (currentToken.type == COMMA) {
		M(COMMA); predicate(); my_rule.addRulerightSide(pred); pred.erase(); parm.clear();  predicateList();
	}
	else {
		//epsilon
	}

}
void Parser::predicate() {
	M(ID); pred.addString(parm); parm.clear();  M(LEFT_PAREN); parameter(); pred.addParameter(parm); parm.clear();  parameterList(); M(RIGHT_PAREN);
}
void Parser::parameterList() {
	if (currentToken.type == COMMA) {
		M(COMMA); parameter(); pred.addParameter(parm); parm.clear();  parameterList();
	}
	else {
		//epsilon
	}
}
void Parser::parameter() {
	token_type currentType = currentToken.type;
	if (currentType == STRING) {
		M(STRING);
	}
	else if (currentType == ID) {
		M(ID);
	}
	else {
		Match(ERROR);
	}
}
void Parser::M(token_type my_enum) {
	switch (my_enum) {
	case COMMA:
		Match(COMMA);
		break;
	case SCHEMES:
		Match(SCHEMES);
		break;
	case FACTS:
		Match(FACTS);
		break;
	case RULES:
		Match(RULES);
		break;
	case QUERIES:
		Match(QUERIES);
		break;
	case PERIOD:
		Match(PERIOD);
		break;
	case COLON:
		Match(COLON);
		break;
	case COLON_DASH:
		Match(COLON_DASH);
		break;
	case Q_MARK:
		Match(Q_MARK);
		break;
	case ID:
		Match(ID);
		break;
	case LEFT_PAREN:
		Match(LEFT_PAREN);
		break;
	case RIGHT_PAREN:
		Match(RIGHT_PAREN);
		break;
	case STRING:
		Match(STRING);
		break;
	case EofF:
		Match(EofF);
		break;
	case ERROR:
		Match(ERROR);
	default:
		throw invalid_argument("parse error");
		break;
	}
		nextToken();
}
void Parser::Match(token_type my_enum){
	string error;
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
	if (my_enum != STRING && my_enum != ID){
		if (currentToken.type != my_enum) {
			error = "(" + printList[currentToken.type] + ",\"" + currentToken.token_string + "\"," + to_string(currentToken.line_number) + ")";
			throw invalid_argument(error);//error
		}
	}
	if (my_enum == STRING){
		if (currentToken.type != STRING) {
			error = "(" + printList[currentToken.type] + ",\"" + currentToken.token_string + "\"," + to_string(currentToken.line_number) + ")";
			throw invalid_argument(error);//error
		}
		else {
			//add the string to the parameter object
			parm.addID(currentToken.token_string);
			parm.addline(currentToken.line_number);
			prog.addDomain(currentToken.token_string);
		}
	}
	if (my_enum == ID){
		if (currentToken.type != ID) {
			error = "(" + printList[currentToken.type] + ",\"" + currentToken.token_string + "\"," + to_string(currentToken.line_number) + ")";
			throw invalid_argument(error);//error
		}
		else {
			//add the ID to the parameter object
			parm.addID(currentToken.token_string);
			parm.addline(currentToken.line_number);
		}
	}
	
	
	
}
