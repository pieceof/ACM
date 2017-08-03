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
#define Case printf("Case %d: ",kase++)

typedef long long llt;
using namespace std;


int const SIZE = 505000;
void dispArray( int const a[],int n );

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
void getExtendKMPNext(DATA const T[],int Next[],int tlen) {
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
    getExtendKMPNext(T,Next,tlen);
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

// ��׺����ģ��
/** \DC3�㷨
 *ʹ�ô�dc3�㷨һ��Ҫ��֤r��sa����󳤶Ȳ�С��3��ԭ����
 *
 */
 /*
//�����꣬���»��߿�ͷ
#define _F(x) ((x)/3+((x)%3==1?0:tb))
#define _G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
//�������飬���»��߿�ͷ
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//��������
int _c0(int const r[],int a,int b){
    return r[a] == r[b]
        && r[a+1] == r[b+1]
        && r[a+2] == r[b+2];
}
int _c12(int k,int *r,int a,int b){
    if( 2 == k ) return r[a]<r[b] || ( r[a]==r[b]&&_c12(1,r,a+1,b+1) );
    return r[a]<r[b] || ( r[a]==r[b]&&_wv[a+1]<_wv[b+1] );
}
void _sort(int const r[],int *a,int *b,int n,int m){
    int i;
    for(i=0;i<n;i++) _wv[i] = r[a[i]];
    for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[_wv[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) b[--_ws[_wv[i]]] = a[i];
    return;
}
//r: Դ���飬�ҳ�r[n-1]�⣬����r[i]>0
//n: r�ĳ���
//m: r�е�Ԫ��ȡֵ���Ͻ磬������r[i]<m
//sa:��׺���飬�����
void dc3(int r[],int n,int m,int sa[]){
    int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
    r[n] = r[n+1] = 0;
    for(i=0;i<n;i++) if(i%3!=0) _wa[tbc++]=i;
    _sort(r+2,_wa,_wb,tbc,m);
    _sort(r+1,_wb,_wa,tbc,m);
    _sort(r,_wa,_wb,tbc,m);
    for(p=1,rn[_F(_wb[0])]=0,i=1;i<tbc;i++)
        rn[_F(_wb[i])] = _c0(r,_wb[i-1],_wb[i])?p-1:p++;
    if(p<tbc) dc3(rn,tbc,p,san);
    else for(i=0;i<tbc;i++) san[rn[i]]=i;
    for(i=0;i<tbc;i++) if(san[i]<tb) _wb[ta++] = san[i]*3;
    if(n%3==1) _wb[ta++]=n-1;
    _sort(r,_wb,_wa,ta,m);
    for(i=0;i<tbc;i++) _wv[_wb[i] = _G(san[i])] = i;
    for(i=0,j=0,p=0;i<ta&&j<tbc;p++)
        sa[p] = _c12(_wb[j]%3,r,_wa[i],_wb[j]) ? _wa[i++] : _wb[j++];
    for(;i<ta;p++) sa[p] = _wa[i++];
    for(;j<tbc;p++) sa[p] = _wb[j++];
    return;
}//*/



/*
 * da�����е�mҪС��SIZE��
 * m���Կ��ܴ�ǰ����SIZE ҲҪ���ܴ�
 */
///*
//�������飬���»��߿�ͷ
int _wa[SIZE],_wb[SIZE],_wv[SIZE],_ws[SIZE];
//��������
int _cmp(int const r[],int a,int b,int l){return r[a]==r[b]&&r[a+l]==r[b+l];}
//���׺����ı����㷨
//r: Դ���飬�ҳ�r[n-1]�⣬����r[i]>0
//n: r�ĳ���
//m: r�е�Ԫ��ȡֵ���Ͻ磬������r[i]<m
//sa:��׺���飬�����
void da(int const r[],int n,int m,int sa[]){
    int i,j,p,*x=_wa,*y=_wb,*t;
    for(i=0;i<m;i++) _ws[i] = 0;
    for(i=0;i<n;i++) _ws[x[i] = r[i]]++;
    for(i=1;i<m;i++) _ws[i] += _ws[i-1];
    for(i=n-1;i>=0;i--) sa[--_ws[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p){
        for(p=0,i=n-j;i<n;i++) y[p++]=i;
        for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0;i<n;i++) _wv[i]=x[y[i]];
        for(i=0;i<m;i++) _ws[i]=0;
        for(i=0;i<n;i++) _ws[_wv[i]]++;
        for(i=1;i<m;i++) _ws[i] += _ws[i-1];
        for(i=n-1;i>=0;i--) sa[--_ws[_wv[i]]] = y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=_cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}//*/

//����rank������height����
//r:  Դ����
//sa: ��׺����
//n:  Դ����ĳ���
//rank: rank���飬��������
//height: height���飬��������
void calHeight(int const r[],int const sa[],int n,int rank[],int height[]){
    int i,j,k=0;
    for(i=1;i<n;i++) rank[sa[i]]=i;
    for(i=0;i<n-1;height[rank[i++]]=k)
    for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    return;
}

/**<  ��Ҫ��������Сֵ��ֻҪ��max����min */
//int a[200010] ; // ԭ����
//const int rmq_size = log2(SIZE)+1;
int _RMQ[SIZE][20]; //Ԥ��������
void getRMQ( int const a[] ,int n ){
    for (int i = 0;i < n;++i) _RMQ[i][0] = a[i];
    for (int j = 1;(1<<j) <= n;++j )
        for (int i = 0;i+(1<<j) <=n;++i )
            _RMQ[i][j] = min( _RMQ[i][j-1] ,_RMQ[i+(1<<(j-1))][j-1] ) ;
}
int querry(int A,int B){
    int k = (int)(log((double)(B+1-A))/log(2.0));
    return min( _RMQ[A][k] , _RMQ[B+1-(1<<k)][k] );
}
// =================== code line ==========================//


int R[SIZE],SA[SIZE];
int Rank[SIZE],Height[SIZE];

int LCP( int l ,int r ){
    l = Rank[l] , r = Rank[r];
    if ( l > r )swap(l,r);
    return querry(l+1,r);
}

//int SIZE = 105000;
//char part[SIZE],tar[SIZE];
//int EkmpNext[SIZE],extend[SIZE],Next[SIZE];
int n,t,kase = 1;
char str[SIZE];
//char S[SIZE],T[SIZE];
//int tar[SIZE],part[SIZE];
//int ans[SIZE];
//int nub[SIZE];

int main() {
//    scanf("%d",&t);
//    while( t-- ){
    while(scanf("%s",str) != EOF ){
        int mid = strlen(str);
        str[mid] = 'a';
        scanf("%s",str+mid+1);
//        deBug(str);
        int len = strlen(str);
        for (int i = 0;i < len;++i ){
            R[i] = str[i] - 'a' + 1;
        }
        R[mid] = 30;
        R[len++] = 0;

        da(R,len,32,SA);
        calHeight(R,SA,len,Rank,Height);
//        cout << "R :"; dispArray(R,len);
//        cout << "SA :";dispArray(SA,len);
//        cout << "Rank :";dispArray(Rank,len);
//        cout << "Height :";dispArray(Height,len);
        int ans = 0;
        for (int i = 0;i <len;++i ){
            if ( Height [i] > ans ){
                if ( min(SA[i-1],SA[i]) < mid && max(SA[i-1],SA[i] ) > mid )
                    ans = Height[i];
            }
        }

        printf("%d\n",ans);


    }

    return 0;
}


/*
    ios.sync_with_stdio(false);  /// ��ôcin, �Ͳ��ܸ�C�� scanf��sscanf, getchar, fgets֮���һ��ʹ���ˡ�
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
void dispArray( int const a[],int n ) {
//    printf("this array is  ==  > ");
    if( n < 1) puts("");
    printf("%d",a[0]);
    for (int i = 1 ; i < n; ++i )printf(" %2d",a[i]);
    puts("");
}
