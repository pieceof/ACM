#include <bits/stdc++.h>
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
template<class T> inline T pow2( T const&x ){ return x*x; }
inline double ln(double const&x ){ return log(x)/log(exp(1));}
inline double Vfrustum( double const&r1,double const&r2,double const&h ){
    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
}
void ArrayCin( int *a ,int n ,int pos = 0){
    for (int i = pos;i < n;++i ) scanf("%d",a+i);
}
void ArrayDisp(int *a,int n ){
//    std::cout << varName(a) << "  : ";
    printf("===> : ");
    for (int i = 0;i < n;++i )printf("%4d ",a[i]);printf("\n");
}

/// ------------------------------ code line ------------------------------//

int const SIZE_OF_COLS = 1010;
int const SIZE_OF_ROWS = 510;

/**< 十字静态链表  */
int Up[SIZE_OF_ROWS*SIZE_OF_COLS];
int Down[SIZE_OF_ROWS*SIZE_OF_COLS];
int Right[SIZE_OF_ROWS*SIZE_OF_COLS];
int Left[SIZE_OF_ROWS*SIZE_OF_COLS];

/**< 保持节点的row,col信息 */
int Rth[SIZE_OF_ROWS*SIZE_OF_COLS];
int Cth[SIZE_OF_ROWS*SIZE_OF_COLS];


//
int Rhead[SIZE_OF_ROWS]; /**< 每列头节点的指针 */
int Ccnt[SIZE_OF_COLS];  /**< 该列节点的个数  */

int toUsed ;
int ans;
//int AnsRows[SIZE_OF_ROWS];
// dlx1 based
void init( int rows ,int cols ){
    /**< 每一列个数置0 */
    fill( Ccnt,Ccnt+cols+1 ,0 );
    /**< 此处第0 row初始化cols个 node , 作为每列链表的head节点 */

    for (int i = 0;i <= cols;++i ){
        /**< 初始化这些列的head节点 */
        Up[i] = Down[i] = i;
        Left[i+1] = i;
        Right[i] = i+1;
        /**< 维护这些节点的(row,col)信息 */
        Rth[i] = 0;
        Cth[i] = i;
    }
    /**< 首位相连,做成双向循环链表 */
    Left[0] = cols;
    Right[cols] = 0;

    toUsed = cols;
    Rhead[0] = 0;
    /**< 清空每row的头指针 */
    fill(Rhead+1,Rhead+rows+2,-1);
//    ans = -1;
    /**< 重复覆盖求最小值 所以此处初始化最大  */
    ans = INT_MAX;
}

// (row,col) = 1
inline void link( int row ,int col ){
    /**< 节点序号 */
    toUsed++;
    /**< 保存节点信息 Node(row ,col) */
    Rth[toUsed] = row;
    Cth[toUsed] = col;
    /**< 这一行列个数+1 */
    ++Ccnt[ col ];

    /**< Down链表头插入 */
    Down[toUsed] = Down[col];
    Down[col] = toUsed;

    /**< 维护Up链 */
    Up[toUsed] = col;
    Up[ Down[toUsed] ] = toUsed;

    /**< 如果这一行还没有节点 */
    if ( Rhead[row] < 0 )
        /**< 将该节点作为这一行的head节点 */
        /**< 此处的head节点跟col的head节点不一样,col的head节点是在初始化的时候添进去的*/
        Rhead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    else {
        /**< 如果这一行已经有了头节点,插在头节点的后面 */
        /**< 注意每一行的第一个节点作为链表的head节点,插入是在head后面做头插入*/
        int const &h = Rhead[row];

        /**< 维护节点右链 */
        Right[toUsed] = Right[h];
        Left[ Right[h] ] = toUsed;
        /**< 维护节点左链 */
        Left[toUsed] = h;
        Right[h] = toUsed;
    }
}

/**< 删除这个节点 */
void remove( int node ){
    /**< 因为是重复覆盖, 所以此处只删除这列上的节点*/
    /**< 枚举这列上的节点 */
    for (int i = Down[node] ; i != node ;i = Down[i] )
        /**< 所谓删除 只是删除左右链的被指向指针 */
        Left[Right[i]] = Left[i] , Right[Left[i]] = Right[i];
}

void resume( int node ){
    /**< 与删除的逻辑一样 ,顺着恢复即可 */
    for (int i = Up[node]; i != node ;i = Up[i] )
        /**< 所以恢复只是修复一下被指向指针 */
        Left[Right[i]] = Right[Left[i]] =  i;
}

bool Flag[SIZE_OF_COLS] = {false};

/**< 估价函数f意义为从当前状态最好情况下需要添加几条边才能覆盖 */
/**< 这个估计的下界其实 远小于真正需要行数(下界) */
/**< 这个函数的返回值不唯一,但都小于真正的下界  */
int f(){
    int ret = 0;
    /**< 标记一下没有覆盖的col */
    for (int i = Right[0];i != 0;i = Right[i] )Flag[i] = true;

    /**< 枚举所有列 */
    for (int i = Right[0];i != 0;i = Right[i] )
        /**< 如果没被标记,就需要一个row来覆盖 */
    if ( Flag[i] == true ){
        ret++;
        Flag[i] = false;
        /**< 这列上的点所在的行覆盖的列全都覆盖上 */
        for (int j = Down[i];j != i;j = Down[j] )
            for (int k = Right[j];k != j;k = Right[k] )
                Flag[ Cth[k] ] = false;
    }
    return ret;
}



void dlx( int d ){
    /**< 如果估计下界都大于ans 就不用继续了 */
    if ( d + f() <= ans )return;
    if ( Right[0] == 0 ){
        /**< 更新一下ans */
//        if ( d < ans )
            ans = max(ans,d);
        return;
//        return true;
    }
    int col, tmp = INT_MAX;
    /**< 选择含1最少的列,回溯会少 */
    for (int i = Right[0]; i != 0;i = Right[i] )
        if ( Ccnt[i] < tmp && 1 == ( tmp = Ccnt[col=i] ) )break;

    /**< 枚举行 */
    for (int i = Down[col];i != col ;i = Down[i] ){
//        AnsRows[d] = Rth[i];
        /**< 该行node 覆盖的列删去 */
        remove(i);
        /**< 因为是重复覆盖,所以只删除这些列 */
        for (int j = Right[i]; j != i; j = Right[j] ) remove(j);
        dlx(d+1);
        for (int j = Left[i]; j != i; j = Left[j] ) resume(j);
        resume(i);
    }
}
////------------------------------------------------

int n ;
const int SIZE = 10000;
typedef long long llt;
llt a[SIZE];

bool read(){
    if ( EOF == scanf("%d",&n) )return false;
    for (int i = 0;i < n;++i )
        scanf("%lld",a+i);
    return true;
}
void solve(  ){
    init(n,n);
    for (int i = 0;i < n;++i ){
        for ( int j = 0;j < n;++j ){
            if ( a[i]%a[j] == 0 || a[j]%a[i] == 0 ){
                link(i+1,j+1);
//                printf("(%d,%d)\n",i+1,j+1);
            }

        }
    }
    ans = 0;
    dlx(0);
}
int main(){
//    writefile("out.txt");
    int t;scanf("%d",&t);while ( t-- ){
//    while (  ){
        read();
        solve();
        printf("%d\n",ans);

    }
    return 0;
}


////////////////////////////////////
/*
void dispNode( int node ){
    printf("%d:(%d,%d)(%d,%d,%d,%d)\n",
           node,Rth[node],Cth[node],Up[node],Down[node],Left[node],
           Right[node]);
}
void dispCol( int col ){
    dispNode(col);
    for (int c = Down[col] ;c != col;c = Down[c] )
        dispNode(c);
}
void dispRow( int row ){
    int h = Rhead[row];
    dispNode(h);
    for (int r = Right[h]; r != h;r = Right[r] )
        dispNode(r);
}
void disp( char const *p ){
    printf("cross:\n");
    if ( 'r' == *p ){
        for (int r = 0;Rhead[r] != -1;++r ) dispRow(r);
    }else if ( 'c' == *p ){
        dispNode(0);
        for (int i = Right[0]; i ;i = Right[i]) dispCol(i);
    }else{
        ;
    }
}//*/
