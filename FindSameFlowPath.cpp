/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;


//function to find if the nodes to find collapsed nodes between are on the same flow path
bool isOnSamepath(int node1, int node2, vector<int> flowpath)
{
	bool bRet = false;
	if(std::find(flowpath.begin(), flowpath.end(), node1) != flowpath.end() && (std::find(flowpath.begin(), flowpath.end(), node2) != flowpath.end()))
	{
		bRet = true;
	}
	return bRet;
}