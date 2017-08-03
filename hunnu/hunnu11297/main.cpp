#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstring>
#define INF ((1<<31)-1)
using namespace std;
typedef long long llt;

//int ST[4000010];

struct tree{
    int s,e;
    friend bool operator < ( tree const &a,const tree & b){
        return a.s < b.s;
    }
}Tree[40050];
int main(){
    int l,m;
    while(scanf("%d%d",&l,&m) != EOF){

        for (int i = 0;i < m;++i){
            scanf("%d%d",&Tree[i].s,&Tree[i].e);
        }
        sort(Tree,Tree+m);
        int idx = 0;

        int ans = l+1;
        int start,maxEnd = -1;

        while(idx < m){
            while( maxEnd >= Tree[idx].s && idx < m ) idx++;
            start = Tree[idx].s;
            maxEnd = Tree[idx].e;
            int j = idx+1;
            while( maxEnd >= Tree[j].s && j < m ) maxEnd = max(maxEnd,Tree[j].e),j++;
            ans -= (maxEnd - start + 1);
            idx = j;
        }

        printf("%d\n",ans);

    }

    return 0;
}
