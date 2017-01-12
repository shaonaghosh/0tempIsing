#include"Misc.h"

using namespace std;

void transposegraph(adjmattype AdjMat, adjmattype& AdjMatTrans)
{
	for(int i = 0; i < V; ++i)
	{
		for(int j = 0; j < V; ++j){
			if(AdjMat[i][j] != 0 && AdjMat[j][i] != 0)
			{
				//transposing will matter even if the original matrix was undirected as after flows some 
				AdjMatTrans[i][j] = AdjMat[j][i];
				AdjMatTrans[j][i] = AdjMat[i][j];
			}
		}
	}
}