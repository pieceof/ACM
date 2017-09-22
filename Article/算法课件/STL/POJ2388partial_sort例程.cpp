#include <cstdio>
#include <algorithm>
using namespace std;

int Arr[10000];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%d",Arr+i);

	//STL通用算法，部分排序，注意区间都是前闭后开
	partial_sort(Arr,Arr+n/2+1,Arr+n);

	printf("%d\n",Arr[n/2]);
	return 0;
}
