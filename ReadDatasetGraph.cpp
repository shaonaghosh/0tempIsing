/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;
//function to read the dataset and contruct the graph from the file

void readDatasetGraph(adjmattype& AdjMat2, int num, int index )
{
	////File I/O
	std::ifstream fileid;
	char buffer[100];
	sprintf_s(buffer,"%s%d%d%s", "datasetgraph", num, index, ".csv"); 
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
	
	
		AdjMat2[nodei-1][nodej-1] = 1;//-1 as files have indexes starting at 1
		AdjMat2[nodej-1][nodei-1] = 1;
		if( nodei == 254 || nodei == 280)
			cout << "IN here" << endl;
	}
	fileid.close();

}