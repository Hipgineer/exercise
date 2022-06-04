#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    uint32_t targetLen;
    int32_t num=0;
    scanf("%d", &targetLen);

    for (int32_t ii = 7 ; ii >= 0; --ii)
        if ((targetLen >> ii) & 1) num++;
    printf("%d",num);
}