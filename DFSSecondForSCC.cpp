#include"Misc.h"

using namespace std;

void DFSSecondForSCC(int vertex, bool visited[], stack<int> &Stack, adjlist adj, vector<int>& scc)
{
	// Mark the current node as visited and print it
    visited[vertex] = true;
    cout << vertex << " ";
	scc.push_back(vertex);
	
 
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
					DFSSecondForSCC(indxadjnode, visited, Stack, adj, scc);
			}
		}
	}
}


