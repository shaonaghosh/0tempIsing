#ifndef UTILITY_H
#define UTILITY_H

#include<list>
#include<vector>
#include<string>

using namespace std;

//Class for graph
class GraphOperations{

	//Member funcitons
public:
	//Empty Constructor
	GraphOperations(int n, int *Adj, double * f_j);

	//Flatten the same labelled nodes
	void FlattenSameLabels();

private:
       
protected:
	//Member functions

	//member Variables
protected:
    std::list<vector<int>> collapsiblelist;
	std::list<vector<int>> parentsofcollaplist;
	std::list<vector<int>> neighofcollaplist;
	int novertices;
	int *m_Adj;
	double *m_fj;
};

#endif