/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;


//function to get the labels of all other nodes from the collapsed labelled graph
void labelAllNodesFromCollapsed(vector<int>& predlabelsWholeGraph, vector<int> labcollapsednodes, mapstype mapcollap, mapstype mapnewtoold)
{

	//for all nodes, get the labels from the supernodes id collapsed
	for(int nodetopredold = 0; nodetopredold <V; ++nodetopredold){
		int labeltopred = 0;
		int supernode = -1;
		int newindex = -1;
		//find out the supernode if collapsed - if not its the same as itself
		if(present(mapcollap, nodetopredold)){
			mapstype::const_iterator mapiter = mapcollap.find(nodetopredold);
			supernode = mapiter->second;
		}

		
		//get the new index for the supernode
		if(present(mapnewtoold, supernode)){
			mapstype::const_iterator mapiter = mapnewtoold.find(supernode);
			newindex = mapiter->second;
		}

		//the label for this node is the same as the label for this supernode
		if(newindex != -1)
		{
			labeltopred = labcollapsednodes[newindex];
		}

		//update predicted label to predlabel vector- using old index- before that need to be sure this is the 
		predlabelsWholeGraph[nodetopredold] = labeltopred;
	}

}	
