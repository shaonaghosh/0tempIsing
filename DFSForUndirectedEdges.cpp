#include"Misc.h"

using namespace std;

//function to do dfs through undirected edges only
void dfsforundirected(int index, vector<int>& nodestocontract, adjmattype residual, vector<int> path, adjmattype AdjMat)
{
	vector<int> visitedarr;
	//same labels start exploring neighbours depth first, new dfs stack for each i 
	stack<int> s;
	s.push(index);
	while(s.empty() == false){//until no more nodes to visit - dfs finidhes normally
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
			if ( AdjMat[top][i] != 0 &&  (0 == residual[top][i]) )
            {
				//need to check to see if not already in to be contracted list or not in flow paths
                s.push(i);
				
            }
			if(	AdjMat[i][top] != 0 && (0 == residual[i][top]) )
			{
				//need to check to see if not already in to be contracted list or not in flow paths
                s.push(i);
			}
		}
		//cout << "Traversed node  " << top << "\n";
		
	}
	nodestocontract = visitedarr;
}
