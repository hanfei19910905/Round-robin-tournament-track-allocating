#include<iostream>
#include<map>
#include<vector>
#include<cstring>
#include<cstdlib>
using namespace std;
namespace FORMAT{
    typedef pair<int,int> pii;
    // heavy[i]是队伍i用了几次深壶
    int heavy[1005] = {0};
    int light[1005] = {0};
    int TeamNum,n,m;
    const int inf = 1e9;
    bool cmp(pii a,pii b){
        return a.first > b.first || (a.first == b.first && a.second < b.second);
    }
    //check是检查方案arr的冲突数，和冲突距离总和，冲突越少越好，距离越大越好。
    pii check(vector<pii>& arr){
        map<int,int> last,lastline;
        int ans = 0, value = 0;
        vector<int> heavyVec(heavy,heavy+TeamNum + 1);
        vector<int> lightVec(light,light+TeamNum + 1);
        for(int i = 0; i < arr.size(); i++){
            int x = arr[i].first;
            int y = arr[i].second;
            if(0 == x) continue;
            else if(last.find(x) == last.end()){
                last[x] = 0;
            } else if(1 == last[x]){
                last[x] = 0;
            } else {
                ans ++;
                if(lastline.find(x) != lastline.end()){
                    value += i - lastline[x];
                }
            }
            if(0 == y) continue;
            else if(last.find(y) == last.end()){
                last[y] = 1;
            } else if(0 == last[y]){
                last[y] = 1;
            } else {
                ans ++;
                if(lastline.find(y) != lastline.end()){
                    value += i - lastline[y];
                }
            }
            heavyVec[x] += 1;
            lightVec[y] += 1;
            lastline[x] = lastline[y] = i;
        }
        for(int i = 1; i <= TeamNum; i++)
            if(abs(heavyVec[i] - lightVec[i]) > 1)
                return pii(inf,value);
         return pii(ans,value);
        
    }
    // temp是当前搜索方案，array是当前最好结果，ans.first代表冲突个数，ans.second代表冲突的队伍的距离。
    void WorkDfs(int now,vector<pii>& temp,vector<pii>& array,pii& ans){
        if(now == n){
            pii temp_ans = check(temp);
            if(cmp(ans,temp_ans)){
                ans = temp_ans;
                array = temp;
            }
            return ;
        }
        swap(temp[now].first,temp[now].second);
        WorkDfs(now+1,temp,array,ans);
        if(temp[now].first == 0) {
            return ;
        }
        swap(temp[now].first,temp[now].second);
        WorkDfs(now+1,temp,array,ans);
    }
    // work返回值为0代表没有方案
    // 否则返回值为1, 方案记录在array中
    bool work(vector<pii>& array){
        vector<pii> temp(array.begin(), array.end());
        pii ans = pii(inf,0);
        WorkDfs(0,temp,array,ans);
        return ans.first != inf;
    }
    // 计算总队伍数，为了保证接口统一没有作为参数传进来。
    int GetTeamNum(vector<vector<pii> >& table){
        int ans = 0;
        for(int i = 0; i < table.size(); ++i)
            for(int j = 0; j < table[i].size(); ++j){
                ans = max(ans, table[i][j].first);
                ans = max(ans, table[i][j].second);
            }
        return ans;
    }
    int Solve(vector<vector<pii> >& table){
            TeamNum = GetTeamNum(table);
            memset(heavy,0,sizeof(heavy));
            memset(light,0,sizeof(light));
            n = table.size();
            m = table[0].size();
            vector<vector<int> > hashTbl = vector<vector<int> >(TeamNum + 1,vector<int>(m,0));
            // 计算分布率
            for(int i = 0; i < n; i ++){
                for(int j = 0; j < m; j++){
                    if(0 != table[i][j].first){
                        hashTbl[table[i][j].first][j] ++;
                        hashTbl[table[i][j].second][j] ++;
                    }}}
            // fail[i] = 1 代表赛道i没有合法深浅壶分布方案
            vector<int> fail = vector<int>(m,1);
            for(;;){
                bool flag = 0;
                for(int j = 0; j < m; j++) if(fail[j]){
                    vector<pii> column;
                    for(int i = 0; i < n; i++){
                        column.push_back(table[i][j]);
                    }
                    // 提取出一列，为数组column
                    if(work(column) == 0){
                        continue;
                    } else {
                        flag = 1;
                        fail[j] = 0;
                    }
                    for(int i = 0; i < n; i++){
                        table[i][j] = column[i];
                        heavy[column[i].first] += 1;
                        light[column[i].second] += 1;
                    }
                }
                if(!flag) break;
            }
    }
};
