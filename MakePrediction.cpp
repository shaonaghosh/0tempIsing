#include"Misc.h"

using namespace std;

//predicts the label
void predictLabels(const list< vector<int> > flowpathlist, const mapstype mapnewtoold, vector<int> newlabels, int newn, vector<int>& predlabelsNewGraph, vector<int> f_jvect ) 
{
	int nodetopred = -1;
	//flowpaths will have vertices in the original indices, need to find corr new indices from the map
	std::list< vector<int> >::const_iterator collaplistiter;
	std::vector<int>::const_iterator pathiter;
	std::vector<int>::const_iterator veciter = predlabelsNewGraph.begin();
	std::map<int,int>::const_iterator mapiter;
	//first predict the nodes in the new graph
	for(int j = 0; j<newn; ++j)
	{
		int labeltopred = 0;
		if(newlabels[j] != 0){
			//already labelled
			//predlabelsNewGraph.push_back(newlabels[j]);
			//predlabelsNewGraph.insert(predlabelsNewGraph.begin()+j, newlabels[j]);
			predlabelsNewGraph[j] = newlabels[j];
			continue;
		}else{//not labelled yet
			int cntmajupstream = 0, cntmajdwnstream = 0;

			//need to get the old index back as can work on old indices itself
			/*if(present(mapnewtoold, j)){
				mapstype::const_iterator mapiter = mapnewtoold.find(j);
				nodetoprednew = mapiter->second;
			}*/	
			//TODO not log n as of searching with key
			
			for (mapiter = mapnewtoold.begin(); mapiter != mapnewtoold.end(); ++mapiter ){
				if (mapiter->second == j){
					nodetopred = mapiter->first; //get the old index, will search through flow paths using this index as flowpaths have old index
					break;
				}
			}
			//iterate through the flow paths to get a predicted majority vote from all paths it is on
			for(collaplistiter = flowpathlist.begin(); collaplistiter != flowpathlist.end(); ++collaplistiter )
			{
				labeltopred = 0;
				vector<int> path = *collaplistiter;
				//find the old mapping for this
				//search through this path to see if there if not continue
				if (std::find(path.begin(), path.end(), nodetopred) == path.end())
					continue;
				//if there, then look for distance to next labelled node and predict 
				//int length to +1 - need to check first labelled upstream
				//int length to -1 - need to check first labelled downstream, need to retrive their labels
				int lenupstream = 0, lendownstream = 0;
				std::vector<int>::const_iterator iternodetolab = std::find(path.begin(), path.end(), nodetopred);
				//find upstream
				for(pathiter = iternodetolab; pathiter != path.end(); ++pathiter)
				{
					int nodeinpath = *pathiter;
					if(f_jvect[nodeinpath] == 0){//if unlabelled continue searching
						lenupstream++;
						continue;
					}
					else if(f_jvect[nodeinpath] == 1){
						break;
					}

				}
				std::vector<int>::const_reverse_iterator riternodetolab = std::find(path.rbegin(), path.rend(), nodetopred);
				std::vector<int>::const_reverse_iterator rpathiter; 
				for(rpathiter = riternodetolab; rpathiter != path.rend(); ++rpathiter )
				{
					int nodeinpath = *rpathiter;
					if(f_jvect[nodeinpath] == 0){//if unlabelled continue searching
						lendownstream++;
						continue;
					}
					else if(f_jvect[nodeinpath] == -1){
						break;
					}
				}
				//check for nearest label inside the path
				if(lenupstream >= lendownstream){
					labeltopred = -1;
					cntmajdwnstream += 1; //this flow path predicted a 1
				}
				else{
					labeltopred = 1;
					cntmajupstream += 1; //this flow path predicted a -1
				}


			}
			//Predict a/c to majority of flow paths
			if(cntmajupstream > cntmajdwnstream)
				labeltopred = 1;
			else
				labeltopred = -1;
		}
		
		
		//Update the new labels for the new graph
		//predlabelsNewGraph.insert(predlabelsNewGraph.begin()+j,labeltopred);
		predlabelsNewGraph[j] = labeltopred;
		//if(predlabelsNewGraph[j] == 0)
			//cout  << "0 inside new graph\n";
	}
}