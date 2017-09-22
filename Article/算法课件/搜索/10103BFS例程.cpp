#include <iostream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <climits>
#include <deque>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <stdlib.h>
#define INF 1<<30
#define EPS 1e-13
#define MOD  1000000007
#define S(r) r*r*PI
///#define N 100000
#define maxn 10010
#define PI acos(-1.0)
#define UP(i,x,y) for(int i=x;i<=y;i++)
#define DOWN(i,x,y) for(int i=x;i>=y;i--)
#define MEM(a,x) memset(a,x,sizeof(a))
#define Wt while(t--)
#define LL long long
#define endll printf("\n")
#define LEN sizeof(struct student)
using namespace std;
bool cmp(int a,int b) { return a<b; }
int gcd(int a,int b){  return b==0?a:gcd(b,a%b);  }


int N,M,K;
int Snake[100][2];
int Ladder[100][2];
bool Flag[20*20+1];
int Ans[20*20+1];

int goStep(int n){
	for(int i=0;i<M;i++)if(n == Ladder[i][0])return Ladder[i][1];
	for(int i=0;i<K;i++)if(n==Snake[i][0]) return Snake[i][1];
	return n;
}

void bfs(){
	queue<int> que;
	que.push(1);

	while(1){
		int status = que.front();
		que.pop();

		for(int i=1;i<=6;i++){
			int st = goStep(i+status);
			if ( st <= N * N && !Flag[st] ){
				que.push(st);
				Flag[st] = true;
				Ans[st] = Ans[status] + 1;
				if ( N * N == st ) return;
			}
		}
	}
}

int main(){
	while( scanf("%d",&N) && N ){
		scanf("%d",&M);
		for(int i=0;i<M;i++)scanf("%d%d",Ladder[i],Ladder[i]+1);

		scanf("%d",&K);
		for(int i=0;i<K;i++)scanf("%d%d",Snake[i],Snake[i]+1);

		memset(Flag,0,sizeof(Flag));
		memset(Ans,0,sizeof(Ans));

		if ( 1 == N ){
			printf("0\n");
			continue;
		}

        bfs();
		printf("%d\n",Ans[N*N]);
	}

	return 0;
}

