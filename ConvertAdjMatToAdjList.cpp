/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;

#include"Misc.h"

using namespace std;

void convertAdjMatToList(adjmattype AdjMat, list<vector<int>>& AdjList)
{
	vector<int> neighbours;
	for(int i = 0; i< V; ++i)
	{
		neighbours.clear();
		int vertextocons = i;
			for(int j = 0; j <V; ++j)
			{
			if(1 == AdjMat[i][j])//only consider directed edges, even no flow edges will be directed by now
			{
				neighbours.push_back(j);
			}
		}
		AdjList.push_back(neighbours);
	}

}