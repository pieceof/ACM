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
        Next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
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

const int SIZE = 1050000;
char str[SIZE],p[SIZE];
int Next[SIZE];
int n,t;
int main()
{
//    scanf("%d",&n);
    while(scanf("%s",p)!=EOF)
    {
        if (p[0] == '.')break;

        int len = strlen(p);
        getNext(p,Next,len);
//        dispArray(Next,len);
        if (len % (len-Next[len-1]) == 0)
        printf("%d\n",len / (len-Next[len-1]));
        else printf("1\n");
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
    printf("%d",a[0]);
    for (int i = 1 ;i < n;++i )printf(" %d",a[i]);puts("");
}
