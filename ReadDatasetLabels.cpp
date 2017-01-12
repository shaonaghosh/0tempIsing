#include"Misc.h"

using namespace std;
//reading dataset  labels from file
void readDatasetLabels(vector<int>& labels, int num, int index)
{
	std::ifstream fileid;
	char buffer[100];
	sprintf_s(buffer,"%s%d%d%d%s", "labset", num, index, 0, ".csv"); 
	//fileid.open ("labset40010.csv");
	fileid.open(buffer);
	string line;
	while(getline(fileid,line))
	{
		vector<int> labelrec;
		stringstream linestream(line);
		string str1, str2;
		int nodei, labeli;
		getline(linestream, str1, ',');
		getline(linestream, str2, ',');
		//linestream >> nodei >> nodej;
		
		istringstream(str1) >> nodei;
		istringstream (str2) >> labeli; 
		
		//labelrec.push_back(nodei-1);
		//labelrec.push_back(labeli);
		
		labels.push_back(labeli);
	}

	fileid.close();
}