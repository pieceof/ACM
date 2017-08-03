#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <climits>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;


void dispArray( int *a ,int n );

void getNext( char *P,int *Next, int n ){
    Next[0] = 0;
    for (int i = 1;i < n ;++i ){
        int k = Next[i-1];
        while ( k > 0 && P[i] != P[k] )
            k = Next[k-1];
        if ( P[k] == P[i] ) Next[i] = k+1;
        else Next[i] = 0;
    }
}
void getKMPNext(char * P,int *Next,int n){
    Next[0] = -1;
    int i = 0, k = -1;
    while( i < n ){
    	while( k >= 0 && P[i] != P[k] )
    		k = Next[k];
    	++i,++k;
    	if ( i == n ) return;
    	Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

const int SIZE = 1000;
char str[SIZE];
int Next[SIZE];
int n,t;
int main()
{
//    scanf("%d",&n);
    scanf("%d",&t);
    while( t-- ){
        scanf("%s",str);
        int len = strlen(str);
        getKMPNext(str,Next,len);
        dispArray(Next,len);
    }
    return 0;
}


/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
void dispArray( int *a ,int n ){
//    printf("this array is  ==  > ");
    if( n < 1) puts("");
    printf("%d",a[0]+1);
    for (int i = 1 ;i < n;++i )printf(" %d",a[i]+1);puts("");
}
