#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <stdlib.h>
//stl
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <utility>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <bitset>
//unused
#include <complex>
#include <functional>
#include <fstream>
#include <ctime>
#include <stdexcept>
//define
#define MOD  1000000007
#define INF 1<<30
#define EPS 1e-13
#define S(r) r*r*PI
#define PI acos(-1.0)
#define UP(i,x,y) for(int i=x;i<=y;i++)
#define MEM(a,x) memset(a,x,sizeof(a))
#include <bits/stdc++.h>
int gcd(int a,int b){  return b==0?a:gcd(b,a%b); }
typedef long long llt ;



//cout.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
//freopen("cin.txt", "r", stdin);
//freopen("cout.txt", "w", stdout);
using namespace std;




const int SIZE =  1000000;
struct node_t{
    node_t* child[26];
    int cnt;
}Node[SIZE];
int toUsed = 1;

void insert( char const word[] ){
    node_t* loc = Node;
    for (int i = 0 ;word[i] ;++i ){
        int sn = word[i]-'a';
        if ( !loc->child[sn] )
            loc->child[sn] = Node + toUsed ++;

        loc = loc->child[sn];
        loc->cnt++;

    }
    //loc->cnt++;
}
int find( char const word[] ){
    node_t * loc = Node;
    for (int i = 0; word[i];++i ){
        int sn = word[i]-'a';
        if ( !loc->child[sn] ) return 0;
        loc = loc->child[sn];

    }
    return loc->cnt;
}


int main(){
    int n,m;
    scanf("%d",&n);
    char wd[100];
    memset( Node,0,sizeof(Node));
    for (int i = 0;i < n;++i ){
        scanf("%s",wd);
        insert(wd);
    }

    scanf("%d",&m);
    while( m-- ){
        scanf("%s",wd);
        int ans = find(wd);
        printf("%d\n",ans);

    }


    return 0;
}
