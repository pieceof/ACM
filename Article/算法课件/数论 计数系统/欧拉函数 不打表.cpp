#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
using namespace std;


int euler_phi(int n)
{
    int m = floor(sqrt(n+0.5));
    int ans = n;
    for(int i = 2; i <= m; i++) if(n%i == 0)
    {
        ans = ans / i * (i-1);
        while(n%i == 0)
        {
            n /= i;
        }
    }
    if(n > 1) ans = ans / n *(n-1);
    return ans;
}



int main()
{
    int n;
    while(scanf("%d", &n)!=EOF && n!=-1)
    {
        printf("%d\n", euler_phi(n));
    }
    return 0;
}
