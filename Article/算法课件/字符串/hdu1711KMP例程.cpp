//KMP算法，匹配的不是字符序列，而是整数
#include <cstdio>
using namespace std;
int T[1000005];
int P[10005];
int Next[10005];
void getKMPNext(int const P[],int n,int next[]){
    next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
    	while( k >= 0 && P[i] != P[k] )
    		k = next[k];
    	++i,++k;
    	if ( i == n ) return;
    	next[i] = ( P[i] == P[k] ) ? next[k] : k;
    }
}
//在T中搜索P，输出第一个找到的位置，否则输出-1
int KMP(int const T[],int tn,int const P[],int pn,int const next[]){
	if ( pn > tn ) return -1;
    int tp = 0, pp = 0;
    while( tp < tn ){
    	if ( -1 == pp || T[tp] == P[pp] ) ++tp,++pp;
    	else pp = next[pp];
    	if ( pn == pp ) return tp - pp;
    }
    return -1;
}
void dispNext(int n){
	for(int i=0;i<n;++i)printf("%d ",Next[i]);
	printf("\n");
}
int main() {
	int nofkase;
	scanf("%d",&nofkase);
	while(nofkase--){
		int tn,pn;
		scanf("%d%d",&tn,&pn);
		for(int i=0;i<tn;++i)scanf("%d",T+i);
		for(int i=0;i<pn;++i)scanf("%d",P+i);
		getKMPNext(P,pn,Next);
		//从1开始索引
		int t = KMP(T,tn,P,pn,Next);
		printf("%d\n",(-1==t)?-1:t+1);
	}
	return 0;
}
