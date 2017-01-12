#include"Misc.h"

using namespace std;
//The max flow and bfs modules are adapted from 
//http://www.geeksforgeeks.org/find-edge-disjoint-paths-two-vertices/
int findMaxFlow(adjmattype graph, int s, int t, adjmattype &fGraphvect, vector<int> parentorig)
{
    int u, v;
	if (-1 == s|| -1 == t)
		return 0;
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
	
	//Calculate the flows on each edge - subtracting residual from capacity, aka. residual capacity current flow on each edge
//	cout << "Flows on edges\n";
	for( int i = 0; i < V; ++i)
	{
		for( int j = 0; j < V; ++j )
		{
			//fGraph[i][j] = graph[i][j] - rGraph[i][j];
			fGraphvect[i][j] =  graph[i][j] - rGraph[i][j];
//			cout << fGraphvect[i][j];
//			cout << " ";
		}
//		cout << endl;
	}
//	cout << endl;
	
    // Return the overall flow (max_flow is equal to maximum
    // number of edge-disjoint paths)
    return max_flow;
}