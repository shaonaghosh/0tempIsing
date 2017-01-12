#include"Misc.h"

using namespace std;

//bfs function to find the max flow
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
