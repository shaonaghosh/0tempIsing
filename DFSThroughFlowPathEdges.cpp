/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;

//function to dfs through flow path nodes only
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

		//check if already visited if yes continue with others
		if( ( visitedarr.empty() == false ) && (std::find(visitedarr.begin(), visitedarr.end(), top) != visitedarr.end()))
			continue;
		
		visitedarr.push_back(top);
		//find neighbours of top
		for(int i = 0 ; i < V; ++i)
		{
			//If neighbour of top and not in flow path - TODO need to add check that neighbour not in any to contract list
			//Todo if already in flow path or connected to some neighbour in the same flow path, then need to flag this two supernodes, collapse all supernodes
			//bw these two supernodes connected and return right now restart the loop
			if(Adj[top][i] != 0 && (std::find(totalflowpath.begin(), totalflowpath.end(), i) == totalflowpath.end()))
			{
					s.push(i);
			}
		}
		
		
	}
	nodestocontract = visitedarr;
}
