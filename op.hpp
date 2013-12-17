#include<iostream>
#include<vector>
#include<cstdio>
using namespace std;
namespace OP{
    typedef pair<int,int> pii;
    void Solve(vector<vector<pii> > num,vector<int> team){
        int n = num.size();
        int m = num[0].size();
        vector<int> even = vector<int>(10000,0);
        int teamNum = 1;
        for(int i = 0; i < team.size(); i++){
            for(int v = 0; v < team[i]; v++)
                if(0 == team[i] % 2 && 0 == v % 2){
                    even[teamNum + v] = 1;
                }
            teamNum += team[i];
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int x = num[i][j].first,
                y = num[i][j].second;
                if(0 == x || (even[min(x,y)] && abs(x - y) == 1)){
                    printf("%3d,%3d",x,y);
                } else if(0==abs(x-y)%2){
                    if(x > y) {
                        printf("*%2d,%3d",x,y);
                    } else {
                        printf("%3d,*%2d",x,y);
                    }
                } else {
                    if(x > y){
                        printf("%3d,*%2d",x,y);
                    } else {
                        printf("*%2d,%3d",x,y);
                    }
                }
                printf(" | ");
            }
            printf("\n");
        }
        even.clear();
        vector<vector<int> > hashTable = vector<vector<int> >(
        teamNum ,vector<int>(m,0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int x = num[i][j].first;
                int y = num[i][j].second;
                hashTable[x][j] ++;
                hashTable[y][j] ++;
            }
        }
        for(int i = 1; i < teamNum;i++){
            printf("team #%d: ",i);
            for(int j = 0; j < m; j++){
                printf("%d ",hashTable[i][j]);
            }
            puts("");
        }
    }
};
