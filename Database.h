/*
File: Database.h
Author: Benjamin Hilton
Date: March 2016*/
#include "Relation.h"
#include <map>
#include "DatalogProgram.h"
#include "Predicate.h"
#include <fstream>
#include <string>
using namespace std;

#ifndef DATABASE_H_
#define DATABASE_H_

class Database
{
struct node {
		vector<int> VectorofEdges;
	};

public:
	Database();
	~Database();
	void addSchemeVector(vector<Predicate>);
	void addFactVector(vector<Predicate>);
	void addRuleVector(vector<Rule>);
	void addQueryVector(vector<Predicate>);
	void Process_program(string);
	void Process_all_schemes(ofstream&);
	void Process_all_facts(ofstream&);
	void Process_all_rules(ofstream&);
	void Process_all_queries(ofstream&);
	void Print_schemes(ofstream&);
	void Print_facts(ofstream&);
	void Print_rules(ofstream&);
	Relation massJoin(vector<Relation>);
	int getTotalTuples();
private:
	void whileLoopRules(vector<Rule>&, ofstream&);
	vector<set<int>> getSCCs(map<int, node>, vector<int>);
	vector<int> printSCCOrder(vector<int>, ofstream&);
	void printPostOrder(vector<int>, ofstream&);
	void dfs(int, set<int>&, map<int, node>, vector<int>&, set<int>&);
	vector<int> getPostOrderNumbers(map<int, node> );
	void populateMapWithReverseDependency(map<int, node>&);
	void printMap(map <int, node>, ofstream&);
	vector<set<int>> optimizeRules(ofstream& fout);
	void populateMapWithDependency(map<int, node>&);
	ofstream fout;
	map<string, Relation> my_map;
	vector<Predicate> Schemes;
	vector<Predicate> Facts;
	vector<Rule> Rules;
	vector<Predicate> Queries;
	map<string, Relation> Resultmap;
	
};
#endif

