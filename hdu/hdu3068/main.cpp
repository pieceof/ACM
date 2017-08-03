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

void getNext( char const P[],int *Next ,int n ){
    Next[0] = 0;
    for (int i = 1;i < n ;++i ){
        int k = Next[i-1];
        while ( k > 0 && P[i] != P[k] )
            k = Next[k-1];
        Next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
    }
}
void getKMPNext(char const P[],int *Next){
    Next[0] = -1;
    //int i = 0, k = -1,n = strlen(P)+1 ; // kmp循环匹配多算一位
    int i = 0, k = -1,n = strlen(P);
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
//            ans++;
//            pp = Next[pp];
            /**< 如果不循环匹配 直接return  */
            return tp-plen;
        }
    }
//    return ans;
    return -1;
}

/*
 *对于n长度的字符串，存储是从1~n+n+1， 实际长度是n+n+2；
 *注意size范围
 */
const int SIZE =  230000;
int p[SIZE];
void manacher(char *s) //manacher 函数
{
    int len=strlen(s);
    for(int i = len;i >= 0;--i) {//将s扩大，中间加#，开头加*
        s[i+i+2] = s[i];
        s[i+i+1] = '#';
    }
    s[0] = '*';
    int id,mx = 0;  //mx代表以id为中心时，到达最远的位置
    for(int i = 1;i <= len+len+1;++i ){
        if( mx > i ) p[i] = min(p[2*id-i],mx-i ); //如果到达最远位置大于当前匹配的地方，则p[i]取min（id的对称点的p，到达最远距离-i）
        else p[i] = 1; //如果i在mx右方，则p[i]=-1;
        while( s[i-p[i]] == s[i+p[i]] ) ++p[i];   //判断i回文长度
        if( i + p[i] > mx ) {//看是否要更新最远距离，如果要，将此点作为中心。
            id = i;
            mx = p[i] + i;
        }
    }
}


//const int SIZE = 1050000;
char str[SIZE],part[SIZE],tar[SIZE];
int Next[SIZE];
int n,t;
int main()
{
//    scanf("%d",&t);
//
//    while( t-- ){
    while ( scanf("%s",str) != EOF ){
            n = strlen(str);
        manacher(str);

//        for (int i = 1 ;i <= n+n+1 ;++i )cout << p[i] <<" ";cout << endl;
//        for (int i = 1 ;i <= n+n+1 ;++i )cout << str[i] <<" ";cout << endl;
        int ans = 0;
        for (int i = 1;i <= n+n+1;++i ){
            if ( p[i]-1 > ans ){
                ans = p[i]-1;
            }
        }
        printf("%d\n",ans);
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
