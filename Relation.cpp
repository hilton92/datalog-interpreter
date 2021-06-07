/*
File: Relation.cpp
Author: Benjamin Hilton
Date: March 2016*/



#include "Relation.h"



Relation::Relation()
{
}


Relation::~Relation()
{
}

void Relation::printRelation(ofstream & fout) {
	vector<string> myschemes = myScheme.getScheme();
		for (set<Tuple>::iterator it = my_tuples.begin(); it != my_tuples.end(); it++) {
			Tuple element = *it;
			if (element.size() > 0) {
				fout << "\n  ";
			}
			for (int i = 0; i < myschemes.size(); i++) {
				fout << myschemes[i] << "=" << element[i];
				
				if (i != element.size() - 1){
					fout << " ";
				}
			}
		}

}
int Relation::getSchemeSize() {
	vector<string> mySchemes = myScheme.getScheme();
	return mySchemes.size();
}
int Relation::getNo_ofTuples() {
	return my_tuples.size();
}
void Relation::addTuples(set<Tuple> newset) {
	my_tuples = newset;
}

void Relation::addName(string new_name) {
	name = new_name;
}
void Relation::addScheme(Scheme new_Scheme) {
	myScheme = new_Scheme;
}
void Relation::addTuple(Tuple new_Tuple) {
	my_tuples.insert(new_Tuple);
}
string Relation::getName() {
	return name;
}
Scheme Relation::getScheme() {
	return myScheme;
}
set<Tuple> Relation::getTuples() {
	return my_tuples;
}

Relation Relation::Union(set<Tuple> inputSet) {
	Relation newRelation;
	set<Tuple> originalTuples = my_tuples;
	my_tuples.insert(inputSet.begin(), inputSet.end());
	set<Tuple> result;
	set_difference(my_tuples.begin(), my_tuples.end(), originalTuples.begin(), originalTuples.end(),
		inserter(result, result.end()));
	newRelation.addTuples(result);
	newRelation.addScheme(myScheme);
	newRelation.addName(name);
	return newRelation;
}

Relation Relation::select(vector<string> inputVec) {
	Relation new_relation;
	new_relation.addScheme(myScheme);
	Tuple this_tuple;
	bool wasError = false;
	map <string, string> myVars;
	for (set<Tuple>::iterator it = my_tuples.begin(); it != my_tuples.end(); it++) {
		Tuple element = *it;
		for (int j = 0; j < inputVec.size(); j++) {
			if ((inputVec[j])[0] == '\'') {//it is a constant
				if (inputVec[j] == element[j]) {
					this_tuple.push_back(inputVec[j]);
				}
				else {
					//error
					wasError = true;
				}
			}
			else {//it is a variable
				if (myVars.find(inputVec[j]) == myVars.end())
				{
					//variable has not already appeared in the Tuple
					//create a new variable and add to the map
					myVars[inputVec[j]] = element[j];
					this_tuple.push_back(element[j]);
				}
				else {
					//the variable already appears in the map
					//check to see if the value matches
					if (element[j] == myVars[inputVec[j]]) {
						this_tuple.push_back(element[j]);
					}
					else {
						wasError = true;
					}
				}
			}
		}

//if it was a match (wasError = false)
			if (!wasError) {
				new_relation.addTuple(this_tuple);
			}
			this_tuple.clear();
			wasError = false;
			myVars.clear();
	}
	return new_relation;

}

vector<string> Relation::getJoinScheme(vector<string> Scheme2, vector<int> &indexVec, vector<int> &indexVec2){
vector<string> s = myScheme.getScheme();
for (int i = 0; i < Scheme2.size(); i++) {

		if (find(s.begin(), s.end(), Scheme2[i]) != s.end()) {
			//if the item is found already
			indexVec2.push_back(i);
			int pos = find(s.begin(), s.end(), Scheme2[i]) - s.begin();
			indexVec.push_back(pos);
		}
		else {
			s.push_back(Scheme2[i]);
		}
	}
	return s;


}

Relation Relation::join(Relation joinRelation) {
	//vector<string> Scheme1 = myScheme.getScheme();
	vector<string> Scheme2 = joinRelation.getScheme().getScheme();
	vector<string> s;
	vector<int> indexVec;
	vector<int> indexVec2;
	// combine the 2 schemes
	s = getJoinScheme(Scheme2, indexVec, indexVec2);
	//s is the new scheme
	Relation r;
	Scheme newScheme;
	newScheme.addScheme(s);
	r.addScheme(newScheme);
	Tuple newTuple;
	bool error = false;
	set<Tuple> Tuples1 = my_tuples;
	set<Tuple> Tuples2 = joinRelation.getTuples();
	//check to see if the tuples are compatible, that is, if any of the schemes are the same, the same value has to be present
	for (set<Tuple>::iterator it = Tuples1.begin(); it != Tuples1.end(); it++) {
		Tuple element = *it;
		newTuple = element;
		for (set<Tuple>::iterator it2 = Tuples2.begin(); it2 != Tuples2.end(); it2++) {
			Tuple element2 = *it2;
			int counter = 0;
			if (indexVec2.size() == 0) {
				for (int k = 0; k < element2.size(); k++) {
					newTuple.push_back(element2[k]);
				}
			}
			else {
				joinPT2(error, counter, newTuple, element, element2, indexVec, indexVec2);
			}
			if (!error) {
				r.addTuple(newTuple);
			}
			error = false;
			newTuple = element;
		} 
	}
	return r;
}


void Relation::joinPT2(bool &error, int &counter, Tuple &newTuple, Tuple element, Tuple element2, vector<int> indexVec, vector<int> indexVec2){
	for (int i = 0; i < element2.size(); i++) {
					if (find(indexVec2.begin(), indexVec2.end(), i) != indexVec2.end()) {
						//this will be all of the values in the second tuple from shared categories
						if (element[indexVec[counter]] != element2[indexVec2[counter]]) {
							//if the values here don't match, put an error
							error = true;
						}
						counter++;
					}
					else {
						//this value is not one of the repeated ones
						newTuple.push_back(element2[i]);
					}	
				}
	
}
Relation Relation::project(vector<string> inputVec) {
	Relation exportRelation;
	vector<string> schemeVector;
	Tuple replaceTuple;
	vector<string> variableVector;
	vector<string>::iterator it2;
	for (set<Tuple>::iterator it = my_tuples.begin(); it != my_tuples.end(); it++) {
		Tuple element = *it;
		for (int i = 0; i < inputVec.size(); i++) {
			if (inputVec[i][0] != '\'') {
				//it is a variable
				//check to see if it has already been used
				it2 = find(variableVector.begin(), variableVector.end(), inputVec[i]);
				if (it2 == variableVector.end()) {
					variableVector.push_back(inputVec[i]);
					schemeVector.push_back(myScheme.getScheme()[i]);
					//copy to new tuple
					replaceTuple.push_back(element[i]);
				}
			}
			else {
				//remove them from the Tuple
			}
		}
		exportRelation.addTuple(replaceTuple);
		Scheme add_Scheme;
		add_Scheme.addScheme(schemeVector);
		exportRelation.addScheme(add_Scheme);
		schemeVector.clear();
		replaceTuple.clear();
		variableVector.clear();
	}
	return exportRelation;
	
}
Relation Relation::project2(vector<string> inputVec) {
	Relation exportRelation;
	vector<string> schemeVector = myScheme.getScheme();
	Tuple replaceTuple;
	vector<string>::iterator it2;
	for (set<Tuple>::iterator it = my_tuples.begin(); it != my_tuples.end(); it++) {
		Tuple element = *it;
		for (int i = 0; i < inputVec.size(); i++) {
			
			for (int j = 0; j < schemeVector.size(); j++){
				if (inputVec[i] == schemeVector[j]) {
					//it is a column to save
					//copy to new tuple
					replaceTuple.push_back(element[j]);
				}
			}
		}
		exportRelation.addTuple(replaceTuple);
		Scheme add_Scheme;
		add_Scheme.addScheme(schemeVector);
		exportRelation.addScheme(add_Scheme);
		replaceTuple.clear();
	}
	return exportRelation;
}

Relation Relation::rename(vector<string> inputVec) {
	Relation new_relation;
	new_relation.addScheme(myScheme);
	new_relation.addTuples(my_tuples);
	Scheme myScheme;
	vector<string> newScheme;
	for (int i = 0; i < inputVec.size(); i++) {
		if (inputVec[i][0] != '\'') {
			newScheme.push_back(inputVec[i]);
		}
	}
	myScheme.addScheme(newScheme);
	new_relation.addScheme(myScheme);
	return new_relation;
}
