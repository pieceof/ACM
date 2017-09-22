#include <cstdio>
#include <algorithm>
using namespace std;

int Arr[10000];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%d",Arr+i);

	//STLÍ¨ÓÃËã·¨
	nth_element(Arr,Arr+n/2,Arr+n);

	printf("%d\n",Arr[n/2]);
	return 0;
}
