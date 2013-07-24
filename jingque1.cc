#include<iostream>
#include<cmath>
#include<cstring>
#include<cstdio>
#include<vector>
#include<cassert>
#include<algorithm>
using namespace std;
#define ALL(a) a.begin(),a.end()
#define PB(a) push_back(a)
typedef pair<int,int> pii;
const int N = 105;
const pii zero = make_pair(0,0);
int val[N],vis[N];
vector<pii> ANS[N];
int len = 0;
int spj[8][4][2] = {
	{{1,2},{3,4},{5,6},{7,8}},
	{{5,3},{1,7},{2,8},{6,4}},
	{{1,4},{6,2},{7,3},{5,8}},
	{{2,7},{1,8},{4,5},{3,6}},
	{{4,8},{6,7},{2,3},{1,5}},
	{{5,7},{3,8},{1,6},{2,4}},
	{{6,8},{2,5},{4,7},{1,3}}
};
bool tmp[105], odd[105];
void allocat(int base,int n){
	for(int i = 1; i <= n; i++){
		tmp[i + base] = n&1;
		odd[i + base] = i&1;
	}
	vector<int> tmp;
	for(int i = 1; i<=n; i++) tmp.PB(i);
	int maxn = n&1 ? n : n-1;
	if(maxn > len) len = maxn;

	if(n == 8) {
		for(int i = 0; i < n-1; i++)
			for(int j = 0; j < n/2; j++){
				int x = spj[i][j][0];
				int y = spj[i][j][1];
				if(x > y) swap(x,y);
//				if((y - x) % 2 == 0) swap(x,y);
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
//			if((y - x) % 2 == 0) swap(x,y);
			ANS[i].PB(make_pair(x,y));
		}
		int val = tmp.back();
		tmp.insert(tmp.begin()+1,val);
		tmp.erase(tmp.end()-1);
//		for(int i = 0; i < n; i++) cout<< tmp[i]<<" ";cout<<endl;
	}
}
int diff,coln,rown;
int hash[N][N];
//bool _hash[N][N][N];
int _vis[N][N];
pii ans[N][N];
pii last_ans[N][N];
int last[N],use[N];
bool init(){
	memset(last,-1,sizeof(last));
	memset(hash,0,sizeof(hash));
	memset(use,0,sizeof(use));
	memset(_vis,0,sizeof(_vis));
	for(int i = 0; i <= rown; i++)
		for(int j = 0; j < coln; j++)
			ans[i][j] = zero;
	return 1;
}
bool conflict(pii x,int a,int b){
	if(x == zero) return 0;
	int c = x.first, d = x.second;
	return a == c || a == d || c == b || b == d;
}
int differ(int hash[N]){
	int mx = -1, mn = coln+1;
	for(int i = 0; i < coln; i++){
		if(mn > hash[i]) mn = hash[i];
		if(mx < hash[i]) mx = hash[i];
	}
	return mx - mn;
}
int chk_zero(int hash[N]){
	int ans = 0;
	for(int i = 0; i < coln; i++)
		ans += hash[i] == 0;
	return ans;
}
int cntn,tmpn,TMP,best,EPS,flag,lim,base;
int conf[100] ,myconf[100];
void dfs(int x,int y,int c){
	if(flag) return ;
	pii temp[N];
	int expt = c / tmpn;
	int sum = 0;
	for(int i = 1; i <= cntn; i++)
		sum += differ(hash[i]);
	if(sum > TMP+EPS) return;
//	if(sum > best) return ;
	if(y == ANS[x].size()) x ++, y = 0;
	if(x == len) {
		if(sum == TMP) {
			flag = 1;
		}
		if(sum < best ) {
			for(int i = 1; i <= base; i++)
				if(chk_zero(hash[i]) > 1)
					return ;
//			cout<<c<<endl;
			best = sum;
			memcpy(last_ans,ans,sizeof(ans));
			memcpy(myconf,conf,sizeof(conf));
		}
		return;
	}
//	cout<<"x,y: "<<x<<" "<<y<<endl;
	pii p = ANS[x][y];
	int a =p.first, b = p.second;
//	cout<<"a,b: "<<a<<" "<<b<<endl;
	for(int i =  0; i < coln; i++)
		temp[i] = make_pair(use[i],i);
	sort(temp,temp+coln);
	for(int  q = 0; q < coln; q++){
		int j = temp[q].second;
		hash[a][j]++;
		hash[b][j]++;
		use[j] ++;
		int dif = coln <= 4 ? 3 : 2;
		if(differ(hash[a]) <= dif && differ(hash[b]) <= dif) {
			int i = expt,cost = 0;
				if(ans[i][j] == zero && !_vis[a][i] && !_vis[b][i]) 
				if(coln < 3 || i == 0 || !conflict(ans[i-1][j],a,b))
					
					{
					/*
					for(int row = i - 1; row >= 0; row --) if(ans[row][j].first == a){
						cost ++;
						break;
					} else if(ans[row][j].second == a) break;
					
					for(int row = i - 1; row >= 0; row --) if(ans[row][j].second == b){
						cost ++;
						break;
					} else if(ans[row][j].first == a) break;
					if(cost + conf[j] > lim ) continue;
					*/
					_vis[a][i] = 1;
					_vis[b][i] = 1;
					ans[i][j] = p;
				//	conf[j] += cost;
					dfs(x,y+1,c+1);
					if(flag) return ;
				//	conf[j] -= cost;
					_vis[a][i] = 0;
					_vis[b][i] = 0;
					ans[i][j] = zero;
					}
		}
		use[j]--;
		hash[a][j]--;
		hash[b][j]--;
	}
//	cout<<x<<" "<<y<<" fail\n";
}
int color[105][105],lastc[105];
int main(){
//    freopen("out.txt","w",stdout);
	int tst,t = 0,myn = 0;
	base = 0;
	cin >> tst >> coln;
	for(int i = 0; i < tst; i++){
		int value;
		cin >> value;
		cout<< value<<" ";
		myn += value/2;
		allocat(base,value);
		base += value;
	}
	cout<<endl;
	cntn = base;
	int sum = 0;
	for(int i = 0; i < len; i++) sum += ANS[i].size();
	tmpn = min(coln,myn);
	rown = sum / tmpn + !!(sum % tmpn);
	TMP = !!((cntn-1) % coln) * rown;
//	cout<<"TMP: "<<TMP<<endl;
	bool myflag = 0;
	for( EPS = 2;; EPS++){
//		for( lim = 0; lim <= 10; lim ++){
//			cout<<EPS<<" "<<lim<<endl;
			memset(conf,0,sizeof(conf));
			flag = 0;
			init();
			if(!myflag) best = 10000;
			dfs(0,0,0);
			if(myflag) break;
			if(best != 10000) {
				//cout<<best<<" "<<TMP<<endl;
				if(flag || best == TMP) break;
				else myflag = 1;
		};
//	}
//	if(myflag || flag || best == TMP) break;
	}
//	cout<<"BEST: "<<best<<endl;
	for(int i = 0; i < rown; i++){
		for(int j = 0; j < coln; j++){
			printf("%d,%d ",last_ans[i][j].first,last_ans[i][j].second);
		}
		cout<< endl;
	}
//	for(int i = 0; i < coln; i++) cout<< myconf[i]<<" ";cout<<endl;
}
