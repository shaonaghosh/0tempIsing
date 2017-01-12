#include"Utils.h"
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<queue>
#include<sstream>
#include<iostream>
using namespace std;

int main(int argc, const char* argv[])
{
	//Graph *graphobj = new Graph();
	//SpanningTree *treeobj = new SpanningTree();
	Forest *forestobj = new Forest();

	//string nodenamearr[] = {"a","b","c","d","e","f","g","h","i","j","k","l" }; 
	//string edges[] = {"1-3","1-4","1-5","1-6", "1-11", "3-2", "3-7","3-4", "4-5", "4-8", "5-9","6-10", "1-11", "7-8", "7-11", "11-12"};
	//string edges[] = {"A-B","A-E","B-E","B-C","C-D"};
	//string edges[] = {"A-B","A-E","A-F","B-C","B-D","B-F","C-B","C-D","D-B","D-C","D-F","D-E","E-F","E-A","E-D"};
	//string edges[] = {"1-2","1-3","1-4","2-5","4-5","6-7","4-6","5-7"};

	//TEST CODE for adjacency matrix for the three armed octopus
	int Adj[12][12] = {{ 0 ,    1,     0,     0,     1,     0,     0,     1,     0,     0,     0,     1},
	{1,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0},
	{0,     1,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0},
	{0,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0},
	{1,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     0},
	{0,     0,     0,     0,     1,     0,     1,     0,     0,     0,     0,     0},
	{0,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     0},
	{1,     0,     0,     0,     0,     0,     0,     0,     1,     0,     0,     0},
	{0,     0,     0,     0,     0,     0,     0,     1,     0,     1,     0,     0},
	{0,     0,     0,     0,     0,     0,     0,     0,     1,     0,     1,     0},
	{0,     0,     0,     0,     0,     0,     0,     0,     0,     1,     0,     0},
	{1,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0}};
	
	int cnt = 0;
	int n  = 8;
	bool status = false;
	
		
 	while( cnt <= n - 1){
		//Find which vertex pair to add
		stringstream substr(edges[cnt]);
		string token;
		queue<string> tokenq;
		string vertexa;
		string vertexb;

		while(getline(substr,token,'-')){
			tokenq.push(token);
		}
		
		while(tokenq.empty() == false ){
			vertexa = tokenq.front();
			tokenq.pop();
			vertexb = tokenq.front();
			tokenq.pop();
		}

		//Create the graph
		//graphnode *srcnode = new graphnode();
		//graphnode *destnode = new graphnode();

		//if( NULL != srcnode && NULL != destnode )
		//{	
		//srcnode->nodename = vertexa;
		//cout << "First node created  " << srcnode->nodename << "\n" ;
		////srcnode->visited = false;
		//
		//destnode->nodename = vertexb;
		//cout << "Second node created  " << destnode->nodename << "\n";
		////destnode->visited = false;

		//
		//status = graphobj->connectNodesGraph(srcnode,destnode, edges[cnt]);
		//cnt += 1;

		treenode *srcnode = new treenode();
		treenode *destnode = new treenode();

		if( NULL != srcnode && NULL != destnode )
		{	
		srcnode->nodename = vertexa;
		cout << "First node created  " << srcnode->nodename << "\n" ;
		////srcnode->visited = false;
		srcnode->parent = NULL;
		//
		destnode->nodename = vertexb;
		cout << "Second node created  " << destnode->nodename << "\n";
		////destnode->visited = false;
		destnode->parent = NULL;
		//
		//status = treeobj->connectNodeTree(srcnode,destnode);
		//cnt += 1;


		//Forest
		
		if(forestobj != NULL)
		{
			forestobj->buildForest(srcnode,destnode);
			cnt += 1;
		}
		}
		}
		
		//treeobj->traverseTreeWhole();

	/*treenode *srcnode = new treenode();
	srcnode->nodename = "D";
	treenode *destnode = new treenode();
	destnode->nodename= "B";
	vector<string> path;
	path = treeobj->getPathTree(srcnode,destnode);
	for( std::vector<string>::const_iterator i = path.begin(); i != path.end(); ++i)
    std::cout << *i << ' ';*/

	std::getchar();
	return 0;
}
