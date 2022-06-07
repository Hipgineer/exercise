/*
- printf/scanf are faster than cout/cin
*/ 

#include <iostream>
#include <algorithm>
using namespace std;

int32_t N; 

int main(int argc, const char** argv)
{
    
    int32_t arr[1'001];
    int32_t tmpint; 

    // cin >> N ;
    scanf("%d",&N);
    for (int32_t ii = 0; ii < N; ++ii)    
    {
        scanf("%d",&tmpint);
        arr[ii] = tmpint;   
    }

    sort(arr, arr+N);
    
    for (int32_t ii = 0; ii < N; ++ii)    
    {
        printf("%d\n",arr[ii]);  
    }
}