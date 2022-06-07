/*
- Binary search
- printf/scanf are faster than cout/cin
*/ 

#include <iostream>
#include <algorithm>
using namespace std;

int32_t N; 
int32_t M;

void bs(int32_t tmpint, int32_t arr[])
{
    int32_t start = 0;
    int32_t end = N-1;
    int32_t mid = (end+start)/2;

    while (start <= end)
    {
        mid = (end+start)/2;
        if (arr[mid] == tmpint)
        {
            // cout << 1 << endl;
            printf("1\n");
            return;
        }
        else if (arr[mid] > tmpint)
        {   
            end = mid - 1;
        }        
        else if (arr[mid] < tmpint)
        {
            start = mid + 1;
        }   
    }
    if (start > end)
        // cout << 0 << endl;
        printf("0\n");
    else
        // cout << 1 << endl;
        printf("1\n");
}

int main(int argc, const char** argv)
{
    
    int32_t arr[100'001];
    int32_t tmpint; 

    // cin >> N ;
    scanf("%d",&N);
    for (int32_t ii = 0; ii < N; ++ii)    
    {
        // cin >> tmpint;
        scanf("%d",&tmpint);
        arr[ii] = tmpint;   
    }

    sort(arr, arr+N);
    
    // cin >> M ;
    scanf("%d",&M);
    for (int32_t jj = 0; jj < M; ++jj)
    {
        // cin >> tmpint;   
        scanf("%d",&tmpint);
        bs(tmpint, arr);         
    }
}