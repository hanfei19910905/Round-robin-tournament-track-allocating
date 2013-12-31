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
#ifndef POSIX
#include "sugar.hpp"
#include <windows.h>
DWORD WINAPI SingleThread(LPVOID lp){
    SINGLE::Solve(ans,m,input);
    return 0;
}
#endif
int main(){
        freopen("out.txt","w",stdout);
        // 宏都不用管
        #ifndef POSIX 
        	/*
        	SUGAR是的功能判断系统时间是否小于2014年
        	*/
            SUGAR::wtf();
        #endif
   		// 这部分是读入数据，存放在数组input中
   		cin >> n >> m;
        input.resize(n);
        for(int i = 0; i < n; i++){
            scanf("%d",&input[i]);
        }

        #ifndef POSIX
        // 这部分是先让单组程序跑数据，超过了10秒就让多组跑
        HANDLE threadHandle = CreateThread(NULL,0,SingleThread,NULL,0,NULL);
        DWORD flag = WaitForSingleObject(threadHandle,10000);
        CloseHandle(threadHandle);
        if(flag == WAIT_FAILED || flag == WAIT_TIMEOUT){
            MULTI::Solve(ans,m,input);
        }
        // 下面的不用管
        #else 
        if(n==1) {
            SINGLE::Solve(ans,m,input);
        } else {
            MULTI::Solve(ans,m,input);
        }
        #endif
        // FORMAT::Solve是排布深浅壶
        FORMAT::Solve(ans);
        // 这个是输出调试结果，比如赛队的分布情况等等。
        // 还有先后手的逻辑也在这里面。
		OP::Solve(ans,input);
}
