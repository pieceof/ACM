#include <cstdio>
#include <algorithm>
using namespace std;

int Arr[10000];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%d",Arr+i);

	//STLͨ���㷨����������ע�����䶼��ǰ�պ�
	partial_sort(Arr,Arr+n/2+1,Arr+n);

	printf("%d\n",Arr[n/2]);
	return 0;
}
