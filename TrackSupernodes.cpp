/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;
//function to track the supernodes to which the nodes gets collapsed to

void trackCollapse( const vector<int> supernodes, const list< vector<int> > collaplistret, mapstype& mapsforcollapse)
{
	std::list< vector<int> >::const_iterator it;
	std::vector<int>::const_iterator it2;
	std:vector<int>:: const_iterator itsuper = supernodes.begin();
	int count = 0;
	for(it = collaplistret.begin(); it!= collaplistret.end(); ++it){
		vector<int> collapsibles = *it;
		for(it2 = collapsibles.begin(); it2 != collapsibles.end(); ++it2)
		{
			int index = *it2;
			//update the collapsible list - no need to check already there
			mapsforcollapse[index] = supernodes[count];
		}
		count++;//each row for each supernode
	}
}