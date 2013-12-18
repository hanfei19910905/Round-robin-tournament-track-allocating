#include "multi.hpp"
#include "single.hpp"
#include "format.hpp"
#include "op.hpp"
#include <iostream>
#include <vector>
using namespace std;
vector<vector<pair<int,int> > > ans;
vector<int> input;
int n,m;
#ifdef WINWTF
#include "sugar.hpp"
#include <windows.h>
DWORD WINAPI SingleThread(LPVOID lp){
    SINGLE::Solve(ans,m,input);
    return 0;
}
#endif
int main(){
        #ifdef WINWTF
            SUGAR::wtf();
        #endif
   		cin >> n >> m;
        input.resize(n);
        for(int i = 0; i < n; i++){
            scanf("%d",&input[i]);
        }
        #ifdef WINWTF
        HANDLE threadHandle = CreateThread(NULL,0,SingleThread,NULL,0,NULL);
        DWORD flag = WaitForSingleObject(threadHandle,10000);
        CloseHandle(threadHandle);
        if(flag == WAIT_FAILED || flag == WAIT_TIMEOUT){
            MULTI::Solve(ans,m,input);
        }
        #else 
        if(n==1) {
            SINGLE::Solve(ans,m,input);
        } else {
            MULTI::Solve(ans,m,input);
        }
        #endif
        FORMAT::Solve(ans);
        #ifdef OPHPP
		OP::Solve(ans,input);
        #else
        for(int i = 0; i < ans.size(); i++){
            for(int j = 0; j < ans[i].size(); j++){
                printf("%d,%d ",ans[i][j].first,ans[i][j].second);
            }
            puts("");
        }
        #endif
    
}
