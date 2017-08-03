#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
const int SIZE = 1000;

int nub[SIZE];
void just( int *a,int n){
    int now_score = 0;
    int now_statu = 1;

    for (int i = 0;i < n;++i ){
        if ( now_score < 100 ){
            now_score += ((a[i] == 1)?10:-5);
            if ( now_score < 0 ) now_score = 0;
        }

        else{
            if ( i+1 >= n )break;
            if ( a[i] == 1 && a[i+1] == 1 ) {now_score = 0 , now_statu++,i+=1;continue;}
            if ( a[i] == 0 && a[i+1] == 0 ) {now_score = 60,i+=1;continue;}
            if ( i+2 >= n) break;
            if ( a[i] == 1 && a[i+1] == 0 && a[i+2] == 1){now_score = 0 , now_statu++,i+=2;continue;}
            if ( a[i] == 1 && a[i+1] == 0 && a[i+2] == 0){now_score = 60,i+=2;continue;}
            if ( a[i] == 0 && a[i+1] == 1 && a[i+2] == 1){now_score = 0 , now_statu++,i+=2;continue;}
            if ( a[i] == 0 && a[i+1] == 1 && a[i+2] == 0){now_score = 60,i+=2;continue;}

        }

    }
    if ( now_statu == 1 ) puts("D");
    if ( now_statu == 2 ) puts("C");
    if ( now_statu == 3 ) puts("B");
    if ( now_statu == 4 ) puts("A");
    if ( now_statu >= 5 ) puts("S");

}
int main()
{
    int n;
    while ( scanf("%d",&n) != EOF ){

        for (int i = 0 ; i < n;++i )
            scanf("%d",nub+i);
        just(nub,n);
    }
    return 0;
}
