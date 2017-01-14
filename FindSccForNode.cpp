/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;

//function to find if present in list or not
bool findSccForNode(list<vector<int>> nodestocollapse, int index, vector<int>& sccin)
{
	list<vector<int>>::const_iterator listiter;
	for(listiter = nodestocollapse.begin(); listiter != nodestocollapse.end(); ++listiter)
	{
		vector<int> scc = *listiter;
		if(std::find(scc.begin(), scc.end(), index) != scc.end())
		{
			//present in some scc
			sccin = scc;
			return true;
		}
	
	}
	return false;
	
}