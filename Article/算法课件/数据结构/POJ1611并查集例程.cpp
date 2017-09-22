#include <cstdio>
#define SIZE 30000
int Father[SIZE];

void init(int n){
	for(int i=0;i<n;++i)Father[i]=i;
}

//递归寻找父节点
int find(int x){
	return Father[x] == x 
		? x
		: ( Father[x] = find(Father[x]) );
}

//合并
void unite(int x,int y){
    Father[find(y)] = find(x);
}

int main(){
	int n,m;
	while( scanf("%d%d",&n,&m) ){
		if ( 0 == n && 0 == m ) return 0;
		init(n);
		for(int i=0;i<m;++i){
			int nn,x;
			scanf("%d%d",&nn,&x);
			for(int j=1;j<nn;++j){
				int y;
				scanf("%d",&y);
				unite(x,y);
			}
		}
		
		int ret = 0;
		for(int i=0;i<n;++i)
		    if ( find(0) == find(i) )
		        ++ret;
	    printf("%d\n",ret);
	}
	return 0;
}
