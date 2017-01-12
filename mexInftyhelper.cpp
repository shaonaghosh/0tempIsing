/* ---------------------------------------------------------------------------
** This file is composed of helper c++ routines to assist in the matlab infinity norm graph labelling**
** mexInftyhelper.cpp
** <very brief file description>
**
** Author: Shaona Ghosh
** Date: 26.02.2014
** -------------------------------------------------------------------------*/

#include <iostream>
#include <math.h>
#include "mex.h"
#include<stdio.h>
#include"igraph.h"
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<sstream>
#include<iostream>
#include<stack>
#include<fstream>
#include<limits>

using namespace std;

//Typedefs
typedef vector<vector<int>> adjmattype;

void _main();

// Number of vertices in given graph
#define V 6

//TODO to add exception handling
bool bfs(adjmattype rGraph, int s, int t, int parent[], vector<int>& path);
bool vanilladfs( adjmattype rGraph, int s, int t, int parent[], vector<int>& path)
{
	// Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    // Create a stack, with source vertex and mark source vertex
    // as visited
    stack<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
	
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.top();
        q.pop();
		path.push_back(u);

		//If already target reached - TEST CODE
		if (visited[t] == true)
			break;
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
				//path.push_back(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

void dfs(int index, vector<int>& nodestocontract, adjmattype Adj, vector<int> totalflowpath)
{
	
	vector<int> visitedarr;
	
	//same labels start exploring neighbours depth first, new dfs stack for each i 
	stack<int> s;
	s.push(index);
	while(s.empty() == false){
		//add starting node to stack
		int top = s.top();
		s.pop();

		//if( NULL != top ){
		//check if already visited if yes continue with others
		if( ( visitedarr.empty() == false ) && (std::find(visitedarr.begin(), visitedarr.end(), top) != visitedarr.end()))
			continue;
		
		visitedarr.push_back(top);
		//find neighbours of top
		for(int i = 0 ; i < V; ++i)
		{
			//If neighbout of top and not in flow path
			if(Adj[top][i] != 0 && (std::find(totalflowpath.begin(), totalflowpath.end(), i) == totalflowpath.end()))
			{
					s.push(i);
			}
		}
		//cout << "Traversed node  " << top << "\n";
		
	}
	nodestocontract = visitedarr;
}


adjmattype contractGraph(vector<int> parentorig, int maxflow, adjmattype &residual, int source, int target, adjmattype AdjMat, int *num)
{
	//Contract edges and keep track of vertices contracted to supernodes until maxflow paths found
	int cntmaxflowpath = maxflow;
	vector<int> flowpath;
	vector<int> totalpath;
	int parentofpath[V];
	adjmattype residualcpy(residual.begin(),residual.end());
	//std::copy(residual.begin(), residual.end(), residualcpy.begin());
	//bfs is called with target as source and source as target
	while( cntmaxflowpath  )
	{
		vanilladfs(residualcpy, source, target, parentofpath, flowpath);
		//remove already found path from graph
		//int sizepar = sizeof(parentofpath)/sizeof(parentofpath[0]);
		int sizepath = flowpath.size();
		for(int i = 0; i < sizepath-1; ++i)
		{
			residualcpy[flowpath.at(i)][flowpath.at(i+1)]= -2; //-2 to indicate already seen flow path once
		}
		totalpath.insert(totalpath.end(), flowpath.begin(), flowpath.end());
		--cntmaxflowpath;
		flowpath.clear();
		memset(parentofpath,0,sizeof(parentofpath)/sizeof(parentofpath[0])); //TODO not getting reset
	}
	std::vector<int>:: const_iterator iter;
	vector<int> nodestocontract;
	ofstream fileid;
	fileid.open ("verticescontracted.txt");


	//Keep a copy of totalpath
	vector<int> totalpathcpy(totalpath.begin(), totalpath.end());

	//Remove duplicates from the nodes in the max flow path
	sort( totalpathcpy.begin(), totalpathcpy.end() );
	totalpathcpy.erase( unique( totalpathcpy.begin(), totalpathcpy.end() ), totalpathcpy.end() );


	for( iter = totalpathcpy.begin(); iter != totalpathcpy.end(); ++iter)
	{
		int index = *iter;
		//find all the vertices that needs to be contracted
		//Do dfs to find out neighbouring vertices that needs to be contracted - should not be present in flow path and neighbour of current 
		dfs(index, nodestocontract, AdjMat,  totalpathcpy); 
		//save to file the nodes to contract per node in the flow path to be used by matlab to deflatten graph

		char buffer[100];
		std::vector<int>::const_iterator iter2;
		if(!nodestocontract.empty())
		{
		for( iter2 = nodestocontract.begin(); iter2 != nodestocontract.end(); ++iter2)
		{
				sprintf(buffer,"%d ", *iter2);
				fileid << buffer;
			
		}
		fileid << endl;
		nodestocontract.clear();
		}

	}
	fileid.close();
	//Create new adjacency matrix
	vector<vector<int>> newAdj(totalpathcpy.size(),vector<int>(totalpathcpy.size()));
	//for(int i = 0 ; i<totalpathcpy.size(); ++i)
	{
		//for(int j = 0; j<totalpathcpy.size(); ++j)
		{
			//Find first occurence of 
			//auto itsrc = std::find(totalpathcpy.begin(),totalpathcpy.end(),source);
			//auto itdest = std::find(totalpathcpy.begin(), totalpathcpy.end(),target); 
			//// check that there actually is present in the vector
			//std::vector<int>::const_iterator itpath = itsrc;
			//while( itpath != itdest)
			//{
			//	for(int j = 0; j < V; ++j)
			//	{
			//		if(AdjMat[*itpath][j] != 0)&& (std::find((*iter).begin(), (*iter).end(), j) != (*iter).end()))
			//	{
			//		newAdj[i][j] = 1;
			//		newAdj[j][i] = 1;
			//	}
			//	if (it != totalpathcpy.end()) {
			//		totalpathcpy.erase(it);
			//	}
			//	++itpath;
			//	}
			//}
		}
	}
	//Mapping to original vertices
	//cout<< "Just Pausing";
	*num = totalpathcpy.size();
	return AdjMat;
}
//The max flow and bfs modules are adapted from http://www.geeksforgeeks.org/find-edge-disjoint-paths-two-vertices/
bool bfs(adjmattype rGraph, int s, int t, int parent[], vector<int>& path)
{
    // Create a visited array and mark all vertices as not visited
    bool visited[V];
    memset(visited, 0, sizeof(visited));
 
    // Create a queue, enqueue source vertex and mark source vertex
    // as visited
    queue <int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;
	
 
    // Standard BFS Loop
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
		path.push_back(u);

		//If already target reached - TEST CODE
		if (visited[t] == true)
			break;
 
        for (int v=0; v<V; v++)
        {
            if (visited[v]==false && rGraph[u][v] > 0)
            {
                q.push(v);
				//path.push_back(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }
 
    // If we reached sink in BFS starting from source, then return
    // true, else false
    return (visited[t] == true);
}

int findMaxFlow(adjmattype graph, int s, int t, adjmattype &fGraphvect, vector<int> parentorig)
{
    int u, v;
 
    // Create a residual graph and fill the residual graph with
    // given capacities in the original graph as residual capacities
    // in residual graph
    //int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates
                     // residual capacity of edge from i to j (if there
                     // is an edge. If rGraph[i][j] is 0, then there is not)
	adjmattype  rGraph(graph.begin(),graph.end());
	//std::copy(graph.begin(),graph.end(), rGraph.begin());
    /*for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];*/
 
    int parent[V];  // This array is filled by BFS and to store path
	vector<int> path;
    int max_flow = 0;  // There is no flow initially
 
    // Augment the flow while tere is path from source to sink
    while (bfs(rGraph, s, t, parent, path))
    {
        // Find minimum residual capacity of the edges along the
        // path filled by BFS. Or we can say find the maximum flow
        // through the path found.
        int path_flow = INT_MAX;
 
        for (v=t; v!=s; v=parent[v])
        {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and reverse edges
        // along the path
        for (v=t; v != s; v=parent[v])
        {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
 
	//int fGraph[V][V];
	
	//Calculate the flows on each edge - summing residual + capacity
	for( int i = 0; i < V; ++i)
	{
		for( int j = 0; j < V; ++j )
		{
			//fGraph[i][j] = graph[i][j] - rGraph[i][j];
			fGraphvect[i][j] =  graph[i][j] - rGraph[i][j];
			//cout << fGraphvect[i][j];
			//cout << " ";
			#ifdef _WIN32
				mexPrintf("%d",fGraphvect[i][j]);
				mexPrintf(" ");
			#endif
		}
		#ifdef _WIN32
			mexPrintf("\n");
		#endif
	}
	#ifdef _WIN32
			mexPrintf("\n");
	#endif
	
    // Return the overall flow (max_flow is equal to maximum
    // number of edge-disjoint paths)
    return max_flow;
}

//Using igraph library currently not being used as various problems in datastructure conversion, no control over data structure manipulation, reprsenting flow as floats
int calculatemaxflow( adjmattype Adj ) 
{
	FILE *fileid = NULL;
    fileid = fopen("edgelistorig.txt", "r");
	igraph_t g;
	//igraph_real_t flow;
	igraph_real_t value;
	igraph_vector_t flow;
	igraph_vector_t cut;
	igraph_vector_t partition;
	igraph_vector_t partition2;
	igraph_integer_t source = 0;
	igraph_integer_t target = 4;
	igraph_vector_t capacity;
	igraph_vs_t vs;
	igraph_es_t es;
	igraph_vector_t res;

	igraph_vector_init(&res,0);
	igraph_vector_init(&flow,0);
	igraph_vector_init(&cut,0);
	igraph_vector_init(&partition,0);
	igraph_vector_init(&partition2,0);
	igraph_vector_init(&capacity,1.00);
	
	long int i;
	int error = -1;
	//Use igraph to calculate the max flow in the graphs

	error = igraph_read_graph_edgelist(&g, fileid, 0, 0);
	if( IGRAPH_PARSEERROR == error) 
	{
		//cout << "Could not read file for graph creation" << endl;
		#ifdef _WIN32
			mexPrintf("Could not read file for graph creation");
		#endif
	}


	//Get number of vertices
	int n = igraph_vcount(&g);
	int m = igraph_ecount(&g);
	/*igraph_get_edgelist(&g,&res,0);
	for(int i = 0; i<n; ++i)
	{
		printf( "%d", VECTOR(res)[i]);
	}*/
	//Check the edges and vertices to verify index
	/*igraph_vs_all(&vs);
	igraph_es_all(&es,IGRAPH_EDGEORDER_FROM);
	*/

	//calculate max flow
	
	//igraph_maxflow_value(&g,&flow,1,5,&capacity);
	igraph_maxflow(&g,&value,&flow,&cut,&partition,&partition2,source,target,&capacity);
	for(int i = 0; i<m; ++i)
	{
		printf( "%f\n", VECTOR(flow)[i]);
	}

	//cout << value;


	
	//Destroy graph - todo

	//Close file - todo
	return error;
}



/*********************/

static
adjmattype mexcpp( int * num )
{
	//The adjacency matrix and the labels are going to se sent from the matlab program, c++ code here will be referenced as a library
	//Try out example graph to test the logic of flattening after finding the max flow patha
	int Adj[6][6] = {{0,1,1,1,0,0},
	{1,0,1,0,1,0},
	{1,1,0,1,1,0},
	{1,0,1,0,1,1},
	{0,1,1,1,0,0},
	{0,0,0,1,0,0}};

	const int n = 6;
	const int m = 18;
	//Convert 2d matrix to much neater stl
	//std::vector<vector<int>> AdjMatVect(Adj, Adj+sizeof(Adj)/sizeof(Adj[0][0]));
	std::vector<vector<int>> AdjMat(n,std::vector<int>(n));
	std::vector<int>::const_iterator iter2;
	std::vector<vector<int>>::const_iterator iter1;
	for(int i = 0 ; i<n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			AdjMat[i][j] = Adj[i][j];
			//cout << AdjMat[i][j];
			//cout << " ";
			#ifdef _WIN32
				mexPrintf("%d",AdjMat[i][j]);
				mexPrintf(" ");
			#else
				cout << AdjMat[i][j];
				cout << " ";
			#endif
		}
		//cout << endl;
		#ifdef _WIN32
				mexPrintf("\n");
		#endif
	}
	
	//initial labelling
	double f_j[] = {-1,0,0,0,0,1};
	
	//Initially flatten the graph for similar labels 

	//Write to file to be able to import to igraph later
	ofstream fileid;
	fileid.open ("edgelistorig.txt");
	for(int i = 0 ; i<n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			char buffer[50];
			sprintf(buffer,"%d %d",i, Adj[i][j]);
			fileid << buffer << endl;
		}
	}
	fileid.close();


	//read file for igraph graph creation
	//calculatemaxflow(AdjMat);
	//cout << endl;
	//cout << endl;
	#ifdef _WIN32
				mexPrintf("\n");
	#endif

	adjmattype fGraphvect(V, std::vector<int>(V));
	std::vector<int> parentorig;
	int source = 0;
	int target = 4;
	//double maxflow = findMaxFlow(Adj,0,4,fGraphvect,parentorig);
	double maxflow = findMaxFlow(AdjMat,0,4,fGraphvect,parentorig);

	//Find the edge disjoint paths
	adjmattype Adjmatnew = contractGraph(parentorig, maxflow, fGraphvect, source, target, AdjMat, num);
	
	
	std::getchar();
	
	return;
}
void mexFunction(
		 int          nlhs,
		 mxArray      *[],
		 int          nrhs,
		 const mxArray *prhs[]
		 )
{

	/* Check for proper number of arguments */

  if (nrhs != 0) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargin", 
            "MEXCPP requires two input arguments.");
  } else if (nlhs > 1) {
    mexErrMsgIdAndTxt("MATLAB:mexcpp:nargout",
            "Too many o/p arguments.");
  }
  //vin1 = (double *) mxGetPr(prhs[0]);
  //vin2 = (double *) mxGetPr(prhs[1]);
  int num = NULL;
  adjmattype adjnew = mexcpp(&num);

  plhs[0] = mxCreateDoubleMatrix(num, num, mxINT);
  std::vector<int>::const_iterator
  for(int i=0; i<num;++i)
  {

  }
  return;
}