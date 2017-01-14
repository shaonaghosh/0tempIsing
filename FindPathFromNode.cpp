/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;


//find the flow path that the node to label is contained in
vector<int> findPathFromNode(int indexofnode, list<vector<int>> flowpathlist)
{
	vector<int> retpath;
	list<vector<int>>::const_iterator listiter;
	for(listiter = flowpathlist.begin(); listiter != flowpathlist.end(); ++listiter)
	{
		vector<int> path = *listiter;
		vector<int>::const_iterator vectiter;
		if(std::find(path.begin(), path.end(), indexofnode) != path.end())
		{
			return path;
		}
	}
	return retpath;
}