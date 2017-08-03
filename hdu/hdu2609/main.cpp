#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <assert.h>
#include <climits>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;


int const SIZE = 1000050;
void dispArray( int *a,int n );

/*
struct node_t {
    node_t* child[30];//26个儿子
//	int idx;//对应解释的序号
    bool suffix;
    int cnt;
} Node[SIZE];
int toUsed = 1;

//idx表示单词对应解释的序号
void insert(char const word[] ) {
    node_t* loc = Node;
    for(int i = 0; word[i]; ++i) {
        loc->cnt++;
        int sn = word[i] - 'a';
        if ( !loc->child[sn] ) loc->child[sn] = Node + toUsed ++;
        loc = loc->child[sn];
    }
    loc->cnt++;
//    loc->suffix = 1;
}
//查找单词，返回解释的序号，0表示未找到
int find(char const word[]) {
    node_t* loc = Node;
    for(int i = 0; word[i] ; ++i) {
//        if ( loc->suffix ) return 1;
        int sn = word[i] - 'a';
        if ( !loc->child[sn] ) return 0;
        loc = loc->child[sn];
    }
    return loc->cnt;
}
//*/


template<class DATA>
void getNext( DATA const P[],int *Next,int n ) {
    Next[0] = 0;
    for (int i = 1; i < n ; ++i ) {
        int k = Next[i-1];
        while ( k > 0 && P[i] != P[k] )
            k = Next[k-1];
        Next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
    }
}
template<class DATA>
void getKMPNext(DATA const P[],int *Next,int n ) {
    Next[0] = -1;
    //int i = 0, k = -1,n++ ; // kmp循环匹配多算一位
    int i = 0, k = -1;
    while( i < n ) {
        while( k >= 0 && P[i] != P[k] )
            k = Next[k];
        ++i,++k;
        if ( i == n ) return;
        Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

/**< 循环kmp匹配的时候要多算一位next  */
template<class DATA >
int KMP(DATA const T[],int tlen,DATA const P[],int plen,int Next[],int pos=0) {
    int ans = 0;
    if ( tlen < plen ) return 0;
    int tp = pos, pp = 0;
    while( tp < tlen ) {
        if ( -1 == pp || T[tp] == P[pp] )++tp,++pp;
        else pp = Next[pp];
        if ( plen == pp  ) {
            ans++;
            pp = 0;
//            pp = Next[pp];
            /**< 如果不循环匹配 直接return  */
//            return tp-plen;
        }
    }
    return ans;
    return -1;
}


/*
*  扩展KMP算法
*/
//next[i]:x[i...m-1]与x[0...m-1]的最长公共前缀
//extend[i]:y[i...n-1]与x[0...m-1]的最长公共前缀
template<class DATA >
void getExtendKMPNext(DATA const T[],int tlen,int Next[]) {
    Next[0] = tlen ;
    int j = 0,k = 1;;
    while ( j+1 < tlen && T[j] == T[j+1] ) j++;
    Next[1] = j;
    for(int i = 2; i < tlen; i++ ){
        int p = Next[k] + k-1;
        int L = Next[i-k];
        if( i+L < p+1 ) Next[i] = L;
        else{
            j = max( 0 , p-i+1 );
            while( i+j < tlen && T[i+j] == T[j] ) j++;
            Next[i] = j;
            k = i;
        }
    }
}
template<class DATA >
void getExtendKMP(DATA const T[],int tlen,DATA const S[],int slen,int Next[], int extend[]) {
    getExtendKMPNext(T,tlen,Next);
    int j = 0,k = 0;
    while( j < slen && j<tlen && T[j] == S[j] ) j++;
    extend[0] = j;
    for(int i = 1; i < slen; i++ ) {
        int p = extend[k] + k-1;
        int L = Next[i-k];
        if( i+L < p+1 ) extend[i] = L;
        else {
            j = max( 0, p-i+1);
            while( i+j < slen && j < tlen && S[i+j] == T[j]) j++;
            extend[i] = j;
            k = i;
        }
    }
}
/*
 *对于n长度的字符串，存储是从1~n+n+1， 实际长度是n+n+2；
 *注意size范围
 */
/*
const int _SIZE =  SIZE+SIZE;
int p[_SIZE];
template<class DATA >
void manacher(DATA *s ,int len) //manacher 函数
{
    for(int i = len;i >= 0;--i) //将s扩大，中间加#，开头加*
        s[i+i+2] = s[i] , s[i+i+1] = '#';
//        s[i+i+2] = s[i] , s[i+i+1] = -1;
    s[0] = '*';
//    s[0] = -2;
    int id , mx = 0;  //mx代表以id为中心时，到达最远的位置
    for(int i = 1;i <= len+len+1; ++i ){
        if( mx > i ) p[i] = min(p[2*id-i],mx-i ); //如果到达最远位置大于当前匹配的地方，则p[i]取min（id的对称点的p，到达最远距离-i）
        else p[i] = 1; //如果i在mx右方，则p[i]=-1;
        // 如果需要回文串单调不减
//        while( s[i-p[i]] == s[i+p[i]] &&  s[i-p[i]] <= s[i-p[i]+2] ) ++p[i];
        while( s[i-p[i]] == s[i+p[i]] ) ++p[i];   //判断i回文长度
        if( i + p[i] > mx ) //看是否要更新最远距离，如果要，将此点作为中心。
            id = i , mx = p[i] + i;
    }
}
//*/

///*
template<class DATA >
int MinimumRepresentation(DATA const s[],int len){
    int i=0,j=1,k=0; //i和j是两个进行比较的起始匹配位点，k是匹配长度
    while( i < len && j < len && k < len ){
        int t = s[(i+k)%len] - s[(j+k)%len];//比较两个串的大小关系
        if( t == 0 ) k++;//如果相同，匹配长度增大，比较位置向移
        else {//如果不同，则字典序大的位置肯定不会是答案，改变那个匹配位点
            if( t > 0 ) i += k+1;
            else j += k+1;
            if( i == j ) j++;//i和j一定要错开
            k = 0;//匹配长度要重置为0
        }
    }
    return  i < j ? i : j ;//因为字典序大的位置被后移了，所以较小的位置就是答案
}
//*/
///*
template<class DATA >
int MaximumRepresentation(DATA const s[],int len){
    int i=0,j=1,k=0; //i和j是两个进行比较的起始匹配位点，k是匹配长度
    while( i < len && j < len && k < len ){
        int t = s[(j+k)%len] - s[(i+k)%len];//比较两个串的大小关系
        if( t == 0 ) k++;//如果相同，匹配长度增大，比较位置向移
        else {//如果不同，则字典序大的位置肯定不会是答案，改变那个匹配位点
            if( t > 0 ) i += k+1;
            else j += k+1;
            if( i == j ) j++;//i和j一定要错开
            k = 0;//匹配长度要重置为0
        }
    }
    return  i < j ? i : j ;//因为字典序大的位置被后移了，所以较小的位置就是答案
}
//*/


// =================== code line ==========================//

//int SIZE = 105000;
char part[SIZE],tar[SIZE];
int EkmpNext[SIZE],extend[SIZE],Next[SIZE];
int n,t;
int kase = 1;
char S[SIZE],T[SIZE];
char str[SIZE];
//int tar[SIZE],part[SIZE];
//int ans[SIZE];
char secret[30];
char key[30];
set<string> st;
string tmp;
int main() {

//    scanf("%d",&t);
//    while(t--) {
    while( scanf("%d",&n) != EOF ){
//    while ( scanf("%s",part) != EOF){
//        if (kase != 1) puts("");
//        scanf("%d",&n);
//        scanf("%s",secret);
//    while( scanf("%s",str) != EOF ){
//        scanf("%s",T);
        st.clear();
        for (int i = 0;i < n;++i ){
            scanf("%s",str);
            int len = strlen(str);
            int idx = MinimumRepresentation(str,len);
            strcpy(tar,str);
            strcat(tar,str);
            tmp = string(tar+idx,tar+len+idx);
//            deBug(tmp);
            if ( st.count(tmp) == 0 ) st.insert(tmp);
        }
        printf("%d\n",st.size());
//        getExtendKMP(T,strlen(T),S,strlen(S),EkmpNext,extend);
//        getNext(str,Next,strlen(str));
//        dispArray(extend,strlen(T));
//        dispArray(Next,strlen(part));
//        dispArray(EkmpNext,strlen(S));
//        int cnt = len-Next[len-1];
//        if ( len % cnt == 0 ) cnt = len/cnt;
//        else cnt = 1;
//        len = len/cnt;
//        int l = MinimumRepresentation(str,len)+1;
//        int r = MaximumRepresentation(str,len)+1;
//        printf("%d %d %d %d\n",l,cnt,r,cnt );
//        printf("%d")
    }



}

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
void dispArray( int *a,int n ) {
//    printf("this array is  ==  > ");
    if( n < 1) puts("");
    printf("%d",a[0]);
    for (int i = 1 ; i < n; ++i )printf(" %d",a[i]);
    puts("");
}
