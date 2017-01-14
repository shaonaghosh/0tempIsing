/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include<stdio.h>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<sstream>
#include<iostream>
#include<stack>
#include<list>
#include<utility>
#include<vector>

using namespace std;


vector<int> findneighbours(int i, double labeli, double f_pred[], const int n, vector<int> allneigh);
int main(int argc, const char* argv[])
{
	
	//Test case with dummy nodes
	int Adj[15][15] = {{ 0 ,    1,     0,     0,     1,     0,     0,     1,     0,     0,     0,     1, 0 , 0, 0},
	{1,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0, 0, 0 ,0},
	{0,     1,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0, 0, 0, 0},
	{0,     0,     1,     0,     0,     0,     0,     0,     0,     0,     0,     0, 0, 0, 0},
	{1,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     0, 0, 0, 0},
	{0,     0,     0,     0,     1,     0,     1,     0,     0,     0,     0,     0, 1, 0, 0},
	{0,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     0, 0, 0, 0},
	{1,     0,     0,     0,     0,     0,     0,     0,     1,     0,     0,     0, 0, 0, 0},
	{0,     0,     0,     0,     0,     0,     0,     1,     0,     1,     0,     0, 0, 0, 1},
	{0,     0,     0,     0,     0,     0,     0,     0,     1,     0,     1,     0, 0, 0, 0},
	{0,     0,     0,     0,     0,     0,     0,     0,     0,     1,     0,     0, 0, 0, 0},
	{1,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 0, 0, 0},
	{0,     0,     0,     0,     0,     1,     0,     0,     0,     0,     0,     0, 0, 1, 0},
	{0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,     0, 1, 0, 0},
	{0,     0,     0,     0,     0,     0,     0,     0,     1,     0,     0,     0, 0, 0, 0}};
	
	

	//Test case with dummy edges
	const int n = 15;   
	const int m = 14;

	int l = 3;
	
	double f_pred[] = {0.5,0,-0.5,-1,0.5,0.5,0.5,0.5,0.5,0.5,0.5,1,0.7,0.8,0.6};
	

	//Need to decrease the indices by 1 when coming from matlab
	int labellednodes[] = {3, 11};
	std::vector<int> labnodesvect(labellednodes, labellednodes + sizeof labellednodes / sizeof labellednodes[0]);

	double labmat[n][n] =  {0};
	for( int i = 0; i < n; ++i )
	{
		for( int j = 0; j < n; ++j)
		{
			if(labmat != NULL)
			{
				if(Adj[i][j] != 0 )
				{
					labmat[i][j] = f_pred[j];
				}
			}
		}
	}
	for( int i = 0; i < n; ++i )
	{
		for( int j = 0; j < n; ++j)
		{
			cout << labmat[i][j] <<'\n';
		}
	}

	
	//List for keeping track of the collapsing to do
	std::list<vector<int>> collapsiblelist;
	std::list<vector<int>> parentsofcollaplist;
	std::list<vector<int>> neighofcollaplist;


	//For every node, find the neighbours with same label and collapse graph
	//create indices to loop in - will be the vertices labelled
	vector<int> indicestoloop;
	for(int ii = 0; ii < n; ++ii)
	{
		if(std::find(labnodesvect.begin(), labnodesvect.end(), ii) != labnodesvect.end())
			continue;
		indicestoloop.push_back(ii);
	}
	int counter = 0;
	while( indicestoloop.size() )
	{
		//Create the flattened graph
		//Visited nodes
		vector<int> visitedarr;
		vector<int> parentsarr;
		vector<int> newneigharr;
		vector<int> neighorig;

		////check if already present in 
		int predecessor = indicestoloop.front();

				
					//same labels start exploring neighbours depth first, new dfs stack for each i 
					stack<int> s;
					s.push(indicestoloop.front());
					while(s.empty() == false){
						//add starting node to stack
						int top = s.top();
						s.pop();
						
					//if( NULL != top ){
						//check if already visited if yes continue with others
						if( ( visitedarr.empty() == false ) && (std::find(visitedarr.begin(), visitedarr.end(), top) != visitedarr.end()))
								continue;
							//Get the neighbours of i 
						vector<int> allneigh;
						for (int jj = 0; jj < n; ++jj)	
						{
							allneigh.push_back(Adj[top][jj]);
						}
						double labeli = f_pred[top];
						neighorig = findneighbours(top, labeli, f_pred, n, allneigh);
						visitedarr.push_back(top);
						parentsarr.push_back(predecessor);

						//cout << "Traversed node  " << top << "\n";
																			
						std::vector<int>::const_iterator iterator;
						for (iterator = neighorig.begin(); iterator != neighorig.end(); ++iterator)
						{
							s.push(*iterator);
						}
						//update predecessor
						predecessor = top;
						//	}
						}


						//check which neighbours are found to be the same and flatten the graph already to avoid unecessary loops
						cout << "Node " << indicestoloop[counter];
						std::vector<int>::const_iterator iterator;
						for (iterator = visitedarr.begin(); iterator != visitedarr.end(); ++iterator)
						{
							cout << "-visited nodes" << *iterator << "\n";
							//find elements already collapsed and remove from outer iteration
							std::vector<int>::const_iterator iter = find(indicestoloop.begin(), indicestoloop.end(), *iterator);
							indicestoloop.erase(iter);
						}
						//Populate the lists
						collapsiblelist.push_back(visitedarr);
						parentsofcollaplist.push_back(parentsarr);

	}
	
	

	//Flatten the graph
	list<list<vector<int>>> neightotrack;
	list<list<vector<double>>> labneightotrack;
	std::list<vector<int>>::const_iterator iter;

	std::list<std::pair<int,int>> nodeidxreflist;
	std::list<vector<int>> collapsiblelistcopy(collapsiblelist.begin(), collapsiblelist.end());

	//the number of nodes in the new adjacency is the number of zones found, also added number of labelled nodes
	const int zones = collapsiblelist.size() + labnodesvect.size();
	
	//new adjacency
	int *newAdj = new int[zones*zones];
	double *newlab = new double[zones];
	std::fill(newAdj, newAdj + (zones*zones),  0);

	int countrows = 0;
	int countcols = 1;
	int numnodes = 0;
	for (iter = collapsiblelist.begin(); iter != collapsiblelist.end(); ++iter)
	{
		//increment no of nodes
		numnodes += 1;

		list<vector<int>> neighpernodexist;
		list<vector<double>> labneighpernodexist;
		
		std::vector<int>::const_iterator iter2;
		//Need to keep track of the neighbours of the nodes being collapsed   
		int sizecollapnodes = (*iter).size();
		if (sizecollapnodes > 1)
		{
			//Remove this collapsed nodes already dealt with from the original list
			collapsiblelistcopy.remove(*iter);
			//At least two neighbours with same labels, find neighbours of collapsible nodes
			for (iter2 = (*iter).begin()+1; iter2 != (*iter).end(); ++iter2)
			{
				
				//Find the neighbours of the second same labelled neighbour
				int nodeindex = *iter2;
				vector<int> neighnotsame;
				vector<double> labneighnotsame;

				//first insert the starting node
				std::vector<int>::const_iterator iter3 = (*iter).begin();
				neighnotsame.push_back(*iter3);
				labneighnotsame.push_back(f_pred[*iter3]);
				nodeidxreflist.push_back( make_pair(*iter3,countrows) ); 

					for(int j = 0; j < n; ++j)
					{
						if(Adj[nodeindex][j] != 0 )
						{
							//Should not be in the collapsible list but are connected to nodes in collapsible list
							if (std::find((*iter).begin(), (*iter).end(), j) == (*iter).end()) 
							{
							if(newAdj != NULL)
							{
								newAdj[countrows+countcols*zones] = 1;
								newAdj[countcols+countrows*zones] = 1;
								//countrows += 1;
								countcols += 1;
								numnodes += 1;
								nodeidxreflist.push_back( make_pair(j,countcols) ); 
							}	
							neighnotsame.push_back(j);
							labneighnotsame.push_back(f_pred[j]);
							}
							else
							{
								//For nodes not to be collapsed

							}
						}

					}
				neighpernodexist.push_back(neighnotsame);
				labneighpernodexist.push_back(labneighnotsame);
				//int index = std::distance(aVector.begin(), it);
				
				
			}
			//Connect to other nodes originally connected to that are not in the collapsible list
			for (int j = 0; j<n ; ++j)
			{
				//first insert the starting node
				std::vector<int>::const_iterator iter3 = (*iter).begin();
				if(Adj[*iter3][j] != 0)
				{
					//Not in the collapsible list of the starting node
					if (std::find((*iter).begin(), (*iter).end(), j) == (*iter).end()) 
					{
							if(newAdj != NULL)
							{
								newAdj[countrows+countcols*zones] = 1;
								newAdj[countcols+countrows*zones] = 1;
								//countrows += 1;
								countcols += 1;
								numnodes += 1;
								nodeidxreflist.push_back( make_pair(j,countcols) ); 
							}
					}
					
				}
				
			}
			neightotrack.push_back(neighpernodexist);
			labneightotrack.push_back(labneighpernodexist);

			//Add the nodes that will not be collapsed - TODO...basically need to join this with other main nodes in the collapsiblelist TODO check lists
		}
		
		//Update rows and columns
		countrows = numnodes;
		countcols = countrows + 1;

	}
	//Now deal with the ones that are not yet collapsed as loop before only deals with nodes to be collapsed
	// Now these non-collapsible nodes in all likeliness will be connected to non collapsible nodes or nodes just collapsed to main node
	std::list<vector<int>>::const_iterator iter3;
	for (iter3 = collapsiblelistcopy.begin(); iter3 != collapsiblelistcopy.end(); ++iter3)
	{
		int curridxfornodei = -1;
		int curridxfornodej = -1;
		std::vector<int>::const_iterator itervect = *iter3;
		vector<int> nodeidx = iter.begin();
		for(int j = 0; j < n; ++j)
		{
			if(Adj[nodeidx][j] != 0)
			{
				//Find the new index for *iter and j if exists else create new index and update adjacency matrix
				std::list<std::pair<int,int>>::const_iterator iter2 = nodeidxreflist.begin();
				//for(;iter2 != nodeidxreflist.end();++iter2) 
				auto pos = std::find_if(nodeidxreflist.begin(), nodeidxreflist.end(),
                        [nodeidx](std::pair<int, int> const &b) { 
                            return b.first == *iter; 
                        });
				
			  
			   curridxfornodei  = pos.second; 
			   auto pos2 = std::find_if(nodeidxreflist.begin(), nodeidxreflist.end(),
                        [j](std::pair<int, int> const &b) { 
                            return b.first == value; 
                        });
			   curridxfornodej = pos2.second;

			   if(curridxfornodei!=-1 && curridxfornodej !=-1)
			   {
				   //Already exists in the new adjacenecy matrix - either attached to a non-collapsible node or a node that has been collapsed
			   }
			   else if (curridxfornodej == -1 && curridxfornodei != -1)
			   {
				   //Node j not present so create new index and update new adjacency matrix
				   newAdj[curridxfornodei+countcols*zones] = 1;
				   newAdj[countcols+curridxfornodei*zones] = 1;
				   numnodes += 1;
				   countcols += 1;
				   nodeidxreflist.push_back( make_pair(j,countcols) ); 


			   }
			   else if (curridxfornodei == -1 && curridxfornodej != -1)
			   {
				   //Node j not present so create new index and update new adjacency matrix
				   newAdj[countcols+curridxfornodej*zones] = 1;
				   newAdj[curridxfornodej+countcols*zones] = 1;
				   numnodes += 1;
				   countcols += 1;
				   nodeidxreflist.push_back( make_pair(*iter,countcols) ); 
			   }
			   else
			   {
				   //both new nodes
				   newAdj[countrows+countcols*zones] = 1;
				   newAdj[countcols+countrows*zones] = 1;
				   numnodes += 1;
				   countcols += 1;
				   nodeidxreflist.push_back( make_pair(*iter,countrows) ); 
				   nodeidxreflist.push_back( make_pair(j,countcols) ); 
				   countrows = numnodes;
				   countcols = countrows +1;
			   }
			
			}
		}

	}
	////Add the original labelled nodes
	int ii = zones - labnodesvect.size();
	for( int it = ii; it < zones; ++it)
	{
		newAdj[countrows+countcols*zones] = 1;
		newAdj[countcols+countrows*zones] = 1;
	}


	//Display the adjacenecy
	for (int i  = 0 ; i < zones; ++i)
	{
		for( int j = 0; j < zones; ++j)
		{
			cout << newAdj[i+j*zones];
			cout << " ";
		}
		cout << endl;
	}

	std::getchar();
	return 0;
}
template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
    almost_equal(T x, T y, int ulp)
{
    // the machine epsilon has to be scaled to the magnitude of the larger value
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::abs(x-y) <=   std::numeric_limits<T>::epsilon()
                            * std::max(std::abs(x), std::abs(y))
                            * ulp;
}
vector<int> findneighbours(int i, double labeli, double f_pred[], const int n, vector<int> allneigh)
{
	vector<int> samelabneigh = vector<int>();
	//find neighbours of i
	std::vector<int>::const_iterator iterator;
	int count = 0;
    for (iterator = allneigh.begin(); iterator != allneigh.end(); ++iterator)
	{
			if(*iterator != 0)
			{
				double labelj = f_pred[count];
				//compare to see if same labels
				if(almost_equal(labeli, labelj, 4))//last argument is the precision
				{
					samelabneigh.push_back(count);
				}
			}
			count++;
	}

	return samelabneigh;
	
}

