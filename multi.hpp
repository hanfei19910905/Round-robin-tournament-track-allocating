#include<iostream>
#include<map>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<queue>
#include<vector>
#include<cassert>
#include<algorithm>
#include<set>
using namespace std;
#define ALL(a) a.begin(),a.end()
#define PB(a) push_back(a)
namespace MULTI{
    typedef pair<int,int> pii;
    // 队伍数量为8的特殊考虑，这是一个三维数组
    int spj[8][4][2] = {
        {{1,2},{3,4},{5,6},{7,8}},
        {{5,3},{1,7},{2,8},{6,4}},
        {{1,4},{6,2},{7,3},{5,8}},
        {{2,7},{1,8},{4,5},{3,6}},
        {{4,8},{6,7},{2,3},{1,5}},
        {{5,7},{3,8},{1,6},{2,4}},
        {{6,8},{2,5},{4,7},{1,3}}
    };
    vector<pii> ANS[105];
    // base是已经确定了多少个队伍，n是当前组的队伍数
    void allocat(int base,int n){
        if(n == 8) {
            for(int i = 0; i < n-1; i++)
                for(int j = 0; j < n/2; j++){
                    int x = spj[i][j][0];
                    int y = spj[i][j][1];
                    if(x > y) swap(x,y);
                    if((y - x) % 2 == 0) swap(x,y);
                    ANS[i].PB(make_pair(x+base,y+base));
                }
            return ;
        }
        // 固定轮转法
        vector<int> tmp;
        for(int i = 1; i<=n; i++) tmp.PB(i);
        if(n&1) {tmp.PB(0);n++;}
        for(int i =0 ; i <n-1;i++){
            for(int j = 0; j < n/2; j++){
                int x = tmp[j] + base, y = tmp[n-j-1] + base;
                if(x > y) swap(x,y);
                if(x == base) continue;
                if((y - x) % 2 == 0) swap(x,y);
                ANS[i].PB(make_pair(x,y));
            }
            int val = tmp.back();
            tmp.insert(tmp.begin()+1,val);
            tmp.erase(tmp.end()-1);
        }
    }
    // ans是最终结果
    pii ans[10005][105];
    const pii ZERO = make_pair(0,0);
    // hash为分布率
    int hash[105][105],SUM[105];
    double dif[105];
    // 按照 方差/出现次数 排序
    bool cmp1(pii a,pii b){
        return (dif[a.first] + dif[a.second]) * (SUM[b.first] + SUM[b.second]) > 
               (dif[b.first] + dif[b.second]) * (SUM[a.first] + SUM[a.second]);
    }
    // cal函数的作用是计算hash数组的方差
    double cal(int hash[],int k){
        double sum = 0,val = 0;
        for(int j = 0; j < k; j++)
            sum += hash[j];
        sum /= k;
        for(int j = 0; j < k; j++)
            val += pow(abs(hash[j] - sum),2);
        return val;
    }
    // diff函数的作用是计算分布率最大最小值之差。
    int diff(int hash[],int n){
        int mx = 0,mn = 1000000000;
        for(int i = 0; i < n;i++){
            if(hash[i] > mx) mx = hash[i];
            if(mn > hash[i]) mn = hash[i];
        } return mx - mn;
    }
    // row表示当前处理到了哪个轮次,last[i]代表队伍i上次在哪个赛道出现。
    int last[105],row;
    // vis代表当前轮次中是否被访问过
    int vis[100];
    //为某个队伍在论次col贪心选择一个赛道
    // flag是，按照“均匀分布”的策略是否能找到方案的一个标记
    // k是赛道数，n是队伍总数
    int MAX(int col,int k,int n,bool flag){
        for(int i = 1; i <= n; i++){
            dif[i] = cal(hash[i],k);
        }
        if(ANS[row].size() == 0) row ++;
        // t是当前轮次数组
        vector<pii>& t = ANS[row];
        if(t.size()==0) return -2;
        sort(ALL(t),cmp1);
        vector<pii> :: iterator tmp,it=t.begin();
        for(;;it++){
            // x是确定要选择的比赛
            pii x = ZERO;
            // 选择一场合法的比赛
            for(; it != t.end(); it++){
                pii v = *it;
                if(!vis[v.first] && !vis[v.second]){
                    x = v;
                    tmp = it;
                    break;
                }
            }
            if(x == ZERO) return -1;
            // s是为x分配的赛道
            int a = x.first, b= x.second,s = -1;double mx = 1e20;
            for(int i = 0; i < k; i++) if(ans[col][i] == ZERO) {
                if((i == last[a] || i == last[b]) && k > 2) continue;
                hash[a][i]++;
                hash[b][i]++;
                double val = cal(hash[a],k) + cal(hash[b],k);
                if(diff(hash[a],k)< 10 || diff(hash[b],k)<10 || !flag)
                    if( val < mx){mx = val; s = i;}
                hash[a][i]--;
                hash[b][i]--;
            }
            if(s!=-1){
                ans[col][s] = x;
                hash[a][s] ++;
                hash[b][s] ++;
                SUM[a]++;
                SUM[b]++;
                last[a] = last[b] = s;
                t.erase(tmp);
                vis[a] = 1; vis[b] = 1;
                return 0;
            }
        }
        return -1;
    }
    // col代表选到了第几个论次
    int col = 0;
    // k是赛道数，n是队伍数
    void solve(int k,int n){
        for(int i = 1; i <= n; i++)
            last[i] = k;
        // flag是，按照“均匀分布”的策略是否能找到方案的一个标记
        bool flag = 1;
        for(int _=0;_<105;_++){
            memset(vis,0,sizeof(vis));
            for(int i = 0; i < k; i++)
                ans[col][i] = ZERO;
            int a;
            for(int i=0; i < k; i++){
                 a = MAX(col,k,n,flag);
                if(a == -1 || a == -2) break;
            }
            bool tmp = 0;
            for(int i = 0; i < k; i++){
                pii x = ans[col][i];
                if(x!= ZERO) tmp = 1;
            }
            if(tmp) col ++;
            else {flag = 0;}
            if(a == -2) break;
        }
    }
    int Solve(vector<vector<pii> >& __ans,int m,vector<int> input){
        int tst = input.size(),t = 0,N= 0;
        for(int i = 0; i < tst; i++){
            int value = input[i];
            allocat(N,value);
            N += value;
        }
        solve(m,N);
        __ans.resize(col);
        for(int i = 0; i < col; i++){
            for(int j = 0; j < m; j++){
                __ans[i].push_back(ans[i][j]);
            }
        }
        return 1;
    }
};
