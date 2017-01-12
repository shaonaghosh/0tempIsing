#include"Misc.h"

using namespace std;

void generateFlowInducedNWForSCC(adjmattype AdjMat, adjmattype& flwAdjMat, adjmattype residual)
{
	for(int i = 0; i< V; ++i)
	{
		for(int j = 0; j <V; ++j)
		{
			//add directions to the edges that have flow of 0 on their edges
			if( AdjMat[i][j] != 0 && (0 == residual[i][j]) )
				flwAdjMat[j][i] = 1;
			if( AdjMat[j][i] != 0 && (0 == residual[j][i]) )
				flwAdjMat[i][j] = 1;
		}
	}
	
}