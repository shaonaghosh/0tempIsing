#include"Misc.h"

using namespace std;

//function to find if present in list or not
bool findiftobecontracted(list<vector<int>> nodestocollapse, int index)
{
	list<vector<int>>::const_iterator listiter;
	for(listiter = nodestocollapse.begin(); listiter != nodestocollapse.end(); ++listiter)
	{
		vector<int> nodes = *listiter;
		if(std::find(nodes.begin(), nodes.end(), index) != nodes.end())
			return true;
	}
	//not present in to be contracted list
	return false;
}
//function to do dfs through undirected edges only
void dfsforundirectededgesonly(int index, list<vector<int>> nodestocontractfullist, vector<int>& nodestocontract, adjmattype residual, vector<int> totalflowpathnodes, adjmattype AdjMat)
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
				if(std::find(totalflowpathnodes.begin(), totalflowpathnodes.end(), i) == totalflowpathnodes.end()
					&& ( !findiftobecontracted(nodestocontractfullist, index)) )
						s.push(i);
            }
			if(	AdjMat[i][top] != 0 && (0 == residual[i][top]))
			{
				if(std::find(totalflowpathnodes.begin(), totalflowpathnodes.end(), i) == totalflowpathnodes.end()
					&& ( !findiftobecontracted(nodestocontractfullist, index)))
						s.push(i);
			}
		}
		//cout << "Traversed node  " << top << "\n";
		
	}
	nodestocontract = visitedarr;
}
