/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;

void readSimGraph(adjmattype& AdjMat2, int num )
{
	////File I/O
	std::ifstream fileid;
	char buffer[100] = "simgraphtestcase1.csv";
	//sprintf_s(buffer,"%s%d%d%s", "datasetgraph", num, index, ".csv"); 
	//fileid.open ("datasetgraph4001.csv");
	fileid.open(buffer);
	string line;
	while(getline(fileid,line))
	{
		stringstream linestream(line);
		string str1, str2;
		int nodei, nodej;
		getline(linestream, str1, '\t');
		getline(linestream, str2, '\t');
		//linestream >> nodei >> nodej;
		
		istringstream(str1) >> nodei;
		istringstream (str2) >> nodej; 
	
	
		AdjMat2[nodei][nodej] = 1;//-1 as files have indexes starting at 1
		AdjMat2[nodej][nodei] = 1;
		
	}
	fileid.close();

}