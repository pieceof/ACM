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
//const double eps = 1e-9;
//const double PI = acos(-1);
//inline double ln(double const&x ){ return log(x)/log(exp(1));}
//inline double Vfrustum( double const&r1,double const&r2,double const&h ){
//    return PI * h * ( r1*r1 + r2*r2 + r1*r2 )/3;
//}
//void ArrayCin( int *a ,int n ,int pos = 0){
//    for (int i = pos;i < n;++i ) scanf("%d",a+i);
//}
//void ArrayDisp(int *a,int n ){
////    std::cout << varName(a) << "  : ";
//    printf("===> : ");
//    for (int i = 0;i < n;++i )printf("%4d ",a[i]);printf("\n");
//}

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
}

*/


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
        //Rth[i] = 0;
        Cth[i] = i;
    }
    /**< 首位相连,做成双向循环链表 */
    Left[0] = cols;
    Right[cols] = 0;

    toUsed = cols;
    /**< 清空每row的头指针 */
    fill(Rhead+1,Rhead+rows+2,-1);
    ans = -1;
}

// (row,col) = 1
inline void link( int row ,int col ){
    toUsed++;
    /**< save Node(row ,col) */
    Rth[toUsed] = row;
    Cth[toUsed] = col;
    /**< 这一行列个数+1 */
    ++Ccnt[ col ];

    /**< Down链表头插入 */
    Down[toUsed] = Down[col];
    Up[ Down[toUsed] ] = toUsed;


    /**< 维护Up链 */
    Up[toUsed] = col;
    Down[col] = toUsed;

    /**< 如果这一行还没有节点 */
    if ( Rhead[row] < 0 )
        /**< 将该节点作为这一行的head节点 */
        /**< 此处的head节点跟col的head节点不一样,col的head节点是在初始化的时候添进去的*/
        Rhead[row] = Left[toUsed] = Right[toUsed] = toUsed;
    else {
        /**< 如果这一行已经有了头节点,插在头节点的后面 */
        /**< 注意每一行的第一个节点作为链表的head节点,插入是在head后面做头插入*/
        int const &h = Rhead[row];
        /**< 维护toUsed右边的两个指针 */
        Right[toUsed] = Right[h];
        Left[ Right[h] ] = toUsed;
        /**< 维护toUsed左边的两个指针 */
        Left[toUsed] = h;
        Right[h] = toUsed;
    }
}

/**< 删除这个节点 */
void remove( int node ){
    /**< 只断开Left , Right链 与 node的链接 */
    Right[ Left[node] ] = Right[node];
    Left[ Right[node] ] = Left[node];

    /**< 根据算法的描述 ,此处应该去掉这个节点所在列col
        以及 在col列上有节点的每一行 */
    /**< 先列循环这一列上的节点 */
    for (int i = Down[node] ; i != node ;i = Down[i] ){
        /**< 再右循环这个节点所在行上的节点 */
        for (int j = Right[i] ; j != i;j = Right[j] ){
            /**< 将这些节点去掉 */
            Up[ Down[j] ] = Up[j];
            Down[ Up[j] ] = Down[j];
            /**< 这个节点所在列的计数-1 */
            -- Ccnt[ Cth[j] ];
        }
    }
}
/**
 * 注意删除操作只是整体的删除了一部分,对于删除的这些节点要么删了左右的关系,
 * 要么删了上下的关系(注意这个关系是被指向的关系,存的时候是双向关系),
 * 而且处于列循环上的节点什么都没删,整体的内部的关系没有改变,
 * 所以恢复起来没那么麻烦,只要记录了 删除这个操作的发起点
 * 然后顺着这个发起点 依次恢复即可.
 * 相对于 剩下的节点 S2,(删除的部分S1), 删除这个操作,本质上来说就是
 * S1 能看到S2 , 但是S2看不到S1了, 断开的链只是 S2的, S1上的链一个都没变
 */

void resume( int node ){
    /**< 先恢复这个节点的左右关系 */
    Left[Right[node]] = Right[Left[node]] = node;

    /**< 与删除的逻辑一样 ,顺着恢复即可 */
    for (int i = Up[node]; i != node ;i = Up[i] )
        for (int j = Left[i]; j != i;j = Left[j] )
            Up[ Down[j] ] = Down[ Up[j] ] = j ,
                Ccnt[ Cth[j] ]++;
}

void dlx( int d ){
    if ( ans != -1 && ans <= d )return;
    if ( Right[0] == 0 ){
        ans = d;
        return;
//        return true;
    }
    int col, tmp = INT_MAX;
    /**< 选择含1最少的列,回溯会少 */
    for (int i = Right[0]; i != 0;i = Right[i] )
        if ( Ccnt[i] < tmp && 1 == ( tmp = Ccnt[col=i] ) )break;
//    disp("r");
    remove(col);
//    disp("r");
    //col
    for (int i = Down[col];i != col ;i = Down[i] ){
//        AnsRows[d] = Rth[i];
        for (int j = Right[i]; j != i; j = Right[j] ) remove(Cth[j]);
        dlx(d+1);
//        if ( dlx(d+1) ) return true;
        for (int j = Left[i]; j != i; j = Left[j] ) resume(Cth[j]);
    }
    resume(col);
//    return false;
}

int t,n,m,p;
void read(){
//    if ( t-- == 0 )return false;
    scanf("%d%d%d",&n,&m,&p);
    init(p,n*m);int x1,y1,x2,y2;

    for (int k = 1;k <= p;++k ){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        for (int i = x1;i < x2;++i )for (int j = y1;j < y2;++j ){
            link(k,j*n+i+1);
//            printf("(%d,%d)\n",k,j*n+i+1);
        }
    }
//    return true;
}

int main(){
//    writefile("out.txt");
    scanf("%d",&t);
    while ( t-- ){
        read();
        dlx(0);
//        deBug(ans);
        Ans(ans);
//        ArrayDisp(AnsRows, ans );

    }
    return 0;
}

