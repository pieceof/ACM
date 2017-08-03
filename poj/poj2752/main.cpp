#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <assert.h>
#include <climits>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;


int const SIZE=1000050;

struct node_t{
	node_t* child[30];//26������
//	int idx;//��Ӧ���͵����
    bool suffix;
    int cnt;
}Node[SIZE];
int toUsed = 1;

//idx��ʾ���ʶ�Ӧ���͵����
void insert(char const word[] ){
    node_t* loc = Node;
    for(int i = 0;word[i];++i){
        loc->cnt++;
    	int sn = word[i] - 'a';
    	if ( !loc->child[sn] ) loc->child[sn] = Node + toUsed ++;
    	loc = loc->child[sn];
    }
    loc->cnt++;
//    loc->suffix = 1;
}
//���ҵ��ʣ����ؽ��͵���ţ�0��ʾδ�ҵ�
int find(char const word[]){
    node_t* loc = Node;
    for(int i = 0; word[i] ;++i){
//        if ( loc->suffix ) return 1;
    	int sn = word[i] - 'a';
    	if ( !loc->child[sn] ) return 0;
    	loc = loc->child[sn];
    }
    return loc->cnt;
}


void dispArray( int *a ,int n );

template<class DATA>
void getNext( DATA const P[],int *Next ,int n ){
    Next[0] = 0;
    for (int i = 1;i < n ;++i ){
        int k = Next[i-1];
        while ( k > 0 && P[i] != P[k] )
            k = Next[k-1];
        Next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
    }
}
template<class DATA>
void getKMPNext(DATA const P[],int *Next,int n ){
    Next[0] = -1;
    //int i = 0, k = -1,n++ ; // kmpѭ��ƥ�����һλ
    int i = 0, k = -1;
    while( i < n ){
    	while( k >= 0 && P[i] != P[k] )
    		k = Next[k];
    	++i,++k;
    	if ( i == n ) return;
    	Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

/**< ѭ��kmpƥ���ʱ��Ҫ����һλnext  */
template<class DATA >
int KMP(DATA const T[],int tlen,DATA const P[],int plen,int Next[],int pos=0){
//    int const plen = strlen(P);
//    int const tlen = strlen(T);
    int ans = 0;
    if ( tlen < plen ) return 0;
    int tp = pos, pp = 0;
    while( tp < tlen ){
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
 *����n���ȵ��ַ������洢�Ǵ�1~n+n+1�� ʵ�ʳ�����n+n+2��
 *ע��size��Χ
 */
//const int _SIZE =  SIZE+SIZE;
//int p[_SIZE];
//template<class DATA >
//void manacher(char *s ,int len) //manacher ����
//{
//    for(int i = len;i >= 0;--i) //��s�����м��#����ͷ��*
//        s[i+i+2] = s[i] , s[i+i+1] = '#';
//
//    s[0] = '*';
//    int id , mx = 0;  //mx������idΪ����ʱ��������Զ��λ��
//    for(int i = 1;i <= len+len+1; ++i ){
//        if( mx > i ) p[i] = min(p[2*id-i],mx-i ); //���������Զλ�ô��ڵ�ǰƥ��ĵط�����p[i]ȡmin��id�ĶԳƵ��p��������Զ����-i��
//        else p[i] = 1; //���i��mx�ҷ�����p[i]=-1;
//        while( s[i-p[i]] == s[i+p[i]] ) ++p[i];   //�ж�i���ĳ���
//        if( i + p[i] > mx ) {//���Ƿ�Ҫ������Զ���룬���Ҫ�����˵���Ϊ���ġ�
//            id = i;
//            mx = p[i] + i;
//        }
//    }
//}

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



// =================== code line ==========================//

//int SIZE = 105000;
char part[SIZE],tar[SIZE];
int Next[SIZE];
int n,t;
int kase = 1;
//char str[10050];
//int tar[SIZE],part[SIZE];
int ans[SIZE];
int main(){
//    int t;
//    scanf("%d",&t);
//    while(t--){
//    while( scanf("%d",&n) && n ){
        while ( scanf("%s",part) != EOF){
//        if (kase != 1) puts("");
//        scanf("%s",part);
//        int plen,tlen;
//        scanf("%d%d",&tlen,&plen);
//        for (int i = 0 ;i < tlen;++i ){
//            scanf("%d",tar+i);
//        }
//        for (int i = 0;i < plen;++i ){
//            scanf("%d",part+i);
//        }

        int len = strlen(part);
//        assert(n == len);
        getNext(part,Next,len );
//        dispArray(Next,len);
        int tmp = Next[len-1];
        int cnt = 0;
        ans[cnt++] = len;
        while ( tmp ){
            ans[cnt++] = tmp;
            tmp = Next[tmp-1];
        }
        for (int i = cnt-1;i > 0 ;--i )
            printf("%d ",ans[i]);
        printf("%d\n",ans[0]);;
//        getKMPNext(part,Next,strlen(part));
        //int ans = KMP(tar,strlen(tar),part,strlen(part),Next);

//        if ( ans != -1)ans++;
//        printf("%d\n",ans);
        //printf("%d\n",MinimumRepresentation(str,strlen(str))+1);

    }


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
