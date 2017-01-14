/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
//Misc.h
#ifndef MISCMONPRED_H
#define MISCMONPRED_H

#include<stdio.h>
//#include"igraph.h"
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<sstream>
#include<iostream>
#include<stack>
#include<fstream>
#include<limits>
#include<list>
#include<map>
#include<assert.h>
#include<algorithm>
#include<numeric>


///Typedefs
typedef std::vector< std::vector<int> > adjmattype;
typedef std::map<int,int> mapstype;
typedef std::list<std::vector<int>> adjlist;
////////////////////////////////////////////////////////////////////////////////////
// 
// Number of vertices in given graph - TODO  - have a config file
#define V 8
#define _SIMULATOR_TEST_NORMAL 0
#define _SIMULATOR_INTERTWINED_TEST 0
#define _SIMULATOR_TEST_OCTOPUS 0
#define _SIMULATOR_TEST_LOOPS 1
#define _DATASETS_TESTS 0
#define _BATCH_PREDICTION 1
#define _SIMULATOR_PREDICTION 1
//MACROS for using the STL 
#define all(c) (c).begin(),(c).end() 
//#define tr(c,i) for(typeid((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define present(c,x) ((c).find(x) != (c).end())      //for set and map
#define cpresent(c,x) (find(all(c),x) != (c).end())  //for vector and others
///////////////////////////////////////////////////////////////////////////////////

//Function declarations
//Function to geenrate new compressed graph after collapsing
int compress(int *in, int ***out, int map[], int n, mapstype& oldtonewmap);

//Function to seach for k arbitray flow paths
bool vanilladfs( adjmattype rGraph, int s, int t, int parent[], std::vector<int>& path );

//dfs that searches through flow path nodes only
void dfs(int index, std::vector<int>& nodestocontract, adjmattype Adj, std::vector<int> totalflowpath);

//dfs through undirected edges
void dfsforundirected(int index, std::vector<int>& nodestocontract, adjmattype residual, std::vector<int> path, adjmattype AdjMat);

//find the path the nodes is contained in 
std::vector<int> findPathFromNode(int indexofnode, std::list<std::vector<int>> flowpathlist);

//function to find if the nodes to find collapsed nodes in between are on the same flow path
bool isOnSamepath(int node1, int node2, std::vector<int> flowpath);

//function to find all flow path nodes to collapse
std::vector<int> dfsflowpathnodesbetween(int flownode1, int flownode2, adjmattype adjmat, adjmattype residual);

//contract the graph by removing the loops as in Provan and Ball
void contractGraphSCC(std::vector<int> parentorig, int maxflow, adjmattype &residual, int source, int target, adjmattype AdjMat, const int n, adjmattype &newAdjMat, std::list<std::vector<int>>& flowpathslist, mapstype& collapmap, std::vector<int> labnodesvect);

//function to collapse the undirected edges first, then collapse the flow path edges found by forward directed dfs
void contractGraph(std::vector<int> parentorig, int maxflow, adjmattype &residual, int source, int target, adjmattype AdjMat, const int n, adjmattype &newAdjMat, std::list<std::vector<int>>& flowpathslist, mapstype& collapmap, std::vector<int> labnodesvect);

//bfs to find the max flow first
bool bfs(adjmattype rGraph, int s, int t, int parent[], std::vector<int>& path);

//function to compute the max flow
int findMaxFlow(adjmattype graph, int s, int t, adjmattype &fGraphvect, std::vector<int> parentorig);

//read the dataset graph from the file
void readDatasetGraph(adjmattype& AdjMat2, int num, int index );

//read the dataset laels
void readDatasetLabels(std::vector<int>& labels, int num, int index);

//read the labelled nodes in the dataset
void readDatasetLabelledNodes(std::vector<int>& labnodes, int num, int index);

//keep track of which node the nodes are being collapsed to
void trackCollapse( const std::vector<int> supernodes, const std::list< std::vector<int> > collaplistret, mapstype& mapsforcollapse);

//predict the labels
void predictLabels(const std::list< std::vector<int> > flowpathlist, const mapstype mapnewtoold, std::vector<int> newlabels, int newn, std::vector<int>& predlabelsNewGraph, std::vector<int> f_jvect ); 

//label the whole graph from collapsed graph
void labelAllNodesFromCollapsed(std::vector<int>& predlabelsWholeGraph, std::vector<int> labcollapsednodes, mapstype mapcollap, mapstype mapnewtoold);

//average results
void averageResults(const std::list< std::vector< int > > predLabelsAlltrials, const int trials, const std::vector< int > truelabels, double& meanacc, double& stddevacc, const int n, std::string filename);

//read sim graph from file
void readSimGraph(adjmattype& AdjMat2, int num );

void collapseLabelledNodes(adjmattype in, adjmattype& out, int num, std::vector<int> f_j, int lenfj, std::vector<int> labnodes, int lenlabnodes, std::vector<int>& supernodes, std::list< std::vector<int> >& collaplist);

//utility to convert adjacency matrix to adjacency list
void ConvertAdjMatToList(adjmattype AdjMat, std::list<std::vector<int>>& AdjList);

//function to generate flow induced network 
void generateFlowInducedNWForSCC(adjmattype AdjMat, adjmattype& flwAdjMat, adjmattype residual);

//function to find the strongly connected component
void findSCCs(adjmattype AdjMat, std::list<std::vector<int>>& listScc);

//DFS  first for finding SCC
void DFSFirstForSCC(int vertex, bool visited[], std::stack<int> &Stack, adjlist adjlist);

//DFS second for finding SCC
void DFSSecondForSCC(int vertex, bool visited[], std::stack<int> &Stack, adjlist adj, std::vector<int>& scc);

//transposing the graph for finding SCCs
void transposegraph(adjmattype AdjMat, adjmattype& AdjMatTrans);

//converting adjmat to adjlist
void convertAdjMatToList(adjmattype AdjMat, std::list<std::vector<int>>& AdjList);

//dfs for undirected edges not in flow paths and not already in contracted list
void dfsforundirectededgesonly(int index, std::list<std::vector<int>> nodestocontractfullist, std::vector<int>& nodestocontract, adjmattype residual, std::vector<int> totalflowpathnodes, adjmattype AdjMat);

//find the scc the node is present in 
bool findSccForNode(std::list<std::vector<int>> listScc, int nodetocontract, std::vector<int>& sccfornode);

//constructing pq graph by collapsing the scc first
void contractGraphSCCBySccFirst(std::vector<int> parentorig, int maxflow, adjmattype &residual, int source, int target, 
	adjmattype AdjMat, const int n, adjmattype &newAdjMat, std::list<std::vector<int>>& flowpathslist, mapstype& collapmap, std::vector<int> labnodesvect);

#endif
