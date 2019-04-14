#include<bits/stdc++.h>
using namespace std;

class SegmentedLeastSquares{
	public:
		double OPT[10000]={0};
		double cost;
		int N;
		vector <double> x_sum,y_sum,xy_sum,xsqr_sum,ysqr_sum;
		vector<pair<double,double>> points;
		vector<vector<double>> error,a,b;
		vector<int> segments;
		/*!
		* 'c' is the cost of using a new line to fit the data
		*/
		SegmentedLeastSquares(int c);
		/*! 
		* Function that returns pairs if points.
		* Here each pair denotes the end points of the lines used to fit the data
		*/
		pair<vector<pair<pair<double,double>,pair<double,double>>>,double> LeastSquares();
	private:
		/*! 
		* Function to precompute required values,and stores the following values x_sum,y_sum,xy_sum,xsqr_sum,ysqr_sum
		*/
		void Precompute();
		/*!
		* Function that computes and stores the error that every possible lines produces
		*/
		void computeError();
};