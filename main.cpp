#include<bits/stdc++.h>
#include "SegmentedLeastSquares.h"
using namespace std;

int main(int argc,char* argv[]){
	SegmentedLeastSquares test_obj(stoi(argv[1]));
	pair<vector<pair<pair<double,double>,pair<double,double>>>,double> answer = test_obj.LeastSquares();
	for(auto k : answer.first){
		cout<<k.first.first<<" "<<k.first.second<<" "<<k.second.first<<" "<<k.second.second<<endl;
	}
	cout<<answer.second<<endl;
	// cout<<test_obj.OPT.back();

	return 0;
}
