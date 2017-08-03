#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;

using namespace std;

const int SIZE = 1100;


int t;
map<int,int> team;
int kase = 1;

bool read( ){
    scanf("%d",&t);
    if ( 0 == t ) { return 0;}
    printf("Scenario #%d\n",kase++);
    team.clear();
    for ( int i = 0 ;i < t;++i ){
        int n; scanf("%d",&n);
        for (int j = 0;j < n ;++j ){
            int x; scanf("%d",&x);
            team[x] = i;
        }
    }
    return 1;
}
void solve( ){
    queue < int > q1,q2[SIZE];
    char op[20];
    int x;

    while (true ){
        scanf("%s",op);
        if (*op == 'S' ) break;
        if ( *op == 'E' ){
            scanf("%d",&x);
            int t = team[x];
            if ( q2[t].empty() ) q1.push(t);
            q2[t].push(x);
        }else {
            int t = q1.front();
            printf( "%d\n",q2[t].front());

            q2[t].pop();
            if ( q2[t].empty())q1.pop();
        }
    }
    printf("\n");
}

int main()
{
    while ( read() ) solve();
    return 0;
}
