/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;
//read the dataset labelled nodes from the file
void readDatasetLabelledNodes(vector<int>& labnodes, int num, int index)
{
	std::ifstream fileid;
	char buffer[100];
	sprintf_s(buffer,"%s%d%d%s", "trainingset", num, index, ".csv"); 
	fileid.open(buffer);
	string line;
	while(getline(fileid,line))
	{
		
		stringstream linestream(line);
		string str1, str2;
		int nodei, labeli;
		getline(linestream, str1, ',');
		getline(linestream, str2, ',');
		//linestream >> nodei >> nodej;
		
		istringstream(str1) >> nodei;
		istringstream (str2) >> labeli; 
		
		//AdjMat2[nodei-1][nodej-1] = 1;
		//AdjMat2[nodej-1][nodei-1] = 1;
		labnodes.push_back(nodei-1);
	}

	fileid.close();

}