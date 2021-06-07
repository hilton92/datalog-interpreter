/*
File: Database.cpp
Author: Benjamin Hilton
Date: March 2016*/


#include "Database.h"



Database::Database()
{
}
Database::~Database()
{
}
void Database::addSchemeVector(vector<Predicate> theSchemes) {
	Schemes = theSchemes;
}
void Database::addFactVector(vector<Predicate> theFacts) {
	Facts = theFacts;
}
void Database::addRuleVector(vector<Rule> theRules) {
	Rules = theRules;
}
void Database::addQueryVector(vector<Predicate> theQueries) {
	Queries = theQueries;
}
void Database::Process_program(string outputFile) {
	fout.open(outputFile);//open fout object
	Process_all_schemes(fout);//process all schemes
	fout << "Fact Evaluation\n\n";
	Process_all_facts(fout);//process all facts
	Process_all_rules(fout); //process all rules
	Process_all_queries(fout);//Process Queries

}
void Database::Process_all_schemes(ofstream& fout) {
	for (int i = 0; i < Schemes.size(); i++){
		//for all of the Schemes, create a new relation and add it to my map, the identifier is the key 
		Relation new_relation;
		new_relation.addName(Schemes[i].getID());
		new_relation.addScheme(Schemes[i].getScheme());
		my_map[Schemes[i].getID()] = new_relation;
	}
	Print_schemes(fout);
}
void Database::Process_all_facts(ofstream& fout) {
	for (int i = 0; i < Facts.size(); i++) {
		//for all of the Facts, make a tuple object and add it to the corresponding relation
		my_map[Facts[i].getID()].addTuple(Facts[i].getList());
	}
	Print_facts(fout);

}
void Database::Process_all_queries(ofstream& fout) {
	//For each query  do a select operation (or multiple), a project operation, and a 
	//rename operation to whatever the name is in the query
	
	fout << "Query Evaluation";
	string ID;
	vector<string> thequerylist;
	string attribute;
	for (int i = 0; i < Queries.size(); i++) {//iterate through the queries
		Relation my_relation;
		Relation new_relation;
		ID = Queries[i].getID();
		thequerylist = Queries[i].getList();
		my_relation = my_map[ID];//get the corresponding relation
		//for each of these queries, do a select
		//parameters - the current query
		new_relation = my_relation.select(thequerylist);
		fout << "\n\n";
		Queries[i].toString(fout);
		fout << "?";
		if (new_relation.getNo_ofTuples() > 0) {
			fout << " Yes(" << new_relation.getNo_ofTuples() << ")";
			fout << "\nselect";
			new_relation.printRelation(fout);
			//for each of these queries, get a relation back
			my_relation = new_relation.project(thequerylist);
			fout << "\nproject";
			my_relation.printRelation(fout);
			new_relation = my_relation.rename(thequerylist);
			fout << "\nrename";
			new_relation.printRelation(fout);
		}
		else {
			fout << " No";
		}
	}
	fout << "\n\n";
}
vector<set<int>> Database::optimizeRules(ofstream& fout) {
	//create map
	map <int, node> mynodemap;
	map <int, node> DependencyGraph;
	vector<int> SCCVec;
	vector<set<int>> SCCVec2;

	//populate map with dependency graph
	populateMapWithDependency(mynodemap);
	DependencyGraph = mynodemap;
	fout << "Dependency Graph\n";
	printMap(mynodemap, fout);
	populateMapWithReverseDependency(mynodemap);
	fout << "\nReverse Graph\n";
	printMap(mynodemap, fout);
	//switch map to reverse dependency graph
	vector<int> PostOrder;
	PostOrder = getPostOrderNumbers(mynodemap);
	fout << "\nPostorder Numbers\n";
	printPostOrder(PostOrder, fout);
	fout << "\nSCC Search Order\n";
	SCCVec = printSCCOrder(PostOrder, fout);
	SCCVec2 = getSCCs(DependencyGraph, SCCVec);
	return SCCVec2;
}

vector<set<int>> Database::getSCCs(map<int, node> mynodemap, vector<int> SSCVec) {
	set<int> visitedNodes;
	set<int> newNodes;
	vector<int> PostOrder;
	vector<set<int>> SSVec2;
	for (int i = 0; i < Rules.size(); i++) {
		dfs(SSCVec[i], visitedNodes, mynodemap, PostOrder, newNodes);
		if (!newNodes.empty()) {
			SSVec2.push_back(newNodes);
		}
		newNodes.clear();
	}
	return SSVec2;
}

vector<int> Database::printSCCOrder(vector<int> PostOrder, ofstream& fout) {
	vector<int> ReturnVec;
	for (int i = Rules.size() - 1; i >= 0; i--) {
		int pos = find(PostOrder.begin(), PostOrder.end(), i+1) - PostOrder.begin();
		ReturnVec.push_back(pos);
	}
	for (int f = 0; f < ReturnVec.size(); f++) {
		fout << "  R" << ReturnVec[f] << endl;
	}
	return ReturnVec;
}

void Database::printPostOrder(vector<int> PostOrder, ofstream& fout) {
	int Size = Rules.size();
	for (int i = 0; i < Size; i++) {
		fout << "  R" << i << ": " << PostOrder[i] << endl;
	}
}

void Database::populateMapWithReverseDependency(map<int, node>& mynodemap) {
	map<int, node> TempMap;
	for (int c = 0; c < mynodemap.size(); c++) {
		TempMap[c];
	}
	for (int i = 0; i < mynodemap.size(); i++) {
		for (int j = 0; j < mynodemap[i].VectorofEdges.size(); j++) {
			if (find(TempMap[mynodemap[i].VectorofEdges[j]].VectorofEdges.begin(), TempMap[mynodemap[i].VectorofEdges[j]].VectorofEdges.end(), i) != TempMap[mynodemap[i].VectorofEdges[j]].VectorofEdges.end()){
					
				}
				else{
					TempMap[mynodemap[i].VectorofEdges[j]].VectorofEdges.push_back(i);
				}
			
		}
	}
	mynodemap = TempMap;
}

vector<int> Database::getPostOrderNumbers(map<int, node> mynodemap) {
	set<int> visitedNodes;
	set<int> newNodes;
	vector<int> PostOrder;
	for (int i = 0; i < Rules.size(); i++) {
		dfs(i, visitedNodes, mynodemap, PostOrder, newNodes);
	}
	vector<int> copyVector;
	for (int g = 0; g < Rules.size(); g++) {
		for (int h = 0; h < Rules.size(); h++) {
			if (PostOrder[h] == g) {
				copyVector.push_back(h + 1);
			}
		}
	}
	PostOrder = copyVector;
	return PostOrder;
}

void Database::dfs(int currentnode, set<int>& visitedNodes, map<int, node> mynodemap, vector<int>& PostOrder, set<int>& newNodes) {

	if (visitedNodes.find(currentnode) != visitedNodes.end()){
		//the node has already been visited
		return;
	}
	else {
		visitedNodes.insert(currentnode);
		newNodes.insert(currentnode);
		for (int i = 0; i < mynodemap[currentnode].VectorofEdges.size(); i++) {
			dfs(mynodemap[currentnode].VectorofEdges[i], visitedNodes, mynodemap, PostOrder, newNodes);

		}
		PostOrder.push_back(currentnode);
	}


	
}

void Database::printMap(map <int, node> mynodemap, ofstream& fout) {
	for (int i = 0; i < mynodemap.size(); i++) {
		fout << "  R" << i << ":";
		for (int j = 0; j < mynodemap[i].VectorofEdges.size(); j++) {
			fout << " R" << mynodemap[i].VectorofEdges[j];
			if (j != mynodemap[i].VectorofEdges.size() - 1){
				//fout << " ";
			}
		}
		fout << endl;
	}
}

void Database::populateMapWithDependency(map<int,node>& myMap) {
	map<int, string> tempMap;
	for (int i = 0; i < Rules.size(); i++) {
		tempMap[i] = Rules[i].getLeftSide().getID();
	}
	for (int i = 0; i < Rules.size(); i++) {
		//for each Rule, iterate through the right side
		//check each rule 
		node newNode;
		for (int j = 0; j < Rules[i].getrightSideSize(); j++) {
			myMap[i];
			for (int k = 0; k < Rules.size(); k++) {
				if (Rules[i].getRightSideID(j) == tempMap[k]) {
					//check if element exists
					if (find(myMap[i].VectorofEdges.begin(), myMap[i].VectorofEdges.end(), k) != myMap[i].VectorofEdges.end()){
						
					}
					else{
						myMap[i].VectorofEdges.push_back(k);
					}
					sort(myMap[i].VectorofEdges.begin(), myMap[i].VectorofEdges.end());
				}
			}
		}
	}
}

void Database::Process_all_rules(ofstream& fout) {
	fout << "Rule Evaluation\n\n";
	vector<set<int>> SCCVec;
	SCCVec = optimizeRules(fout);
	
	for (int z = 0; z < SCCVec.size(); z++) {
		fout << "\nSCC:";
		vector<Rule> Rules2;
		set<int> RuleSet = SCCVec[z];
		set<int>::iterator it;
		for (it = RuleSet.begin(); it != RuleSet.end(); it++) {
			int index = *it;
			fout << " R" << index;
			Rules2.push_back(Rules[index]);
		}
		fout << endl;
		int previous_num = -1;
		int current_num = getTotalTuples();
		int counter = 0;
		while ((current_num - previous_num) != 0) {
			whileLoopRules(Rules2, fout);
			counter++;
			previous_num = current_num;
			if (Rules2.size() != 1) {
				current_num = getTotalTuples();
			}
			else{
				for (int l = 0; l < Rules2[0].getrightSideSize(); l++) {
					if (Rules2[0].getLeftSide().getID() == Rules2[0].getRightSideID(l)) {
						current_num = getTotalTuples();
					}
				}
			}
		}
	}
	fout << "\nRule Evaluation Complete\n\n";
	Print_rules(fout);
}
void Database::whileLoopRules(vector<Rule>& Rules2, ofstream& fout){
	for (int i = 0; i < Rules2.size(); i++) {//iterate through all the rules
				//make a set of all the relations that are on the right side
				vector<Relation> VecofRelations;
				for (int j = 0; j < Rules2[i].getrightSideSize(); j++) {
					//iterate through all of the predicates on the right side
					Predicate my_pred = Rules2[i].getPredicate(j);
					vector<string> thequerylist;
					string ID;
					//select, project, rename
					Relation my_relation;
					Relation new_relation;
					ID = my_pred.getID();
					thequerylist = my_pred.getList();
					my_relation = my_map[ID];//get the corresponding relation
											 //for each of these queries, do a select
											 //parameters - the current query
					new_relation = my_relation.select(thequerylist);
					if (new_relation.getNo_ofTuples() > 0) {
						my_relation = new_relation.project(thequerylist);
						new_relation = my_relation.rename(thequerylist);
					}
					VecofRelations.push_back(new_relation);
				}
				//now the vector is full of relations
				Relation outputRelation;
				if (VecofRelations.size() > 1) {
					// perform join
					//set outputRelation to the result of the join
					outputRelation = massJoin(VecofRelations);
				}
				else {
					outputRelation = VecofRelations[0];
				}
				Predicate newPredicate = Rules2[i].getLeftSide();
				string name = newPredicate.getID();
				vector<string> RuleLeftVec = newPredicate.getList();
				Relation new_relation;
				new_relation = outputRelation.project2(RuleLeftVec);
				vector<string> schemeVect = my_map[name].getScheme().getScheme();
				outputRelation = new_relation.rename(schemeVect);
				Rules2[i].toString(fout);
				new_relation = my_map[name].Union(outputRelation.getTuples());
				new_relation.printRelation(fout);
				fout << endl;
			}
}







Relation Database::massJoin(vector<Relation> myRelations) {
	//takes the vector of Predicates and joins them all
	Relation exportRelation = myRelations[0];
	Relation exportRelation2;
	for (int i = 1; i < myRelations.size(); i++) {
		exportRelation2 = exportRelation.join(myRelations[i]);
		exportRelation = exportRelation2;
	}
	return exportRelation;
	//this will return the one relation with all the joined tuples
	

}
void Database::Print_schemes(ofstream& fout) {
	fout << "Scheme Evaluation\n\n";
}
void Database::Print_facts(ofstream& fout) {
	Scheme my_scheme;
	set<Tuple> my_tuples;
	vector<string> schemeAttributes;
	typedef map<string, Relation>::const_iterator MapIterator;
	for (MapIterator iter = my_map.begin(); iter != my_map.end(); iter++)
	{
		fout << iter->first << endl;
		Relation my_relation = iter->second;
		my_scheme = my_relation.getScheme();
		schemeAttributes = my_scheme.getScheme();
		my_tuples = my_relation.getTuples();
		for (set<Tuple>::iterator i = my_tuples.begin(); i != my_tuples.end(); i++) {
			Tuple element = *i;
			fout << " ";
			for (int j = 0; j < element.size(); j++) {
				fout << " " << schemeAttributes[j] << "=" << element[j];
			}
			fout << "\n";
		}
		fout << endl;
	}
}
int Database::getTotalTuples() {
	//add up all the tuples in all the relations in my_map
	typedef map<string, Relation>::iterator it_type;
	int sum = 0;
	for (it_type iterator = my_map.begin(); iterator != my_map.end(); iterator++) {
		Relation value;
		value = iterator->second;
		sum += value.getNo_ofTuples();
	}
	return sum;
}
void Database::Print_rules(ofstream& fout) {
	Print_facts(fout);
}
