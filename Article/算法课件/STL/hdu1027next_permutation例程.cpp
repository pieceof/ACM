//求排第n个数的第m个全排列，STL，15ms，224k，349B
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int Arr[1000+4];

int main(){
	int n,m;
	while( EOF != scanf("%d%d",&n,&m) ){
        for(int i=1;i<=n;++i)Arr[i-1] = i;
		for(int i=1;i<m;++i)next_permutation(Arr,Arr+n);
		printf("%d",Arr[0]);
		for(int i=1;i<n;++i)printf(" %d",Arr[i]);
		printf("\n");
	}
	return 0;
}
