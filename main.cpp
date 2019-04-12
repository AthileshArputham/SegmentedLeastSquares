#include<bits/stdc++.h>
#include "SegmentedLeastSquares.h"
using namespace std;

int main(int argc,char* argv[]){
	SegmentedLeastSquares test_obj(stoi(argv[1]));
	vector<pair<pair<double,double>,pair<double,double>>> answer = test_obj.LeastSquares();
	for(auto k : answer){
		cout<<k.first.first<<" "<<k.first.second<<" "<<k.second.first<<" "<<k.second.second<<endl;
	}
	// cout<<test_obj.OPT.back();

	return 0;
}
