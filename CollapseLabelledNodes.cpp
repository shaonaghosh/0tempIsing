/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<sstream>
#include<iostream>
#include<stack>
#include<list>
#include<utility>
#include<vector>

using namespace std;

typedef vector<vector<int>> adjmattype;
bool isAlreadyCollapsed(int index1, int index2, vector<int> visitedarr, list<vector<int>> collaplist);
bool makeFlattenLabelledGraph(list<vector<int>> collaplist, vector<int> visitedarr, adjmattype AdjMat, adjmattype& AdjLabFlatten, int n);

void collapseLabelledNodes( adjmattype AdjMat, adjmattype& AdjLabFlatten, int num, vector<int> f_pred, int lenf_j, vector<int> labnodesvect, int lenlabnodes, vector<int>& supernodes, list< vector<int> >& collaplistret)
{
	list<vector<int>> collaplist;
	vector<int> listtocollapse;
	vector<int> visitedarr;


	std::vector<int>::const_iterator iter2 ;
	std::vector<int>::const_iterator iter3 ;
	//loop to find out similar labels and collapse the graph

	for(iter2 = labnodesvect.begin(); iter2 != labnodesvect.end(); ++iter2)
	{
		//empty the to-collapse list
		listtocollapse.clear();

		int index = *iter2;
		
		//check if not already collapsed
		//if already seen before index will be supernodes stored in visited arr
		if(std::find(visitedarr.begin(), visitedarr.end(), index) != visitedarr.end())
			continue;

		for(iter3 = labnodesvect.begin(); iter3 != labnodesvect.end(); ++iter3)
		{
		/*if( (iter2+1) != labnodesvect.end()){
				int index2 = *(iter2+1);
		}*/
		//check if already visited or not
		if(std::find(visitedarr.begin(), visitedarr.end(), *iter3) != visitedarr.end())
			continue;
		
		//check if both are the same 
		if( *iter2 == *iter3)
			continue;
		int index2 = *iter3;
		//check if index2 not in list already for any collapsible list 
		if( isAlreadyCollapsed(index, index2, visitedarr, collaplist ))
			continue;
		if( f_pred[index] == f_pred[index2] )
		{		
			listtocollapse.push_back(index2);
			if(std::find(visitedarr.begin(), visitedarr.end(), index) == visitedarr.end())
			visitedarr.push_back(index); // Will contain the supernodes
			
		}
		}
		if(!listtocollapse.empty()) 
			collaplist.push_back(listtocollapse);
		else{
			//means the there is no other similar label, so still add it to the list for later reference after cross checking again
			int count = std::count(f_pred.begin(), f_pred.end(), f_pred[index]);
			if( 1 == count ){ 
				visitedarr.push_back(index);
				collaplist.push_back(listtocollapse);
			}
		}
	}

	//Make new adjacency matrix by flattening
	makeFlattenLabelledGraph(collaplist, visitedarr, AdjMat, AdjLabFlatten, num);

	//return the supernode and collapsible list information
	supernodes = visitedarr;
	collaplistret = collaplist; 
}
bool isAlreadyCollapsed(int index1, int index2, vector<int> visitedarr, list<vector<int>> collaplist)
{	
	std::list<vector<int>>::const_iterator iter2 ;
	std::vector<int>::const_iterator iter3;
	
	for(iter2 = collaplist.begin(); iter2 != collaplist.end(); ++iter2)
	{
		vector<int> listtocollapse = *iter2;
		if(std::find(listtocollapse.begin(), listtocollapse.end(), index2) != listtocollapse.end())
			return true;

	}
	return false;
}
int getAlreadyCollapsedSuperNode(int index2, vector<int> visitedarr, list<vector<int>> collaplist)
{
	int retIdx = -1;
	std::list<vector<int>>::const_iterator iter2 ;
	std::vector<int>::const_iterator iter3;
	for(iter3 = visitedarr.begin(); iter3 != visitedarr.end(); ++iter3)
	{
		int idforsupernode = *iter3;
		for(iter2 = collaplist.begin(); iter2 != collaplist.end(); ++iter2)
		{
			vector<int> listtocollapse = *iter2;
			if(std::find(listtocollapse.begin(), listtocollapse.end(), index2) != listtocollapse.end())
				return idforsupernode;

		}
	}
	return retIdx;
}

//TODO Sloppy code written in rush -need to use recursion
bool makeFlattenLabelledGraph(list<vector<int>> collaplist, vector<int> visitedarr, adjmattype AdjMat, adjmattype& AdjLabFlatten, int n)
{
	bool bRet = false;
	vector<int> nodesnotsuper;
	//create vector of nodes that are not in the visited array
	for(int i = 0; i<n; ++i)
	{
		//check if supernode
		if(std::find(visitedarr.begin(), visitedarr.end(), i) != visitedarr.end())
			continue;
		else
			nodesnotsuper.push_back(i);
	}


	//Visitedarr will be the supernodes
	//Add all neighbours of supernodes, add neighbours of to be collapsed nodes as neighbours(while doing this check if 
	//any of the neighbour already a collapsible node then dont add this neighbour instead add the supernode as its neighbour
	//of supernodes
	//Add any other node that was already in the graph that was not the supernodes i.e. unlabelled nodes
	std::list<vector<int>>::const_iterator itersuperlist = collaplist.begin();
	vector<int>:: const_iterator itertocollap;
	vector<int>:: const_iterator itervisited;
	int count = -1;
	for(itervisited = visitedarr.begin(); itervisited != visitedarr.end(); ++itervisited)
	{
		count++;
		int indexsuper = *itervisited;
		std::advance(itersuperlist, count); //Keeping track of which supernode being visited
		vector<int> tocollapse = *(itersuperlist);
		
		//First connect this supernode to all its original neighbours
		for(int j = 0; j<n; ++j)
		{
			if(AdjMat[indexsuper][j] != 0 && std::find(tocollapse.begin(), tocollapse.end(), j) == tocollapse.end() )
			{
				if(isAlreadyCollapsed(indexsuper,j,visitedarr,collaplist))
				{
					//find its supernode since already collapseed somewhere
					int indxofcollapnode = getAlreadyCollapsedSuperNode(j,visitedarr,collaplist);
					if( indxofcollapnode != -1 )
					{
						AdjLabFlatten[indexsuper][indxofcollapnode] = 1;
						AdjLabFlatten[indxofcollapnode][indexsuper] = 1;
					}
				}else
				{
					//Not in the list to collapse and original neighbours of supernode so connect
					AdjLabFlatten[indexsuper][j] = 1;
					AdjLabFlatten[j][indexsuper] = 1;
				}
			
			}

		}
		vector<int> neighbours;
		//Now go through the list to collapse to connect to neighbours of collapsible nodes
		for(itertocollap = tocollapse.begin(); itertocollap != tocollapse.end(); ++itertocollap)
		{
			//find the neighbours of each and connect to supernode if neighbour not in collapsible list
			int index = *itertocollap;
			
			for(int j = 0; j < n; ++j)
			{
				if(AdjMat[index][j] != 0 && std::find(tocollapse.begin(), tocollapse.end(), j) == tocollapse.end() && j != indexsuper)
				{
					//TODO j should not be in the collapsible list of any supernode in which case
					
					//find all the neighbours
					neighbours.push_back(j);
					AdjLabFlatten[index][j] = 0;
					AdjLabFlatten[j][index] = 0;
				}
			}
			//Need to zero out the rows corr to the collapsible nodes	
			
		}
		//Connect these neighbors found  to the supernode
		vector<int>::const_iterator itneigh;
		for(itneigh = neighbours.begin(); itneigh != neighbours.end(); ++itneigh)
		{
			int indx = *itneigh;
			//check if neighbour in any other to coolapse list if yes connect to its supernode instead
			if(isAlreadyCollapsed(indexsuper,indx,visitedarr,collaplist))
			{
				//find its supernode since already collapseed somewhere
				int indxofcollapnode = getAlreadyCollapsedSuperNode(indx,visitedarr,collaplist);
				if( indxofcollapnode != -1 )
				{
					AdjLabFlatten[indexsuper][indxofcollapnode] = 1;
					AdjLabFlatten[indxofcollapnode][indexsuper] = 1;
				}
			}else
			{
					AdjLabFlatten[indexsuper][indx] = 1;
					AdjLabFlatten[indx][indexsuper] = 1;
			}
		}
	}
	//Now for the nodes that are not in the visited array that is other than the supernodes
	//while adding check that node not in visitedarr and neighbors not in collapsible list
	for(itervisited = nodesnotsuper.begin(); itervisited != nodesnotsuper.end(); ++itervisited)
	{
		int index = *itervisited;
		//check if superbode or not in which case already taken care of
		if((std::find(visitedarr.begin(), visitedarr.end(), index) != visitedarr.end()))
			continue;

		if(isAlreadyCollapsed(index, index,visitedarr, collaplist))
			continue;
		//check if the neighbour connected to is not in the collapsible list
		for(int j = 0 ; j < n; ++j)
		{
			if(AdjMat[index][j] != 0 && !isAlreadyCollapsed(index,j,visitedarr, collaplist) && (std::find(visitedarr.begin(), visitedarr.end(), j)== visitedarr.end()))
			{
				AdjLabFlatten[index][j] = 1;
				AdjLabFlatten[j][index] = 1;
			}
		}
	}
	return bRet;

	
}