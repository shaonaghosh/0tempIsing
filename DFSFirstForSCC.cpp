/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;
//function to perform dfs to order according to completion time of the dfs for each vertex as first step
//for finding strongly connected components
void DFSFirstForSCC(int vertex, bool visited[], stack<int> &Stack, adjlist adj)
{
	// Mark the current node as visited and print it
    visited[vertex] = true;
 
    // Recur for all the vertices adjacent to this vertex
    adjlist::const_iterator listiter;
	vector<int>::const_iterator vectiter;

    //for(listiter = adj.begin(); listiter != adj.end(); ++listiter)
	{
		//vector<int> edges = *listiter;
		if(adj.size() > vertex){
			listiter = std::next(adj.begin(), vertex);
			vector<int> edges = *listiter; 

			for(vectiter = edges.begin(); vectiter != edges.end(); ++vectiter)
			{
				int indxadjnode = *vectiter;
				if(!visited[indxadjnode])
					DFSFirstForSCC(indxadjnode, visited, Stack, adj);
		}
	}
    // All vertices reachable from v are processed by now, push v to Stack
    Stack.push(vertex);
}
}