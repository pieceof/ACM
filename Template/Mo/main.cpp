#include <cstdio>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>
#include <cstring>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d: ",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
using namespace std;

typedef long long llt;
int const SIZE = 1091100;
int BLOCK_SIZE ;

/**< 记录每次查询 */
struct mo_t{
    int s,e; /**< 左右端点 */
    int idx; /**< 在答案中的位置 */
    friend bool operator <(const mo_t&a,const mo_t&b){
        int ln = a.s / BLOCK_SIZE;
        int rn = b.s / BLOCK_SIZE;
        return ln < rn || ( ln==rn && a.e < b.e );
    }
};

int n,m_query,m_oper;
int A[SIZE]; /**< 源数组 */
int const Q_SIZE = SIZE;
mo_t Mo_query[Q_SIZE];
int Answer[Q_SIZE];
int Cnt[SIZE];
int MoAns;
int cur_left,cur_right; /**< 当前处理区间的游标 */


inline void insert( int n ){
    Cnt[n]++;
    (Cnt[n] == 1 ) ? MoAns ++ :false;
}
inline void remove( int n ){
    (Cnt[n] == 1 ) ? MoAns -- :false;
    Cnt[n]--;
}

void Mo(){
    sort(Mo_query,Mo_query+m_query);
    cur_left = 1;
    cur_right = 0;
    MoAns = 0;
    for (int i = 0;i < m_query;++i ){
        while ( cur_right < Mo_query[i].e ) insert(A[++cur_right]);
        while ( cur_left > Mo_query[i].s  ) insert(A[--cur_left]);
        while ( cur_right > Mo_query[i].e ) remove(A[cur_right--]);
        while ( cur_left < Mo_query[i].s  ) remove(A[cur_left++]);
        Answer[Mo_query[i].idx] = MoAns ;

    }
}

int main(){
    while ( scanf("%d",&n) != EOF ){
        BLOCK_SIZE = (int)sqrt((double)n);
        CLEAR(Cnt);
        for (int i = 1;i <= n;++i ){
            scanf("%d",A+i);
        }
        scanf("%d",&m_query);
        int x,y;
        for (int i = 0;i < m_query;++i ){
            scanf("%d%d",&x,&y);
            if ( y < x )swap(x,y);
            Mo_query[i].s = x;
            Mo_query[i].e = y;
            Mo_query[i].idx = i;
        }
        Mo();
        for (int i = 0;i < m_query;++i )
            Ans(Answer[i]);
    }
    return 0;
}
