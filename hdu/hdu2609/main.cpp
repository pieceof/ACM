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
    node_t* child[30];//26������
//	int idx;//��Ӧ���͵����
    bool suffix;
    int cnt;
} Node[SIZE];
int toUsed = 1;

//idx��ʾ���ʶ�Ӧ���͵����
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
//���ҵ��ʣ����ؽ��͵���ţ�0��ʾδ�ҵ�
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
    //int i = 0, k = -1,n++ ; // kmpѭ��ƥ�����һλ
    int i = 0, k = -1;
    while( i < n ) {
        while( k >= 0 && P[i] != P[k] )
            k = Next[k];
        ++i,++k;
        if ( i == n ) return;
        Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

/**< ѭ��kmpƥ���ʱ��Ҫ����һλnext  */
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
            /**< �����ѭ��ƥ�� ֱ��return  */
//            return tp-plen;
        }
    }
    return ans;
    return -1;
}


/*
*  ��չKMP�㷨
*/
//next[i]:x[i...m-1]��x[0...m-1]�������ǰ׺
//extend[i]:y[i...n-1]��x[0...m-1]�������ǰ׺
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
 *����n���ȵ��ַ������洢�Ǵ�1~n+n+1�� ʵ�ʳ�����n+n+2��
 *ע��size��Χ
 */
/*
const int _SIZE =  SIZE+SIZE;
int p[_SIZE];
template<class DATA >
void manacher(DATA *s ,int len) //manacher ����
{
    for(int i = len;i >= 0;--i) //��s�����м��#����ͷ��*
        s[i+i+2] = s[i] , s[i+i+1] = '#';
//        s[i+i+2] = s[i] , s[i+i+1] = -1;
    s[0] = '*';
//    s[0] = -2;
    int id , mx = 0;  //mx������idΪ����ʱ��������Զ��λ��
    for(int i = 1;i <= len+len+1; ++i ){
        if( mx > i ) p[i] = min(p[2*id-i],mx-i ); //���������Զλ�ô��ڵ�ǰƥ��ĵط�����p[i]ȡmin��id�ĶԳƵ��p��������Զ����-i��
        else p[i] = 1; //���i��mx�ҷ�����p[i]=-1;
        // �����Ҫ���Ĵ���������
//        while( s[i-p[i]] == s[i+p[i]] &&  s[i-p[i]] <= s[i-p[i]+2] ) ++p[i];
        while( s[i-p[i]] == s[i+p[i]] ) ++p[i];   //�ж�i���ĳ���
        if( i + p[i] > mx ) //���Ƿ�Ҫ������Զ���룬���Ҫ�����˵���Ϊ���ġ�
            id = i , mx = p[i] + i;
    }
}
//*/

///*
template<class DATA >
int MinimumRepresentation(DATA const s[],int len){
    int i=0,j=1,k=0; //i��j���������бȽϵ���ʼƥ��λ�㣬k��ƥ�䳤��
    while( i < len && j < len && k < len ){
        int t = s[(i+k)%len] - s[(j+k)%len];//�Ƚ��������Ĵ�С��ϵ
        if( t == 0 ) k++;//�����ͬ��ƥ�䳤�����󣬱Ƚ�λ������
        else {//�����ͬ�����ֵ�����λ�ÿ϶������Ǵ𰸣��ı��Ǹ�ƥ��λ��
            if( t > 0 ) i += k+1;
            else j += k+1;
            if( i == j ) j++;//i��jһ��Ҫ��
            k = 0;//ƥ�䳤��Ҫ����Ϊ0
        }
    }
    return  i < j ? i : j ;//��Ϊ�ֵ�����λ�ñ������ˣ����Խ�С��λ�þ��Ǵ�
}
//*/
///*
template<class DATA >
int MaximumRepresentation(DATA const s[],int len){
    int i=0,j=1,k=0; //i��j���������бȽϵ���ʼƥ��λ�㣬k��ƥ�䳤��
    while( i < len && j < len && k < len ){
        int t = s[(j+k)%len] - s[(i+k)%len];//�Ƚ��������Ĵ�С��ϵ
        if( t == 0 ) k++;//�����ͬ��ƥ�䳤�����󣬱Ƚ�λ������
        else {//�����ͬ�����ֵ�����λ�ÿ϶������Ǵ𰸣��ı��Ǹ�ƥ��λ��
            if( t > 0 ) i += k+1;
            else j += k+1;
            if( i == j ) j++;//i��jһ��Ҫ��
            k = 0;//ƥ�䳤��Ҫ����Ϊ0
        }
    }
    return  i < j ? i : j ;//��Ϊ�ֵ�����λ�ñ������ˣ����Խ�С��λ�þ��Ǵ�
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
    ios.sync_with_stdio(false);  /// ��ôcin, �Ͳ��ܸ�C�� scanf��sscanf, getchar, fgets֮���һ��ʹ���ˡ�
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
