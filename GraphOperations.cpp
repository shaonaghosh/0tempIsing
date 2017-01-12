//#include"Utility.h"
//#include<iostream>
//#include<list>
//#include<algorithm>
//#include<stack>
//#include<string>
//#include<vector>
//
//using namespace std;
//
//GraphOperations::GraphOperations(int n, int *Adj, double *f_j)
//{
//	novertices = n;
//	m_Adj = Adj;
//	m_fj = f_j; 
//
//}
//
//void GraphOperations::FlattenSameLabels()
//{
//
//	for(int i = 0; i < novertices; ++i)
//	{
//		//Create the flattened graph
//		//Visited nodes
//		vector<int> visitedarr;
//		vector<int> parentsarr;
//		vector<int> newneigharr;
//		vector<int> neighorig;
//
//		
//		int predecessor = i;
//
//
//		//same labels start exploring neighbours depth first, new dfs stack for each i 
//		stack<int> s;
//		s.push(i);
//		while(s.empty() == false){
//			//add starting node to stack
//			int top = s.top();
//			s.pop();
//
//			//if( NULL != top ){
//			//check if already visited if yes continue with others
//			if( ( visitedarr.empty() == false ) && (std::find(visitedarr.begin(), visitedarr.end(), top) != visitedarr.end()))
//				continue;
//			//Get the neighbours of i 
//			vector<int> allneigh;
//			for (int jj = 0; jj < n; ++jj)
//			{
//				allneigh.push_back(Adj[top][jj]);
//			}
//			double labeli = f_pred[top];
//			neighorig = findneighbours(top, labeli, f_pred, n, allneigh);
//			visitedarr.push_back(top);
//			parentsarr.push_back(predecessor);
//
//			//cout << "Traversed node  " << top << "\n";
//
//			std::vector<int>::const_iterator iterator;
//			for (iterator = neighorig.begin(); iterator != neighorig.end(); ++iterator)
//			{
//				s.push(*iterator);
//			}
//			//update predecessor
//			predecessor = top;
//			//	}
//		}
//
//
//		//check which neighbours are found to be the same and flatten the graph already to avoid unecessary loops
//		cout << "Node " << indicestoloop[counter];
//		std::vector<int>::const_iterator iterator;
//		for (iterator = visitedarr.begin(); iterator != visitedarr.end(); ++iterator)
//		{
//			cout << "-visited nodes" << *iterator << "\n";
//			//find elements already collapsed and remove from outer iteration
//			std::vector<int>::const_iterator iter = find(indicestoloop.begin(), indicestoloop.end(), *iterator);
//			indicestoloop.erase(iter);
//		}
//		//Populate the lists
//		collapsiblelist.push_back(visitedarr);
//		parentsofcollaplist.push_back(parentsarr);
//
//	}
//
//}
