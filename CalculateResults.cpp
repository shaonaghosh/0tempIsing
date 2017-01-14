/*******************************************************************************************************
//Author: Shaona Ghosh
/*******************************************************************************************************/
#include"Misc.h"

using namespace std;
//calculate average results
void averageResults(const list< vector< int > > predLabelsAlltrials, const int trials, const vector< int > truelabels, double& meanacc, double& stddevacc, const int n, string filename)
{
	list< vector<int> >::const_iterator trialprediter;
	vector<int>::const_iterator predlabiter;
	vector<int>::const_iterator truelabiter;
	vector<double> meanresult;
	vector<double> sdevresult;

	//iterate through the different trials to calculate error per trial for this dataset size
	for(trialprediter = predLabelsAlltrials.begin(); trialprediter != predLabelsAlltrials.end(); ++trialprediter)
	{
		int fp = 0, fn = 0, tp = 0, tn = 0;
		double accuracy;
		double error;
		
		vector< int > predictions = *trialprediter;
		for(truelabiter = truelabels.begin(), predlabiter = predictions.begin(); truelabiter != truelabels.end(), predlabiter != predictions.end(); ++predlabiter, ++truelabiter)
		{
			int predlab = *predlabiter;
			int truelab = *truelabiter;
			if( 0 == predlab ){
				cout << "No prediction" << endl;
				assert(predlab != 0);
			}
			if( predlab == truelab){

				if(predlab == 1)
					tp++;
				else 
					tn++;
			}
			else{
				if( predlab < truelab )
					fn++;
				else if( predlab > truelab )
					fp++;
			}
		}
		accuracy = (double)(tp+tn)/n;
		error =(double)(fp+fn)/(double)(tp+tn+fp+fn);	 
		meanresult.push_back(accuracy);
		
	}
	//calculate the mean and sdev
	meanacc = std::accumulate(all(meanresult), (double)0.0);
	meanacc /= trials;
	std::vector<double> diff(trials);
	std::transform(meanresult.begin(), meanresult.end(), diff.begin(),
               std::bind2nd(std::minus<double>(), meanacc));
	double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
	stddevacc = std::sqrt(sq_sum / trials);
	//write this result to file
	ofstream fileid;
	fileid.open (filename);
	fileid << meanacc << endl;
	fileid << stddevacc << endl;
	fileid.close();
	
}