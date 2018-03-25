//
// Created by bitwater on 18-3-25.
//

#include<bits/stdc++.h>

using namespace std;

const  int SIZE = 1000+50;
int fa[SIZE];
void init( ){
    for(int i = 0;i < SIZE;++i)
        fa[i] = i;
}
int find(int x){
    return  fa[x] == x ? x : fa[x] = find(fa[x]);
}
void unite(int x,int y ){
    fa[find(x)] = find(y);
}
map<int, vector<int> > mp;

int ans[SIZE];
int anscnt = 0;
map<int,int> mp2;

int main(int argc, char *argv[]) {

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        int k;
        scanf("%d:", &k);
        for (int j = 0; j < k; ++j) {
            int x;
            scanf("%d", &x);
            mp[x].push_back(i);
        }
    }
//    printf("\n");
    init();
    for(auto i : mp){
        int tmp = i.second[0];
        for (auto j: i.second){
            unite(tmp,j);
        }
    }

    for(int i = 0;i < n;++i ){
        find(i);
        if( fa[i] == i ){
            ans[anscnt++] = i;
            mp2[i] = 0;
        }
    }
    printf("%d\n",mp2.size());
//    cout << mp2.size()<<endl;
    for(int i = 0;i < n;++i ){
        if( mp2.count(fa[i]) ){
            mp2[fa[i]]++;
        }
    }
    anscnt = 0;
//    printf("%d\n",anscnt);
    for(auto i : mp2){
//        printf("%d ",i.second);
        ans[anscnt++] = i.second;
    }
    sort(ans,ans+anscnt,greater<int>() );
    for(int i = 0;i < anscnt-1;++i ){
        printf("%d ",ans[i]);
    }
    printf("%d\n",ans[anscnt-1]);
    return 0;
}