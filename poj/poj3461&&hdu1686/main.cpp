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

void getNext( char *P,int *Next ,int n ){
    Next[0] = 0;
    for (int i = 1;i < n ;++i ){
        int k = Next[i-1];
        while ( k > 0 && P[i] != P[k] )
            k = Next[k-1];
        Next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
    }
}
void getKMPNext(char * P,int *Next){
    Next[0] = -1;
    int i = 0, k = -1,n = strlen(P)+1 ;
    while( i < n ){
    	while( k >= 0 && P[i] != P[k] )
    		k = Next[k];
    	++i,++k;
    	if ( i == n ) return;
    	Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}
/**< 循环kmp匹配的时候要多算一位next  */
int KMP(char const T[],char const P[],int Next[],int pos=0){
    int const plen = strlen(P);
    int const tlen = strlen(T);
    int ans = 0;
    if ( tlen < plen ) return 0;
    int tp = pos, pp = 0;
    while( tp < tlen ){
    	if ( -1 == pp || T[tp] == P[pp] )++tp,++pp;
    	else pp = Next[pp];
    	if ( plen == pp  ) {
            ans++;
            pp = Next[pp];
            /**< 如果不循环匹配 直接return  */
//            return tp-plen;
        }
    }
    return ans;
    return -1;
}
const int SIZE = 1050000;
char str[SIZE],part[SIZE],tar[SIZE];
int Next[SIZE];
int n,t;
int main()
{
    scanf("%d",&t);

    while( t-- ){
//        scanf("%d",&n);
        scanf("%s%s",part,tar);//scanf("%s",tar);
//        int tn = strlen(tar);
//        int pn = strlen(part);
//        int pos ;scanf("%d",&pos);
        getKMPNext(part,Next);
        int ans = KMP(tar,part,Next);
        printf("%d\n",ans);
//        dispArray(Next,strlen(part)+1);

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
