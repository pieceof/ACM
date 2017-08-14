//#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <climits>
#include <iostream>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
//#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl
#define Case printf("Case %d:\n",kase++)
#define Ans(x) printf("%d\n",(x))
#define readfile(path) freopen( (path) , "r", stdin )
#define writefile(path) freopen( (path) , "w", stdout )
#define deBug(x,y) cout << "(" << x << "," << y << ")" << endl;
using namespace std;
void ArrayCin( int *a ,int n ,int pos = 0){
    for (int i = pos;i < n;++i ) scanf("%d",a+i);
}
void ArrayDisp(int *a,int n ){
    printf("== > : ");
    for (int i = 0;i < n;++i )printf("%4d ",a[i]);printf("\n");
}

/// ------------------------------ code line ------------------------------//

int const SIZE_OF_COLS = 1024+100;
int const SIZE_OF_ROWS = 4096+100;

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
int AnsRows[SIZE_OF_ROWS];


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
//        Rth[i] = 0;
        Cth[i] = i;
    }
    /**< 首位相连,做成双向循环链表 */
    Left[0] = cols;
    Right[cols] = 0;

    toUsed = cols;
    Rhead[0] = 0;
    /**< 清空每row的头指针 */
    fill(Rhead+1,Rhead+rows+2,-1);
    ans = -1;
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
void _remove( int node ){
    /**< 断开该节点的左右链 */
    Right[ Left[node] ] = Right[node];
    Left[ Right[node] ] = Left[node];

    /**< 根据算法的描述 ,此处应该去掉这个节点所在列col
        以及 在col列上有节点的每一行 */
    /**< 枚举这列上的节点 */
    for (int i = Down[node] ; i != node ;i = Down[i] ){
        /**< 再枚举这个节点所在行上的节点 */
        for (int j = Right[i] ; j != i;j = Right[j] ){
            /**< 将这些节点去掉 */
            /**< 所谓删除就是把上下关系删去 , 因为在 dlx函数里面是
                    从列上循环枚举行  */
            Up[ Down[j] ] = Up[j];
            Down[ Up[j] ] = Down[j];
            /**< 这个节点所在列的计数-1 */
            -- Ccnt[ Cth[j] ];
        }
    }
}
/**
 * 注意删除操作只是整体的删除了一部分,只是在第0行上删除了左右关系
 * 其他节点删了上下的关系(注意这个关系是被指向的关系,因为存的时候是双向关系,
 * 所以这个节点指出去的关系没有删除 )
 * 而且处于列循环上的节点什么都没删,整体的内部的结构没有改变,
 * 所以恢复起来没那么麻烦,只要记录了 删除这个操作的发起点(即那一列)
 * 然后顺着这个发起点 依次恢复即可.
 * 设剩下的节点为S2,(删除的部分为S1), 删除这个操作,本质上来说就是
 * S1 能看到S2 , 但是S2看不到S1了, 断开的链只是 S2=>S1的, S1=>S2 上的链一个都没变
 */

void _resume( int node ){
    /**< 先恢复这个节点的左右关系 */
    Left[Right[node]] = Right[Left[node]] = node;

    /**< 与删除的逻辑一样 ,顺着恢复即可 */
    for (int i = Up[node]; i != node ;i = Up[i] )
        for (int j = Left[i]; j != i;j = Left[j] )
            Up[ Down[j] ] = Down[ Up[j] ] = j ,
                Ccnt[ Cth[j] ]++;
}
/** \dlx 的返回值类型
 * 如果需要求得答案(如数读) ,bool型,只要一个解即可
 * 如果只是数量 void型
 * void型在第一次搜索到答案后会继续搜索,这样就会覆盖答案,
 * 但能求得多个可行解
 */
bool dlx( int d ){
    /**< 如果已经搜索到答案过,并且当前已经 > ans, 就不用继续了 */
//    if ( ans != -1 && ans <= d )return;
    /**< 能搜到底的肯定比ans小 */
    if ( Right[0] == 0 ){
        ans = d;
//        return;
        return true;
    }
    int col, tmp = INT_MAX;
    /**< 选择含1最少的列,回溯会少 */
    for (int i = Right[0]; i != 0;i = Right[i] )
        if ( Ccnt[i] < tmp && 1 == ( tmp = Ccnt[col=i] ) )break;
    _remove(col);
    /**< 枚举行 */
    for (int i = Down[col];i != col ;i = Down[i] ){
        AnsRows[d] = Rth[i];
        /**< 该行node 覆盖的列删去 */
        /**< 因为是精确覆盖,所以这些列上的点所在的行也要删去  */
        for (int j = Right[i]; j !=  i; j = Right[j] ) _remove(Cth[j]);
//        dlx(d+1);
        if ( dlx(d+1) ) return true;
        for (int j = Left[i]; j != i; j = Left[j] ) _resume(Cth[j]);
    }
    _resume(col);
    return false;
}
///--------------------------- code line ------------------------------//

/**< 一个小格的宽度 */
int const subSize = 3;
/**< 每行小格的个数 ,这里没遇到过 != subSize 所以先默认相等*/
int const subCnt = 2;
/**< 整个数独的宽度 */
int const allSize = subSize*subSize;
int mat_row[SIZE_OF_ROWS];
int mat_col[SIZE_OF_ROWS];
int shu[SIZE_OF_ROWS];
/**< base是每次覆盖的行号 ,gridCnt 保证每个格子都有值 */
int base , gridCnt ;
/**< 原数独矩阵(r,c) 位置 value 为v */

inline void _coverPos( int r,int c ,int v ){
    /**< base 为该次覆盖所在的行  */
//    int base = (r*allSize+c)*allSize+v;
    mat_row[base] = r;
    mat_col[base] = c;
    shu[base] = v;

    /**< 这一行覆盖的列有4列, 分别link */

    /**< 先link这个点所在的行 */
    link(base, r*9 + v);                            // deBug( base ,r*9 + v );
    /**< 再link这个点所在的列 */
    link(base, c*9 + v + 1*6*9 );                    //deBug( base ,c*9 + v + 1*6*9 );
    /**< 再link这个点所在的九宫格 */
    int Ncnt = (r/2)*2 + c/3+1; /**<  第几个九宫格 *///deBug(Ncnt,0);
    link(base, (Ncnt-1)*9 + v + 2*6*9 );             //deBug( base ,(Ncnt-1)*9 + v + 2*6*9 );

    /**< 最后link 限制 条件 9*9的每个格 都要有值 */
//    link(base, r*allSize+c+1 + 3*allSize*allSize ); deBug( base ,gridCnt + 3*6*9 );
    link(base , gridCnt + 3*6*9 );                   //deBug( base ,gridCnt + 3*6*9 );
    //cout << endl;
    base++;
}
/** dlx 矩阵放置为
 * row 1 (1~9) 2(1~9) .......... count 81 rows
 * col 1 (1~9) 2(1~9) ....9(1~9) count 81 cols
 * nin 1 (1~9) ................. count 81 nine-grid
 * pos 1~81                      count 81 pos
 */
void sudoku(char output [20][20][2] ){
//    CLEAR(output);
    for (int i = 0;i < 6;++i )for (int j = 0;j < 6;++j )output[i][j][0] = output[i][j][1] = '\0';
    base = 1;
    gridCnt = 1;
    char ch[5];
    init( 9*9*9 ,9*6*3 + 9*6 );
    for (int i = 0;i < 6;++i ) for (int j = 0;j < 6;++j,gridCnt++ ){
        scanf("%s",ch);
        // 这个格子一个数
        if ( ch[1] == '\0' ) {
            if ( *ch == '-' )
                // 这个点尝试放置 1~9
                for (int k = 1;k <= 9;++k )
                    _coverPos(i,j,k);
            else
                _coverPos(i, j, *ch-'0');

        // 这个格子两个数
        }else {
            //四种情况
            // 第一个格子确定 第二个确定
            if ( ch[0] != '-' && ch[2] != '-' ){
                _coverPos(i, j, ch[0]-'0');
                gridCnt++;
                _coverPos(i, j, ch[2]-'0');
            }
            // 第一个格子不确定 第二确定
            if ( ch[0] == '-' && ch[2] != '-' ){
                for (int k = 1;k < ch[2]-'0';++k )
                    _coverPos(i,j,k);
                gridCnt++;
                _coverPos(i, j, ch[2]-'0');
            }
            // 第一个格子确定 第二个不确定
            if ( ch[0] != '-' && ch[2] == '-' ){
                _coverPos(i, j, ch[0]-'0');
                gridCnt++;
                for (int k = ch[0]-'0';k <= 9;++k )
                    _coverPos(i,j,k);
            }
            // 第一个格子不确定 第二个不确定
            if ( ch[0] == '-' && ch[2] == '-' ){
                for (int k = 1;k <= 9;++k )
                    _coverPos(i,j,k);
                gridCnt++;
                for (int k = 1;k <= 9;++k )
                    _coverPos(i,j,k);
            }
        }

    }
    int np = dlx(0);
//    cout << np << endl;
//    sort(AnsRows,AnsRows+ans);
//    for (int i = 0,cnt = 0;i < allSize;++i ){
//        for (int j = 0;j < allSize;++j )
//            printf("%d", AnsRows[cnt++]-(j*allSize+i)*allSize );
//        printf("\n");
//    }
//    cout << ans << endl;
    for (int i = 0,k = 0;i < 6;++i ){
        for (int j = 0;j < 9;++j ){
            int &a = AnsRows[k++];
            int b = output[ mat_row[a] ][ mat_col[a] ][0];
            if ( b == '\0' )
                output[ mat_row[a] ][ mat_col[a] ][0] = shu[a] + '0';
            else{
                output[ mat_row[a] ][ mat_col[a] ][1] = shu[a] + '0';
                if (output[ mat_row[a] ][ mat_col[a] ][1] <output[ mat_row[a] ][ mat_col[a] ][0]  )
                    swap( output[ mat_row[a] ][ mat_col[a] ][1] , output[ mat_row[a] ][ mat_col[a] ][0] );
            }

        }
//        output[i][allSize][] = '\0';
    }

}

int t,n,m,p;

const int SIZE = 2000;
//char str[SIZE];
char out[20][20][2];
//inline bool read(){
////    if ( t-- == 0 )return false;
//
//    if (  EOF == scanf("%s",str) ) return false;
//    if ( *str == 'e' )return false;
//    return true;
////    return true;
//}
int main(){
//    writefile("out.txt");
    scanf("%d",&t);while ( t-- ){
//    while ( read() ){
        int k ;
        scanf("%d",&k);
        printf("%d\n",k);
        sudoku(out);
//        printf("\n");
        for (int i = 0;i < 6;++i ){
            for (int j = 0;j < 6;++j ){
                printf("%c",out[i][j][0]);
                if ( out[i][j][1] != '\0' )
                    printf("/%c ",out[i][j][1]);
                else printf(" ");
            }printf("\n");
        }

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
}
*/

