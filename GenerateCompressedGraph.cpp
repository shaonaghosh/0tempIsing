/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;
//function to preserve the mapping - from new indexes in new adjacency matrix to old indexes in old adjacency matrix
//expects input the adjacency matrix with only the path  nodes as nodes having edge between them
int compress(int *in, int ***out, int map[], int n, mapstype& oldtonewmap){

	int i, j, k = 0;
	/* First find the mapping */
	for (i = 0; i < n; i++){
		bool skip = true;
		for (j = 0; j < n; j++){
			if (*(in + i*n + j) != 0 || *(in + j*n + i) != 0){
				skip = false;
				break;
			}
			else
				oldtonewmap[i] = -1; //indicates that these indices not present in collpased graph(collapsed vertex) would also mean
									 //that they remain same as original indices
		}
		if (!skip){
			map[k] = i;
			oldtonewmap[i] = k;    //current indices present in graph
			k++; 
		}
	}
	/* k is the new size */
	int new_n = k;

	/* Allocate memory for new adjacency matrix */
	*out = new int*[new_n];

	/* Use mapping function to copy only non-zero edges*/
	for (i = 0; i < new_n; i++){
		(*out)[i] = new int[new_n];
		for (j = 0; j < new_n; j++){
			(*out)[i][j] = *(in + map[i] * n + map[j]);
		}

	}

	return new_n;
}
