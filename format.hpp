#include<iostream>
using namespace std;
namespace FORMAT{
    int Solver(vector<vector<pii> > table,int teamNum){
            int n = num.size();
            int m = num[0].size();
            vector<vector<int> > hashTbl = vector<teamNum,vector<m,0> >;
            vector<int> even = vector<n+1,0>;
            for(int i = 0; i < n; i ++){
                for(int j = 0; j < m; j++){
                    if(0 != table[i][j].first){
                        hashTbl[table[i][j].first][j] ++;
                        hashTbl[table[i][j].second][j] ++;
                    }}}
    }
};
