#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
#include <climits>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d:\n",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;
const double eps = 1e-9;
const double PI = acos(-1);
inline double ln(double const&x ){ return log(x)/log(exp(1));}
inline double Vfrustum( double const&r1,double const&r2,double const&h ){
    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
}
void ArrayCin( int *a ,int n ,int pos = 0){
    for (int i = pos;i < n;++i ) scanf("%d",a+i);
}
void ArrayDisp(int *a,int n ){
    cout << varName(a) << "  : ";
    for (int i = 0;i < n;++i )printf("%4d ",a[i]);printf("\n");
}

/// ------------------------------ code line ------------------------------//

const int SIZE = 2000000;
///*
struct node_t {
    node_t* child[26];//26个儿子
//    int idx;//对应解释的序号
    bool suffix ;//是否为后缀
//    int cnt;
} Node[SIZE];
int toUsed = 1;

//插入单词
void insert(char const word[] ) {
    node_t* loc = Node;
    for(int i = 0; word[i] ; ++i) {
//        loc->cnt++;
        int sn = word[i] - 'a';
        if ( !loc->child[sn] ) loc->child[sn] = Node + toUsed ++;
        loc = loc->child[sn];
    }
//    loc->cnt++;
    loc->suffix = 1;
}
//查找单词,返回出现的次数
int find(char const word[]) {
    node_t* loc = Node;
    for(int i = 0; word[i] ; ++i) {
//        if ( loc->suffix ) return 1;
        int sn = word[i] - 'a';
        if ( !loc->child[sn] ) return 0;
        loc = loc->child[sn];
    }
//    return loc->cnt;
    return loc->suffix;
}
//*/
char str[50001][50];
int n = 0 ;

int main(){
    while ( EOF != scanf("%s",str+n) ) insert(str[n++]);
    char ch = '\0';
    int flag;
    for (int i = 0;i < n;++i ){
        int len = strlen(str[i]);
        for ( int j = 1;j < len;++j ){
            swap(str[i][j] , ch );
            flag = find(str[i]);
            swap(str[i][j] , ch );
            if ( !flag ) continue;
            if ( !find(str[i]+j) ) continue;
            printf("%s\n",str[i]); break;
        }
    }

    return 0;
}
