#include"Misc.h"

using namespace std;

//function to find the all possible flow path nodes to collapse in between two nodes on the flow path
vector<int> dfsflowpathnodesbetween(int flownode1, int flownode2, adjmattype adjmat, adjmattype residual)
{
	vector<int> visitedarr;
	vector<int> allmarkednodes;

	bool marked[V];
    memset(marked, 0, sizeof(marked));

	int parents[V];
	memset(parents, 0, sizeof(parents));
	//stack<int> parentnodes,

	stack<int> s; //this is the current node stack
	s.push(flownode1);
	//parentnodes.push(-1); //no parent for start node
	parents[flownode1] = -1; //no parent for start node

	int prevcurr = -1;
	
	while(s.empty() == false){//until no more nodes to visit - dfs finishes normally
		//normal backtrack of dfs
		int top = s.top();
		s.pop();//??
		//int topparent = parentnodes.top();
		//should pop parenthere
		//parentnodes.pop();//??
			
		//terminating condition
		if(top == flownode2 || (marked[top] == true))
		{
			//bmark all parents to indicate - found a set  of to be collapsed flow nodes. will be ready for backtrack
			//while(parentnodes.empty() == false)
			//{
			//	//int topparent = parentnodes.top();
			//	if(-1 != topparent && (false == marked[topparent]))
			//	{
			//		marked[topparent] = true;
			//	}
			//	topparent = parentnodes.top();//?? need to pop to change top					
			//}
			//
			for (int v = top; v != flownode1; v = parents[v])
			{
				if(v != -1){
					int u = parents[v];
					if(-1 != u && (marked[u] != true)){
						marked[u] = true;
						//allmarkednodes.push
					}
				}
			}

		
		//check if already visited and marked then dont do forward dfs - normal dfs if visited do not continue but here need to continue even if visited
		//as might not have found destination node yet. at the same time do not want to visit each node repeatedly would be exponential time. so rather backtrack 
		//at this point. continue will cause ot pop the next and hence backtrack
		if( ( visitedarr.empty() == false ) && (std::find(visitedarr.begin(), visitedarr.end(), top) != visitedarr.end()) && (true == marked[top]))
			continue;
		

		
		//if not marked, but visited before or never visited, continue forward dfs
		//visiting for the first time	
		visitedarr.push_back(top);

		//find forward directed edges from top
		for(int i = 0 ; i < V; ++i)
		{
			//forward directed flow edges only - todo check backward directed edges have negative flows so checking with > 0
			if ( adjmat[top][i] != 0 && (residual[top][i] > 0 ))//|| residual[i][top] > 0) ) only forward directed edges
			{
				s.push(i);//might have same node twice - will be taken care of when checking already visited node test above-visited before fine to carry on until not marked, if marked backtrack - pop
				
				parents[i] = top;
			}
		}
		//cout << "traversed node  " << top << "\n";
		
	}
//	nodestocontract = visitedarr;
}
	return visitedarr;
}
	
