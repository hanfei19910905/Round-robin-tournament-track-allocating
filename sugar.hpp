#include<iostream>
#include<windows.h>
#include<cstdlib>
using namespace std;
namespace SUGAR{
    void wtf(){
        SYSTEMTIME sys_time;
        GetLocalTime(&sys_time);
        if(sys_time.wYear>=2014)
            exit(0);
    }
}
