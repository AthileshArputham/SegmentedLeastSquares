#include<bits/stdc++.h>
using namespace std;

class SegmentedLeastSquares{
	public:
		vector<double> OPT;
		double cost;
		int N;
		vector <double> x_sum,y_sum,xy_sum,xsqr_sum,ysqr_sum;
		vector<pair<double,double>> points;
		vector<vector<double>> error,a,b;
		vector<int> segments;
		vector<pair<pair<double,double>,pair<double,double>>> answer;
		
		SegmentedLeastSquares(int c){
			// cout<<"-----";
			cin>>N;
			int Ntemp = N;
			while(Ntemp--){
				double x;
				double y;
				cin>>x>>y;
				points.push_back({x,y});
			}
			for(int i = 0;i<N;i++){
				a.push_back(vector<double>());
				b.push_back(vector<double>());
				error.push_back(vector<double>());
				segments.push_back(0);
				for(int j = 0;j<N;j++){
					error[i].push_back(0);
					a[i].push_back(0);
					b[i].push_back(0);
				}
			}
			// error(N, vector<double> (N, 0));
			// segments(N,0);
			x_sum.push_back(0.0);
			y_sum.push_back(0.0);
			xy_sum.push_back(0.0);
			xsqr_sum.push_back(0.0);
			ysqr_sum.push_back(0.0);
			OPT.push_back(0.0);
			cost = c;
			sort(points.begin(),points.end());
			Precompute();
		}

		void Precompute(){
			// cout<<"-----------";
			for(int i = 0; i <N ;i++){
				x_sum.push_back(x_sum.back() + points[i].first);
				y_sum.push_back(y_sum.back() + points[i].second);
				xy_sum.push_back(xy_sum.back() + points[i].first * points[i].second);
				xsqr_sum.push_back(xsqr_sum.back() + points[i].first*points[i].first);
				ysqr_sum.push_back(ysqr_sum.back() + points[i].second*points[i].second);
			}
			x_sum.erase(x_sum.begin());
			y_sum.erase(y_sum.begin());
			xy_sum.erase(xy_sum.begin());
			xsqr_sum.erase(xsqr_sum.begin());
			ysqr_sum.erase(ysqr_sum.begin());
			computeError();
		}
		void computeError(){
			int i,j;
			// cout<<"----------------------";
			for(i = 0;i < N;i++){
				for(j = i + 1; j< N; j++){
					int n = j - i + 1;
					double xsum,ysum,xsqrsum,ysqrsum,xysum = 0;
					if(i == 0){
						 xsum = x_sum[j];
						 ysum = y_sum[j];
						 xsqrsum = xsqr_sum[j];
						 xysum = xy_sum[j]; 
						 ysqrsum = ysqr_sum[j];
					}
					else{
						xsum = x_sum[j] - x_sum[i-1];
						ysum = y_sum[j] - y_sum[i-1];
						xsqrsum = xsqr_sum[j] - xsqr_sum[i-1];
						xysum = xy_sum[j] - xy_sum[i-1];
						ysqrsum = ysqr_sum[j] - ysqr_sum[i-1];
					}
					

					a[i][j] = (n * xysum - xsum*ysum) / (n*xsqrsum - xsum*xsum);
					b[i][j] = (ysum - a[i][j]*xsum) / n;

					error[i][j] = ysqrsum - 2*a[i][j]*ysum - 2*b[i][j]*xysum + n*a[i][j]*a[i][j] + b[i][j]*b[i][j]*xsqrsum + 2*a[i][j]*b[i][j]*xsum;
					// cout<<error[i][j]<<endl;

				}
			}
			LeastSquares();
		}

		void LeastSquares(){
			int i,j;
			// cout<<endl<<"*****************";
			for(j = 0;j < N;j++){
				double minimum_cost = numeric_limits<double>::infinity();
				int start_point = 0;
				for(i = 1;i <= j;i++){
					// cout<<error[i][j]<<endl;
					double temp_cost = error[i][j] + OPT[i-1] + cost;
					if(temp_cost < minimum_cost){
						minimum_cost = temp_cost;
						start_point = i;
					}

				}
				OPT.push_back(minimum_cost);
				segments[j] = start_point;

			}
			// for(int k:segments){
			// 	cout<<k<<endl;
			// }
			// cout<<"----------------------------------------------"<<endl;
			get_line_segments();
		 }

		 void get_line_segments(){
		 	int pointer = N-1;
		 	while(pointer >= 0){
		 		int next_pointer = segments[pointer];
		 		if(next_pointer == pointer){
		 			answer.push_back({{points[next_pointer].first,points[next_pointer].second},{points[pointer-1].first,points[pointer-1].second}});
		 		}
		 		else{
		 			answer.push_back({{points[next_pointer].first,(b[next_pointer][pointer] + a[next_pointer][pointer]*points[next_pointer].first)},{points[pointer].first,(b[next_pointer][pointer] + a[next_pointer][pointer]*points[pointer].first)}});
		 		}
		 		pointer = next_pointer - 1;
		 	
		 }
		}

};

int main(int argc,char* argv[]){
	SegmentedLeastSquares test_obj(stoi(argv[1]));
	for(auto k : test_obj.answer){
		cout<<k.first.first<<" "<<k.first.second<<" "<<k.second.first<<" "<<k.second.second<<endl;
	}

	return 0;
}

