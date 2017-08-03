#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;

using namespace std;

set<llt> s;
priority_queue <llt,vector<llt> ,greater<llt> > pq;

int main()
{
    pq.push(1);
    s.insert(1);
    int i = 0;
    while ( 1 ){
        i++;
        llt x = pq.top();pq.pop();

        llt tx1 = x*2;
        if ( s.count(tx1) == 0 ){
            s.insert(tx1);
            pq.push(tx1);
        }
        llt tx2 = x*3;
        if ( s.count(tx2) == 0 ){
            s.insert(tx2);
            pq.push(tx2);
        }
        llt tx3 = x*5;
        if ( s.count(tx3) == 0 ){
            s.insert(tx3);
            pq.push(tx3);
        }

        if ( i == 1500  ){
            printf("The 1500'th ugly number is %d.\n",x);
            break;
        }
    }


    return 0;
}
