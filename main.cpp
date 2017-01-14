/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;


int main(int argc, const char* argv[])
{

#if _SIMULATOR_TEST_NORMAL == 1
	int Adj[6][6] = {{0,1,1,1,0,0},
	{1,0,1,0,1,0},
	{1,1,0,1,1,0},
	{1,0,1,0,1,1},
	{0,1,1,1,0,0},
	{0,0,0,1,0,0}};

	const int n = V;
	const int m = 18;
		
	//initial labelling
	int f_j[] = {-1,0,0,-1,1,0};
	int labnodes[] = {0,3,4};

	//TEST CODE TO SEE IF VECTOR WORKS - REDUNDANT MOVE IT UNDER SIMULATOR TEST
	vector<int> f_jvect(f_j, f_j + sizeof(f_j)/sizeof(f_j[0]));
	vector<int> labenodesvect(labnodes, labnodes + sizeof(labnodes)/sizeof(labnodes[0]));

	int lenf_j = sizeof(f_j)/sizeof(f_j[1]);
	int lenlabnodes = sizeof(labnodes)/sizeof(labnodes[1]);
	
	//TEST CODE TO SEE IF VECTOR WORKS
	int lenf_jvect = f_jvect.size();
	int lenlabnodesvect = labenodesvect.size();

	//Convert 2d matrix to much neater stl
	//std::vector<vector<int>> AdjMatVect(Adj, Adj+sizeof(Adj)/sizeof(Adj[0][0]));
	std::vector<vector<int>> AdjMat(n,std::vector<int>(n));
	std::vector<int>::const_iterator iter2;
	std::vector<vector<int>>::const_iterator iter1;
	cout << "Original Adjacency\n";
	for(int i = 0 ; i<n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			AdjMat[i][j] = Adj[i][j];
			cout << AdjMat[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
#elif _SIMULATOR_INTERTWINED_TEST == 1
	int Adj[7][7] = {{0,1,1,0,0,0,0},
	{1,0,1,1,0,0,0},
	{1,1,0,0,0,1,1},
	{0,1,0,0,0,1,0},
	{0,0,0,0,0,1,1},
	{0,0,1,1,1,0,1},
	{0,0,1,0,1,1,0}};

	const int n = V;
	const int m = 20;

	//initial labelling
	int f_j[] = {-1,0,0,0,1,0,0};
	int labnodes[] = {0,4};

	//TEST CODE TO SEE IF VECTOR WORKS - REDUNDANT MOVE IT UNDER SIMULATOR TEST
	vector<int> f_jvect(f_j, f_j + sizeof(f_j)/sizeof(f_j[0]));
	vector<int> labenodesvect(labnodes, labnodes + sizeof(labnodes)/sizeof(labnodes[0]));

	int lenf_j = sizeof(f_j)/sizeof(f_j[1]);
	int lenlabnodes = sizeof(labnodes)/sizeof(labnodes[1]);
	
	//TEST CODE TO SEE IF VECTOR WORKS
	int lenf_jvect = f_jvect.size();
	int lenlabnodesvect = labenodesvect.size();

	//Convert 2d matrix to much neater stl
	//std::vector<vector<int>> AdjMatVect(Adj, Adj+sizeof(Adj)/sizeof(Adj[0][0]));
	std::vector<vector<int>> AdjMat(n,std::vector<int>(n));
	std::vector<int>::const_iterator iter2;
	std::vector<vector<int>>::const_iterator iter1;
	cout << "Original Adjacency\n";
	for(int i = 0 ; i<n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			AdjMat[i][j] = Adj[i][j];
			cout << AdjMat[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
#elif _SIMULATOR_TEST_OCTOPUS == 1
	int Adj[12][12] = {{ 0 ,    1,     0,     0,     1,     0,     0,     1,     0,     0,     0,     1},
	{1,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0},
	{0,     1,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0},
	{0,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0},
	{1,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     0},
	{0,     0,     0,     0,     1,     0,     1,     0,     0,     0,     0,     0},
	{0,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     0},
	{1,     0,     0,     0,     0,     0,     0,     0,     1,     0,     0,     0},
	{0,     0,     0,     0,     0,     0,     0,     1,     0,     1,     0,     0},
	{0,     0,     0,     0,     0,     0,     0,     0,     1,     0,     1,     0},
	{0,     0,     0,     0,     0,     0,     0,     0,     0,     1,     0,     0},
	{1,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0}};

	//// Number of vertices  and edges in given graph
	const int n = V;
	const int  m = 11;

	//starting labels 
	int f_j[] = {0,0,0,-1,0,0,-1,0,0,0,0,1};
	int labnodes[] = {3,6,11};

	vector<int> f_jvect(f_j, f_j + sizeof(f_j)/sizeof(f_j[0]));
	vector<int> labenodesvect(labnodes, labnodes + sizeof(labnodes)/sizeof(labnodes[0]));

	int lenf_jvect = f_jvect.size();
	int lenlabnodesvect = labenodesvect.size();

	std::vector<vector<int>> AdjMat(n,std::vector<int>(n));
	std::vector<int>::const_iterator iter2;
	std::vector<vector<int>>::const_iterator iter1;
	cout << "Original Adjacency\n";
	for(int i = 0 ; i<n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			AdjMat[i][j] = Adj[i][j];
			cout << AdjMat[i][j];
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
#elif _SIMULATOR_TEST_LOOPS == 1 
	
	list< vector<int> > predallTrials;
	const int n = V; 

	//int datasetsizes[] = {15};
	//int datasetsizes[] = {11};
	int datasetsizes[] = {8};
	std::vector<vector<int>> AdjMat(V,std::vector<int>(V));
	
	//read the simualtion graph from the file
	readSimGraph(AdjMat, V);	// every graph is randomly selected data instances as
	
	//starting labels 
	//double f_j[] = {0,0,0,-1,0,0,-1,0,0,0,0,1};
	//int f_j[] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	//int labnodes[] = {0, 14};

	//testcase graphs
	//int f_j[] = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	//int labnodes[] = {0,10};

	int f_j[] = {-1, 0, 0, 0, 0, 0, 1, 0};
	int labnodes[] = {0,6};

	vector<int> f_jvect(f_j, f_j + sizeof(f_j)/sizeof(f_j[0]));
	vector<int> labenodesvect(labnodes, labnodes + sizeof(labnodes)/sizeof(labnodes[0]));

	int lenf_jvect = f_jvect.size();
	int lenlabnodesvect = labenodesvect.size();


#else _DATASETS_TESTS == 1
	vector<int> f_jvect;
	list< vector<int> > predallTrials;
	const int n = V; 
	const int trials = 10;
	//for the different trial graphs
	for(int trialind = 0; trialind < trials; ++trialind)
	{//Should be the for loop for reading the different trial graphs for dataset size n
	//Read from files
	int datasetsizes[] = {1196};
	std::vector<vector<int>> AdjMat(V,std::vector<int>(V));
	vector<int> labenodesvect;
	
	readDatasetGraph(AdjMat, V, trialind+1 );	// every graph is randomly selected data instances as
	readDatasetLabels(f_jvect, V, trialind+1);
	//change the labels that are 0 to -1
	for(int j = 0; j<f_jvect.size(); ++j)
	{
		if(f_jvect[j] == 0)
			f_jvect[j] = -1;
	}
	readDatasetLabelledNodes(labenodesvect,V, trialind+1);
	int lenf_jvect = f_jvect.size();
	int lenlabnodesvect = labenodesvect.size();
	
#endif

	//Flatten the graph based on initial labels
	adjmattype AdjLabFlatten(V,std::vector<int>(V));
	vector<int> supernodes;
	list< vector< int > > collaplist;
	collapseLabelledNodes(AdjMat, AdjLabFlatten, V, f_jvect, lenf_jvect, labenodesvect, lenlabnodesvect, supernodes, collaplist);
	
	//Keep track of what nodes got collpsed to
	mapstype mapcollap;
	mapstype::const_iterator itmap;
	int count = 0;
	for (int i = 0; i<V; ++i)
	{
		//Initialize the map
		mapcollap[i] = i;//initially no vertex is collpased so same as itself
	}
	trackCollapse( supernodes, collaplist, mapcollap );

	//Calculate max flow or s-t min cut	
	adjmattype fGraphvect(V, std::vector<int>(V));
	std::vector<int> parentorig;
//#if _SIMULATOR_TEST_NORMAL == 1
	//Find source and taget from the initial flattened graph
	int source = -1, target = -1;
	if( !supernodes.empty() )
	{
		// ideally there should be only two supernodes
		// check to see if value of source less than value of sink
		vector<int>::const_iterator iter = supernodes.begin();
		int label1 = f_jvect[*iter];
		int label2 = f_jvect[*(iter+1)];
		if (label1 < label2 )
		{
			source = *iter;
			target = *(iter+1);
		}
		else
		{
			source = *(iter+1);
			target = *(iter);
		}

	}
	//int source = 0;
	//int target = 4;
//#elif _SIMULATOR_TEST_OCTOPUS == 1
	//int source = 0;
	//int target = 3;
//#elif _DATASETS_TESTS == 1
	
//#endif
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	double maxflow = findMaxFlow(AdjLabFlatten,source,target,fGraphvect,parentorig);
	
	//Find the edge disjoint paths and contract graph
	std::vector<vector<int>> newAdjMat(n,std::vector<int>(n));
	////TODO remove initialization code below
	for(int i = 0 ; i<n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			newAdjMat[i][j] = 0; //Initializing
		}
	}

	list< vector<int> > flowpathlist;
	//collapse by acycgen
	
	contractGraphSCCBySccFirst(parentorig, maxflow, fGraphvect, source, target, AdjLabFlatten, V, newAdjMat, flowpathlist, mapcollap, labenodesvect);
	
	int *newAdjred = new int[n*n];
	std::fill(newAdjred, newAdjred + (n*n),  0);
		

    //the next section is redundant as only required for function compress ToDo remove
	int countrows = 0;
	int countcols = 1;
	int numnodes = 0;
	for(int i = 0; i<n; ++i)
	{
		for(int j = 0; j<n; ++j)
		{
			if(newAdjred != NULL && newAdjMat[i][j]!= 0)
			{
				newAdjred[i+j*n] = 1;
				newAdjred[j+i*n] = 1;
				countcols += 1;
				numnodes += 1;
			}
		}
		countrows = numnodes;
		countcols = countrows + 1;
	}
	
	int **compressAdj, map[n];
	//To keep track of mapping between original indices and new indices
	mapstype mapindexoldtonew;
	//Need to map to original vertices from the flattened graph for prediction 
	int newn = compress((int*)newAdjred, &compressAdj, map, n, mapindexoldtonew);

	//need to create new label vector for the labelling on the compressed graph
	vector<int> newlabels(newn);
	for(int i = 0; i < newn; ++i)
	{
		int origindex = map[i];
		newlabels[i] = f_jvect[origindex];
	}

	////Predicting unknown labels on the newn no of vertices
	vector<int> predLabelsWholeGraph = vector<int>(n) ;
	vector<int> predlabelsNewGraph = vector<int>(newn);
#if _BATCH_PREDICTION == 1
	
	#if _SIMULATOR_PREDICTION 1

		predictLabels(flowpathlist, mapindexoldtonew, newlabels, newn, predlabelsNewGraph, f_jvect);
		labelAllNodesFromCollapsed(predLabelsWholeGraph, predlabelsNewGraph, mapcollap, mapindexoldtonew);
		predallTrials.push_back(predLabelsWholeGraph);
	#elif _DATASETS_TESTS == 1

		predictLabels(flowpathlist, mapindexoldtonew, newlabels, newn, predlabelsNewGraph, f_jvect);
		labelAllNodesFromCollapsed(predLabelsWholeGraph, predlabelsNewGraph, mapcollap, mapindexoldtonew);
		predallTrials.push_back(predLabelsWholeGraph);
		
	} //Should be the end of for loop for the dataset size n for its 10 trials - 10 different graphs
	//Calculate accuracy and error
	double meanacc = 0.0, stddev = 0.0;
	char buffer[100];
	sprintf_s(buffer,"%s%d%s", "results", n, ".txt"); 
	averageResults(predallTrials, trials, f_jvect, meanacc, stddev, n, buffer);

	#endif
	

#endif
	cout << "done";
	std::getchar();
	return 0;
}

