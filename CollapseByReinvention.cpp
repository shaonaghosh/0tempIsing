#include"Misc.h"

using namespace std;

//function to contract first the undirected edges, then find all flow path edges to collapse by forward directed edges
void contractGraph(vector<int> parentorig, int maxflow, adjmattype &residual, int source, int target, adjmattype AdjMat, const int n, adjmattype &newAdjMat, list<vector<int>>& flowpathslist, mapstype& collapmap, vector<int> labnodesvect)
{
	//Contract edges and keep track of vertices contracted to supernodes until maxflow paths found
	//list<vector<int>> flowpathslist;
	int cntmaxflowpath = maxflow;
	vector<int> flowpath;
	vector<int> totalpath;
	int parentofpath[V];
	adjmattype residualcpy(residual.begin(),residual.end());
	//std::copy(residual.begin(), residual.end(), residualcpy.begin());
	//bfs is called with target as source and source as target
	while( cntmaxflowpath  )
	{
		vanilladfs(residualcpy, source, target, parentofpath, flowpath); //dfs wherever source and target far apart
		//remove already found path from graph
		//int sizepar = sizeof(parentofpath)/sizeof(parentofpath[0]);
		int sizepath = flowpath.size();
		for(int i = 0; i < sizepath-1; ++i)
		{
			residualcpy[flowpath.at(i)][flowpath.at(i+1)]= -2; //-2 to indicate already seen flow path once
		}
		totalpath.insert(totalpath.end(), flowpath.begin(), flowpath.end());
		//Add the flow path to the list of flow paths
		flowpathslist.push_back(flowpath);
		--cntmaxflowpath;
		flowpath.clear();
		memset(parentofpath,0,sizeof(parentofpath)/sizeof(parentofpath[0])); //TODO not getting reset
	}
	
	//Keep a copy of totalpath
	vector<int> totalpathcpy(totalpath.begin(), totalpath.end());
	
	//Remove duplicates from the nodes in the max flow path
	sort( totalpathcpy.begin(), totalpathcpy.end() );
	totalpathcpy.erase( unique( totalpathcpy.begin(), totalpathcpy.end() ), totalpathcpy.end() );
	
	//Find the nodes to collapse per supernode - find all undirected edges(edges not in flowpath) to collapse for all nodes on flow paths
	std::vector<int>:: const_iterator iter, iter2;
	vector<int> nodestocontract;
	vector<int> nodescontracted;
	list<vector<int>> nodescontractedlist;
	//Save to file
	ofstream fileid;
	fileid.open ("verticescontracted.txt");

	//For every node on the flow paths,find the undirected edges first, then check if this node is in the scc, collapse the scc to the supernode,
	//preferbaly to the labelled node in the scc, then collapse the undirected nodes connected to this node being collapsed (if), else 
	//nothing to collapse move to the next one
	for(iter = totalpathcpy.begin(); iter != totalpathcpy.end(); ++iter)
	{
		int index = *iter;
		//check if already contracted then continue
		//if(std::find(nodescontracted.begin(), nodescontracted.end(), index) != nodescontracted.end())//already contracted
			//continue;

		
		//find all the vertices that needs to be contracted
		//Do dfs to find out all undirected egdes that needs to be collapsed - nodes collected can be present in flow path  
		//dfs(index, nodestocontract, AdjMat,  totalpathcpy); 
		//find path for this node on flowpaths
		vector<int> currflowpath = findPathFromNode(index, flowpathslist);
		//nodestocontract above will include, for each node in flow path, nodes not in flow paths, nodes in same or different flowpaths
		dfsforundirected(index, nodestocontract, residualcpy,  currflowpath, AdjMat); 
		nodescontractedlist.push_back(nodestocontract);
		nodestocontract.clear();
	}
	cout << "";
	//list<vector<int>>::const_iterator listiter1;
	//vector<int>::const_iterator itervect;
	//int countnodeonflowpath = 0;
	//for(listiter1 =  nodescontractedlist.begin(); listiter1 != nodescontractedlist.end(); ++listiter1)
	//{
	//	int nodeonflowpathidx = totalpathcpy[countnodeonflowpath];
	//	vector<int> currflowpath = findPathFromNode(nodeonflowpathidx, flowpathslist);
	//	vector<int> nodestocontract1 = *listiter1;
	//	bool bsupernode = true;
	//	int supernodeidx = -1;

	//	//first collpase the nodes on the flow path that this one is connected to
	//	//collect the nodes to be collpased that are in the flow paths
	//	//does not matter which order I am collapsing 7-6 or 6-7 and 6-7 -10 /7-6 - 10 as long as anything in between
	//	
	//	//taking care of directed edges. First find which one is the labelled node
	//	if(false == nodesonflowpathtocontract.empty())
	//	{
	//	//which one is the labelled node
	//	for(int j = 0; j < nodesonflowpathtocontract.size(); ++j)
	//	{
	//		if(std::find(labnodesvect.begin(), labnodesvect.end(), nodesonflowpathtocontract[j]) != labnodesvect.end()){
	//			indxofanysuchnodewithlab = j;
	//			supernodeidx = nodesonflowpathtocontract[j];
	//		}
	//	}
	//	//not any labelled node so pick itself as supernode
	//	if(-1 == supernodeidx)
	//		supernodeidx = nodeonflowpathidx;
	//	//take care of incoming and outgoing edges to and from these nodes on the flow path to collapse
	//	for(int i = 0; i < nodesonflowpathtocontract.size(); ++i)
	//	{
	//		for(int j = 0; j<V; ++j)
	//		{
	//			//find any outgoing directed edge
	//			if( residualcpy[nodestocontract1[i]][j] != 0 || residualcpy[j][nodestocontract1[i]] != 0 )
	//			{
	//				//check that not one of the collapsible nodes or already collapsed
	//				if(std::find(nodestocontract1.begin(), nodestocontract1.end(), j) == nodestocontract1.end())
	//				{
	//					if(std::find(nodescontracted.begin(), nodescontracted.end(), j) == nodescontracted.end())
	//					{
	//						newAdjMat[supernodeidx][j] = 1;
	//						newAdjMat[j][supernodeidx] = 1;
	//						
	//					}
	//					else{//if already contracted then need to find out which node contracted to and connect to that instead
	//						if(present(collapmap, j)){
	//							mapstype::const_iterator mapiter = collapmap.find(j);
	//							//collapsed t0
	//							int supernode = mapiter->second;
	//							newAdjMat[supernode][j] = 1;
	//							newAdjMat[j][supernode] = 1;
	//							
	//						}
	//	

	//					}
	//				}
	//			}
	//			
	//		}
	//						
	//		
	//		//add to nodescontracted
	//		if(supernodeidx != nodestocontract1[i])
	//		{
	//			//is not a supernode itself, else will not be added to nodescontracted list
	//			nodescontracted.push_back(nodestocontract1[i]);
	//		}
	//		//update the map
	//		collapmap[nodestocontract1[i]] = supernodeidx;

	//	}
	//	}//collapsing directed edges if in loops
	//	//for undirected edges
	//	for(itervect = nodestocontract1.begin(); itervect != nodestocontract1.end(); ++itervect)
	//	{
	//		int idx = *itervect;
	//		//check if on flow path
	//		if(std::find(nodesonflowpathtocontract.begin(), nodesonflowpathtocontract.end(), idx) != nodesonflowpathtocontract.end())
	//			continue;

	//		
	//		//check for undirected 
	//		//check if already contracted then continue
	//		if( nodescontracted.empty() == false && std::find(nodescontracted.begin(), nodescontracted.end(), idx) != nodescontracted.end())//already contracted
	//			continue;

	//		
	//	    //just collapse it to the supernode
	//		//update the map
	//		collapmap[idx] = supernodeidx;

	//		
	//		nodescontracted.push_back(idx);
	//		
	//	}
	//	}//just contracted the list (directed loops and undirected edges)for this node 
	//	else{//nothing to contract
	//		//this is already a supernode, connect to all other supernodes
	//		for(int i = 0; i<V; ++i)
	//		{
				//check all incoming and outgoing to t
	//			if(residualcpy[nodeonflowpathidx][i] != 0 || residualcpy[i][nodeonflowpathidx] != 0)
	//			{
	//				//check if this node is already contracted, then connect to its supernode
	//				if( nodescontracted.empty() == false && std::find(nodescontracted.begin(), nodescontracted.end(), i) != nodescontracted.end())//already contracted
	//				{
	//						if(present(collapmap, i)){
	//							mapstype::const_iterator mapiter = collapmap.find(i);
	//							//collapsed t0
	//							int supernode = mapiter->second;
	//							newAdjMat[nodeonflowpathidx][supernode] = 1;
	//							newAdjMat[supernode][nodeonflowpathidx] = 1;
	//							
	//						}
	//	
	//				}else
	//				{
	//					//else if it is not yet contracted but will be contracted in future, connect to it anyway as during contraction, incoming edges will be taken care of
	//					newAdjMat[nodeonflowpathidx][i] = 1;
	//					newAdjMat[i][nodeonflowpathidx] = 1;

	//					//Note: new graph is undirected as not using directionality in prediction at all
	//				}
	//			}
	//		}
	//	}//done collapsing everything for this node on the flow path
	//	++countnodeonflowpath;
	//}
	//now that all nodes to be collapsed are collected for all nodes in flow paths
	//loop through flow paths in the forward direction(dfs)? to collapse edges - both undirected and directed from collected information
	

		//if(!nodestocontract.empty())
		//{
		//for( iter2 = nodestocontract.begin(); iter2 != nodestocontract.end(); ++iter2)
		//{
		//		sprintf_s(buffer,"%d ", *iter2);
		//		fileid << buffer;
		//		if(true == bsupernode)
		//		{
		//			supernodeidx = *iter2;
		//			bsupernode = false;
		//		}
		//		else{
		//				//update collapsed map info
		//			collapmap[*iter2] = supernodeidx;
		//			if(*iter2 == 253)
		//				cout << "supernode issue";
		//		}
		//}
		
		//fileid << endl;
		//nodestocontract.clear();
		//}

	//}
	//fileid.close();

	//Need to check if any supernode is going to be connected to any other supernode by an edge not in the same flow path - then 

	//Create new adjacency matrix will have zeroes for nodes  not in paths TODO return the flowpaths to keep track of collapsed nodes and supernodes
	//std::list<vector<int>>::const_iterator iterpaths;
	//std::vector<int>::const_iterator iterpathnode;
	//for( iterpaths = flowpathslist.begin(); iterpaths != flowpathslist.end(); ++iterpaths)
	//{	
	//	vector<int> path = *iterpaths;
	//	for(iterpathnode = path.begin(); iterpathnode != path.end(); ++iterpathnode)
	//	{
	//		int index1 = *iterpathnode;
	//		int index2 = -1;
	//		if( (iterpathnode+1) != path.end()){
	//			index2 = *(iterpathnode+1);
	//			newAdjMat[index1][index2] = 1;
	//			newAdjMat[index2][index1] = 1;
	//		}
	//		

	//	}
	//}

	//check the loop for directed edges
	//check how to connect the other supernodes not within flow paths to connect to others
	//remove from totalpathcopy and flow paths - dont need this as creating new graph as and when collapsing 
	//update the new adjacency outside for the reamining nodes on flow paths that did not get collapsed to anything but itself - as above point doing it inside the loop
	//as these ones will have nodescontract size to 1
	//	cout<< "Just Pausing";
}
