/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;

//Find the strongly connected components
void findSCCs( adjmattype AdjMat, list<vector<int>>& listScc)
{
    stack<int> Stack;
	vector<int> scc;
 
    // Mark all the vertices as not visited (For first DFS)
    bool visited[V];
    memset(visited, false, sizeof(visited));

	//convert the adjmat to adjlist for finding scc
	adjlist AdjList;
	convertAdjMatToList(AdjMat, AdjList);
 
    // Fill vertices in stack according to their finishing times
    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            DFSFirstForSCC(i, visited, Stack, AdjList);
 
    // Create a reversed graph
	std::vector<vector<int>> AdjMatTrans(V,std::vector<int>(V));
	transposegraph(AdjMat, AdjMatTrans);

	//convert the transposed adjmat to adjlist for finding scc
	adjlist AdjTransList;
	convertAdjMatToList(AdjMatTrans, AdjTransList);
 
    // Mark all the vertices as not visited (For second DFS)
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Now process all vertices in order defined by Stack
    while (Stack.empty() == false)
    {
        // Pop a vertex from stack
        int top = Stack.top();
        Stack.pop();
 
        // Print Strongly connected component of the popped vertex
        if (visited[top] == false)
        {
			scc.clear();
            DFSSecondForSCC(top, visited, Stack, AdjTransList, scc);
            cout << endl;
			listScc.push_back(scc);
        }
		
    }
}