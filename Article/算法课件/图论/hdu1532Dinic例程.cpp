 #include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>

#define INT_MAX 0x3f3f3f3f

using namespace std;

int mp[502][502];
int N,M;
bool combine[502];
int minC=INT_MAX;

void search(int &s,int &t){
    bool vis[502];
    int w[502];
    memset(vis,0,sizeof(vis));
    memset(w,0,sizeof(w));
    int tmpj=1000;
    for(int i=0;i<N;i++){
        int max=-INT_MAX;
        for(int j=0;j<N;j++){
            if(!vis[j]&&!combine[j]&&max<w[j]){
                max=w[j];
                tmpj=j;
            }
        }
        if(t==tmpj){minC=w[t];return;}
        vis[tmpj]=1;
        s=t,t=tmpj;
        for(int j=0;j<N;j++){
            if(!vis[j]&&!combine[j])
                w[j]+=mp[t][j];
        }
    }
    minC=w[t];
}

int mincut(){
    int ans=INT_MAX;
    int s,t;
    memset(combine,0,sizeof(combine));
    for(int i=0;i<N-1;i++){
        s=t=-1;
        search(s,t);
        combine[t]=true;
        ans=ans>minC?minC:ans;
        for(int j=0;j<N;j++){
            mp[s][j]+=mp[t][j];
            mp[j][s]+=mp[j][t];
        }
    }
    return ans;
}

int main(){
    //freopen("in.txt","r",stdin);
    while(cin>>N>>M){
        memset(mp,0,sizeof(mp));
        int u,v,w;
        while(M--){
            scanf("%d %d %d",&u,&v,&w);
            mp[u][v]+=w;
            mp[v][u]+=w;
        }
        cout<<mincut()<<endl;
    }
    return 0;
}
