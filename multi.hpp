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
typedef pair<int,int> pii;
int val[100],N,vis[100];
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
void allocat(int base,int n){
	vector<int> tmp;
	for(int i = 1; i<=n; i++) tmp.PB(i);
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
pii ans[10005][105];
const pii ZERO = make_pair(0,0);
int hash[105][105],now,col,SUM[105];
double dif[105];
bool cmp1(pii a,pii b){
	return (dif[a.first] + dif[a.second]) * (SUM[b.first] + SUM[b.second]) > (dif[b.first] + dif[b.second]) * (SUM[a.first] + SUM[a.second]);
}
double cal(int hash[],int k){
	double sum = 0,val = 0;
	for(int j = 0; j < k; j++)
		sum += hash[j];
	sum /= k;
	for(int j = 0; j < k; j++)
		val += pow(abs(hash[j] - sum),2);
	return val;
}
int diff(int hash[],int n){
	int mx = 0,mn = 1000000000;
	for(int i = 0; i < n;i++){
		if(hash[i] > mx) mx = hash[i];
		if(mn > hash[i]) mn = hash[i];
	} return mx - mn;
}
int last[105],row;
double factor = 0.3;
map<int,int> up[100];
int MAX(int col,int k,int n,bool flag){
	for(int i = 1; i <= n; i++){
		dif[i] = cal(hash[i],k);
	}
	if(ANS[row].size() == 0) row ++;
	vector<pii>& t = ANS[row];
	if(t.size()==0) return -2;
	sort(ALL(t),cmp1);
	vector<pii> :: iterator tmp,it=t.begin();
	int S=-1;
	for(;;it++){
		pii x = ZERO;
		for(; it != t.end(); it++){
			pii v = *it;
			if(!vis[v.first] && !vis[v.second]){
				x = v;
				tmp = it;
				break;
			}
		}
		if(x == ZERO) return -1;
		int a = x.first, b= x.second,s = -1;double mx = 1e20;
		for(int i = 0; i < k; i++) if(ans[col][i] == ZERO) {
			if((i == last[a] || i == last[b]) && k > 2) continue;
			hash[a][i]++;
			hash[b][i]++;
			double val = cal(hash[a],k) + cal(hash[b],k);
			if(up[i][a] == 1) val += factor;
			if(up[i][b] == 2) val += factor;
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
			up[s][a] = 1;
			up[s][b] = 2;
			return 0;
		}
	}
	return -1;
}
void solve(int k,int n){
	now = 0, col = 0;
	for(int i = 1; i <= n; i++)
		last[i] = k;
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
int Solve(char *__ans,int m,vector<int> input){
	int tst = input.size(),t = 0;N= 0;
	for(int i = 0; i < tst; i++){
		int value = input[i];
		allocat(N,value);
		N += value;
	}
	solve(m,N);
	for(int i = 0; i < col ; i++){
		for(int j = 0; j < m; j++)
			sprintf(__ans,"%d,%d ",ans[i][j].first,ans[i][j].second);
        sprintf(__ans,"\n");
	}
    return 1;
}
