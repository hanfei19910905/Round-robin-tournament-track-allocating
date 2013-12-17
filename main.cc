#include "multi.hpp"
#include "single.hpp"
#include "format.hpp"
#include<iostream>
#include<vector>
using namespace std;
vector<int> input;
int main(){
    int n,m;
    while(cin >> n >> m){
        vector<vector<pair<int,int> > > ans;
        input.resize(n);
        for(int i = 0; i < n; i++)
            scanf("%d",&input[i]);
        if(n==1) {
            SINGLE::Solve(ans,m,input);
        } else {
            MULTI::Solve(ans,m,input);
        }
        FORMAT::Solve(ans);
        for(int i = 0; i < ans.size(); i++){
            for(int j = 0; j < ans[i].size(); j++){
                cout<<ans[i][j].first<<","<<ans[i][j].second<<" ";
            }
            cout<<endl;
        }
    }
    
}
