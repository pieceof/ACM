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
    //int i = 0, k = -1,n = strlen(P)+1 ; // kmpѭ��ƥ�����һλ
    int i = 0, k = -1,n = strlen(P);
    while( i < n ){
    	while( k >= 0 && P[i] != P[k] )
    		k = Next[k];
    	++i,++k;
    	if ( i == n ) return;
    	Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}
/**< ѭ��kmpƥ���ʱ��Ҫ����һλnext  */
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
            /**< �����ѭ��ƥ�� ֱ��return  */
            return tp-plen;
        }
    }
//    return ans;
    return -1;
}

/*
 *����n���ȵ��ַ������洢�Ǵ�1~n+n+1�� ʵ�ʳ�����n+n+2��
 *ע��size��Χ
 */
const int SIZE =  230000;
int p[SIZE];
void manacher(char *s) //manacher ����
{
    int len=strlen(s);
    for(int i = len;i >= 0;--i) {//��s�����м��#����ͷ��*
        s[i+i+2] = s[i];
        s[i+i+1] = '#';
    }
    s[0] = '*';
    int id,mx = 0;  //mx������idΪ����ʱ��������Զ��λ��
    for(int i = 1;i <= len+len+1;++i ){
        if( mx > i ) p[i] = min(p[2*id-i],mx-i ); //���������Զλ�ô��ڵ�ǰƥ��ĵط�����p[i]ȡmin��id�ĶԳƵ��p��������Զ����-i��
        else p[i] = 1; //���i��mx�ҷ�����p[i]=-1;
        while( s[i-p[i]] == s[i+p[i]] ) ++p[i];   //�ж�i���ĳ���
        if( i + p[i] > mx ) {//���Ƿ�Ҫ������Զ���룬���Ҫ�����˵���Ϊ���ġ�
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
    ios.sync_with_stdio(false);  /// ��ôcin, �Ͳ��ܸ�C�� scanf��sscanf, getchar, fgets֮���һ��ʹ���ˡ�
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
void dispArray( int *a ,int n ){
//    printf("this array is  ==  > ");
    if( n < 1) puts("");
    printf("%d",a[0]);
    for (int i = 1 ;i < n;++i )printf(" %d",a[i]);puts("");
}
