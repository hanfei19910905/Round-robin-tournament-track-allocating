#include<iostream>
#include<map>
#include<vector>
#include<cstdio>
using namespace std;
namespace OP{
    typedef pair<int,int> pii;
    // conf是冲突数，是需要返回的结果，team是当前队伍，mp是已经用了哪些东西的集合，t = 0表示team在前，否则team在后。
    inline void cal(int &conf,int team,map<int,int> &mp,int t){
        if(mp.find(team) == mp.end()){
            mp[team] = t;
            return ;
        }
        conf += (mp[team] == t);
        mp[team] = t;
    }
    // 检查数组v的冲突个数
    int chk(vector<pii>& v){
        int conf = 0;
        map<int,int> mp;
        for(int i = 0; i < v.size(); i++) if(v[i].first){
            cal(conf,v[i].first,mp,0);
            cal(conf,v[i].second,mp,1);
        }
        return conf;
    }
    // num是比赛排布方案，team是队伍分组
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
        // 输出方案，计算先后手
        vector<int> heavy = vector<int>(teamNum,0);
        vector<int> light = vector<int>(teamNum,0);
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
        // 计算分布率
        vector<vector<int> > hashTable = vector<vector<int> >(teamNum ,vector<int>(m,0));
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                int x = num[i][j].first;
                int y = num[i][j].second;
                hashTable[x][j] ++;
                hashTable[y][j] ++;
                heavy[x] ++;
                light[y] ++;
            }
        }
        for(int i = 1; i < teamNum;i++){
            printf("team #%d: ",i);
            for(int j = 0; j < m; j++){
                printf("%d ",hashTable[i][j]);
            }
            puts("");
        }
        // 统计深浅壶个数
        cout<<"heavy color: ";
        for(int i = 1; i < teamNum; i++) cout<< heavy[i]<<" ";cout<<endl;
        cout<<"light color: ";
        for(int i = 1; i < teamNum; i++) cout<< light[i]<<" ";cout<<endl;
        // 计算冲突率
        cout<<"conflict: ";
        for(int j = 0; j < m; j++){
            vector<pii> tmp;
            for(int i = 0; i < n; i++){
                tmp.push_back(num[i][j]);
            }
            cout<<chk(tmp)<<" ";
        }
        cout<<endl;
    }
};
