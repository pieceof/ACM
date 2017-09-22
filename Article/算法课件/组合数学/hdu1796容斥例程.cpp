#include <iostream>
using namespace std;
typedef unsigned int uint;
int A[11];

uint gcd(uint a,uint b){
    uint r = a % b;
	while( r ){
	    a = b;
		b = r;
		r = a % b;
	}
	return b;
}
uint lcm(uint a,uint b){
    return a / gcd(a,b) * b;
}
int main(){
	int n,m;
	while( EOF != scanf("%d%d",&n,&m) ){
	    int k = 0;   
		for(int i=0;i<m;++i){
			int x;
			scanf("%d",&x);
			if ( 0 == x || x >=n ) continue;
			A[k++] = x;
		}

		if ( 0 == k ){
		    printf("0\n");
			continue;
		}

		m = k;
        //题目要求小于n，所以预先减1    
		--n;
        uint ans = 0;
		for(int i=1;i<(1<<m);++i){
		    uint x = 1;
			uint sum = 0;
			for(int j=0;j<m;++j){
				if ( ( i >> j ) & 1 ){
				    x = lcm(x,A[j]);
					++sum;
				}
			}
			
			if ( sum & 1 ) ans += n / x;
			else           ans -= n / x;
		}
		printf("%u\n",ans);
	}
    return 0;
}