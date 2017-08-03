#include <iostream>
#include"cstdio"
using namespace std;

int main()
{
    int x;
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&x);
        if ( x & 1 ) printf("1\n");
        else printf("0\n");
    }
    return 0;
}
