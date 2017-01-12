#include"Misc.h"

using namespace std;


//function to check if a given node is in any other to contract list
bool isInUndirectedToContract( int index, list<vector<int>> nodestocontractlist, vector<int>& undirected)
{
	list<vector<int>>::const_iterator listiter;
	for(listiter = nodestocontractlist.begin(); listiter != nodestocontractlist.end(); ++listiter)
	{
		vector<int> nodes  = *listiter;
		if(std::find(nodes.begin(), nodes.end(), index) != nodes.end())
		{
			//check if size of this to collapse list where index present is more than 1
			if(nodes.size() > 1)
			{
				undirected = nodes;
				//means that this is a flow path node that has more than one undirected edge connected to it
				return true;
			}
		}

	}
	return false;
}
//function to collapse all the undirected edges
void collapseUndirectededges(int sccindex, vector<int> undirectededges, int supernodeidx, 
	vector<int>& nodescontracted, mapstype& collapmap, vector<int> sccin)
{
	for(int i = 1; i < undirectededges.size(); ++i)
	{
		//the first node is sccindex itself
		int undirnode = undirectededges[i];
		//check if on flow path
		if(std::find(sccin.begin(), sccin.end(), undirnode) != sccin.end())
				continue;


		//check for undirected 
		//check if already contracted then continue
		if( nodescontracted.empty() == false && (std::find(nodescontracted.begin(), nodescontracted.end(), undirnode) != nodescontracted.end()))//already contracted
			continue;


		//just collapse it to the supernode
		//update the map
		collapmap[undirnode] = supernodeidx;

		nodescontracted.push_back(undirnode);

	}
}

//function to collapse all the directed edges
void collapseDirectedEdges(vector<int> sccin, int supernodeidx, vector<int>& nodescontracted, mapstype& collapmap, 
	adjmattype residualcpy, adjmattype& newAdjMat, list<vector<int>> nodestocontraclist)
{
		//take care of incoming and outgoing edges to and from these nodes on the flow path to collapse to their supernode or itself
		for(int i = 0; i < sccin.size(); ++i)
		{
			int idx = sccin[i];
			for(int j = 0; j<V; ++j)
			{
				//find any outgoing or incoming directed edge - original flow edges - will either have incoming or outgoing from the
				//same vertex
				if( (1 == residualcpy[sccin[i]][j]) )//outgoing flow edge
				{
					//check that not one of the undirected collapsible edges list(which will be dealt later)
					//or is an already collapsed edge
					//if(!isInUndirectedToContract(j, nodestocontraclist))
					if(std::find(sccin.begin(), sccin.end(), j) == sccin.end())//not in same scc to collapse
					{
						//check if not already contracted
						if(std::find(nodescontracted.begin(), nodescontracted.end(), j) == nodescontracted.end())
						{
							newAdjMat[supernodeidx][j] = 1;//will be in the same direction as the incoming edge
														//j could be collapsed later into another supernode
							//also if previously this scc node was not collapsed, alter the entry
							if(sccin[i] != supernodeidx){
								if(1 == newAdjMat[sccin[i]][j])
									newAdjMat[sccin[i]][j] = 0;//no longer its own 
							}
						}
						else//already contracted
						{
							if(present(collapmap, j)){
								mapstype::const_iterator mapiter = collapmap.find(j);
								//collapsed t0
								int supernode = mapiter->second;
								newAdjMat[supernodeidx][supernode] = 1;//outgoing from already collapsed
								//also if previously this scc node was not collapsed, alter the entry
								if(sccin[i] != supernodeidx){
									if(1 == newAdjMat[sccin[i]][supernode])
										newAdjMat[sccin[i]][supernode] = 0;//no longer its own 
								}
								
							}
						}
						
					}
				}
				else if( 1 == residualcpy[j][sccin[i]] ) //will be either incoming or outgoing edge, will not be both in flow path
				{
					//check that not one of the undirected collapsible edges list(which will be dealt later)
					//or is an already collapsed edge
					//if(!isInUndirectedToContract(j, nodestocontraclist))
					if(std::find(sccin.begin(), sccin.end(), j) == sccin.end())
					{
						//check if not already contracted
						if(std::find(nodescontracted.begin(), nodescontracted.end(), j) == nodescontracted.end())
						{
							newAdjMat[j][supernodeidx] = 1;
							
							//also if previously this scc node was not collapsed, alter the entry
							if(sccin[i] != supernodeidx){
								if(1 == newAdjMat[j][sccin[i]])
									newAdjMat[j][sccin[i]] = 0;//no longer its own 
							}
														
						}
						else//already contracted
						{
							if(present(collapmap, j)){
								mapstype::const_iterator mapiter = collapmap.find(j);
								//collapsed t0
								int supernode = mapiter->second;
								newAdjMat[supernode][supernodeidx] = 1;//outgoing from already collapsed
								
								if(sccin[i] != supernodeidx){
									if(1 == newAdjMat[supernode][sccin[i]])
										newAdjMat[supernode][sccin[i]] = 0;//no longer its own 
								}
								
							}
						}	

					}
				}
							
			}//just dealt with all incoming and outgoing flow edges from this scc node being collapsed to its supernode or itself
			//add to nodescontracted if not a supernode itself
			if(supernodeidx != sccin[i])
			{
				//is not a supernode itself, else will not be added to nodescontracted list
				if(std::find(nodescontracted.begin(), nodescontracted.end(), sccin[i]) == nodescontracted.end())
					nodescontracted.push_back(sccin[i]);
			}
			//update the map to keep track which supernode this scc node got collapsed to
			collapmap[sccin[i]] = supernodeidx;


			//find if any undirected edges needs to be collapsed for this scc in node just collapsed
			vector<int> undirectededges;
			isInUndirectedToContract(sccin[i], nodestocontraclist, undirectededges);
			collapseUndirectededges(sccin[i], undirectededges, supernodeidx, nodescontracted, collapmap, sccin);
		
		}
}
void findkArbFlowPaths(list<vector<int>>& flowpathslist, int& cntmaxflowpath, adjmattype& residualcpy, 
	int source, int target, int parentofpath[], vector<int>& flowpath, vector<int>& totalpath )
{
	while( cntmaxflowpath  )
	{
		vanilladfs(residualcpy, source, target, parentofpath, flowpath); //dfs wherever source and target far apart. Todo consider bfs.
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
}

void findAllUndirEdgesToCollapse(list<vector<int>>& nodestocontractlist, vector<int>& nodestocontract, adjmattype residualcpy, 
	vector<int> totalpathcpy, adjmattype AdjMat, list<vector<int>> flowpathslist)
{
	std::vector<int>:: const_iterator iter, iter2;
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
		//dfsforundirected(index, nodestocontract, residualcpy,  currflowpath, AdjMat); 
		dfsforundirectededgesonly(index, nodestocontractlist, nodestocontract, residualcpy, totalpathcpy, AdjMat);
		nodestocontractlist.push_back(nodestocontract);
		nodestocontract.clear();
	}
}


//contract the graph by removing the loops as in Provan and Ball
void contractGraphSCC(vector<int> parentorig, int maxflow, adjmattype &residual, int source, int target, 
	adjmattype AdjMat, const int n, adjmattype &newAdjMat, list<vector<int>>& flowpathslist, mapstype& collapmap, vector<int> labnodesvect)
{
	list<vector<int>> listScc;
	int cntmaxflowpath = maxflow;
	vector<int> flowpath;
	vector<int> totalpath;
	int parentofpath[V];
	adjmattype residualcpy(residual.begin(),residual.end());
	adjmattype flwAdjMat(residual.begin(),residual.end());
	
	////reverse the directions of all the edges where no flow is happening
	generateFlowInducedNWForSCC(AdjMat, flwAdjMat, residual);
		
	//find the SCCs in the flow induced network to find the scc components to collapse apparently this would collapse the loops only
	findSCCs(flwAdjMat, listScc);
	
	//Find k arb maxflow paths from the flow network
	std::copy(residual.begin(), residual.end(), residualcpy.begin());
	findkArbFlowPaths(flowpathslist, cntmaxflowpath, residualcpy, 
	source, target, parentofpath, flowpath, totalpath );
	
	//Keep a copy of totalpath
	vector<int> totalpathcpy(totalpath.begin(), totalpath.end());
	//Remove duplicates from the nodes in the max flow path
	sort( totalpathcpy.begin(), totalpathcpy.end() );
	totalpathcpy.erase( unique( totalpathcpy.begin(), totalpathcpy.end() ), totalpathcpy.end() );
	
	
	//Find the nodes to collapse per supernode - find all undirected edges(edges not in flowpath) to collapse for all nodes on flow paths
	vector<int> nodestocontract;
	vector<int> nodescontracted;
	list<vector<int>> nodestocontraclist;
	//Save to file
	ofstream fileid;
	fileid.open ("verticescontracted.txt");

	findAllUndirEdgesToCollapse(nodestocontraclist, nodestocontract, 
		residual, totalpathcpy, AdjMat, flowpathslist);
	
	//list<vector<int>>::const_iterator listiter1;
	//vector<int>::const_iterator itervect;
	//int countnodeonflowpath = 0;


	//now collapse the SCCs to supernodes to remove loops
	//go through each flow paths and collapse everything not in flow paths
	std::list<vector<int>>::const_iterator iterpaths;
	std::vector<int>::const_iterator iterpathnode;
	list<vector<int>> listSccCpy = listScc;
	for( iterpaths = flowpathslist.begin(); iterpaths != flowpathslist.end(); ++iterpaths)
	{	
		vector<int> path = *iterpaths;
		for(iterpathnode = path.begin(); iterpathnode != path.end(); ++iterpathnode)
		{
			int nodetocontract = *iterpathnode;
			int supernodeidx = -1;//the index that this current node will collapse to could be itself
			int anynodeinsccwithlab = -1;
			vector<int> sccin;
			//check if in strongly connected components or not, then find its scc
			findSccForNode(listSccCpy, nodetocontract, sccin);
			if( false == sccin.empty() )//has other nodes to collapse with
			{
				//should be present in any strongly connected component, either it itself is a scc or present with others
				//find out the node in this scc that this node should collapse to
				//which one is the labelled node:Todo use map here
					for(int j = 0; j < sccin.size(); ++j)
					{
						if(std::find(labnodesvect.begin(), labnodesvect.end(), sccin[j]) != labnodesvect.end()){
							anynodeinsccwithlab = j;//has a label associated with some node in scc
							supernodeidx = sccin[j];//can be the supernode
							break;
						}
					}
				
				//no node in scc has a label so
				//not any labelled node so pick itself as supernode
				if(-1 == supernodeidx)
						supernodeidx = nodetocontract;
				//collapse the sccs to this supernode by keeping track of all incoming and outgoing edges
				//collapseDirectedEdges(sccin, supernodeidx, nodescontracted, collapmap, residual);
				collapseDirectedEdges(sccin, supernodeidx, nodescontracted, collapmap, 
				residual, newAdjMat, nodestocontraclist);
				//remove the scc that has been collapsed already
				listSccCpy.remove(sccin);
			}





		}
	}
	cout << "";
}




