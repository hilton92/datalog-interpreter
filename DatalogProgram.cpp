/*
File: DatalogProgram.cpp
Author: Benjamin Hilton
Date: Feb 2016
*/


#include "DatalogProgram.h"

DatalogProgram::DatalogProgram()
{
}


DatalogProgram::~DatalogProgram()
{
}

vector<Predicate> DatalogProgram::getSchemes() {
	return Schemes;
}
vector<Predicate> DatalogProgram::getFacts() {
	return Facts;
}
vector<Rule> DatalogProgram::getRules() {
	return Rules;
}
vector<Predicate> DatalogProgram::getQueries() {
	return Queries;
}


void DatalogProgram::addDomain(string my_string) { //adds a new string, after checking that it does not already exist in the vector
	bool foo = true;
	for (int i = 0; i < Domains.size(); i++) {
		if (my_string == Domains[i]) {
			foo = false;
		}
	}
	if (foo) {
		Domains.push_back(my_string);
	}
}
void DatalogProgram::printDomains(ofstream& fout) { //sorts, and prints the domain list
	sort(Domains.begin(), Domains.end());
	fout << "\nDomain(" << Domains.size() << "):";
	for (int i = 0; i < Domains.size(); i++) {
		fout << "\n  " << Domains[i];
	}
}
void DatalogProgram::addScheme(Predicate pred) { //adds a predicate to the scheme vector
	Schemes.push_back(pred);
}
void DatalogProgram::addFact(Predicate pred) { //adds a predicate to the Fact vector
	Facts.push_back(pred);
}
void DatalogProgram::addRule(Rule my_rule) { //adds a rule to the rule vector
	Rules.push_back(my_rule);
}
void DatalogProgram::addQuery(Predicate pred) { //adds a predicate to the query vector
	Queries.push_back(pred);
}
void DatalogProgram::toString(string outputFile, bool wasError, string Errorstring) { //toString
	fout.open(outputFile); //open the ofstream file
	if (wasError) { //if there was a parse error, print out the failure message
		fout << "Failure!\n  ";
		fout << Errorstring << "\n";
	}
	else {
		//Schemes:
		fout << "Success!\n";
		fout << "Schemes(" << Schemes.size() << "):";
		for (int i = 0; i < Schemes.size(); i++) {
			fout << "\n  ";
			Schemes[i].toString(fout);
		}
		//Facts:
		fout << "\nFacts(" << Facts.size() << "):";
		for (int i = 0; i < Facts.size(); i++) {
			fout << "\n  ";
			Facts[i].toString(fout);
		}
		//Rules:
		fout << "\nRules(" << Rules.size() << "):";
		for (int i = 0; i < Rules.size(); i++) {
			fout << "\n  ";
			Rules[i].toString(fout);
		}
		//Queries:
		fout << "\nQueries(" << Queries.size() << "):";
		for (int i = 0; i < Queries.size(); i++) {
			fout << "\n  ";
			Queries[i].toString(fout);
		}
		//Domain:
		printDomains(fout);
		fout << "\n";
	}
}
