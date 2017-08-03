#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <climits>
#include <stdlib.h>
//stl
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <complex>
#include <string>
#include <vector>
#include <bitset>

//define
#define MOD  1000000007
#define INF 1<<30
#define EPS 1e-13
#define S(r) r*r*PI
#define PI acos(-1.0)
#define UP(i,x,y) for(llt i=x;i<=y;i++)
#define MEM(a,x) memset(a,x,sizeof(a))

using namespace std;
typedef map<int,int>::iterator mii_iter;
typedef map<int,string>::iterator mis_iter;
typedef map<string,string>::iterator mss_iter;
typedef map<int,vector<int> >::iterator mivi_iter;
typedef vector<int>::iterator vi_iter;
typedef vector<string>::iterator vs_iter;
typedef string::iterator s_iter;
typedef long long llt ;
/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/
const int SIZE = 10;
vector < pair<int,int > > tile;
map< pair<int,int> ,int > isUsed;

int chess[SIZE][SIZE];
//int IsFill[SIZE][SIZE];
//bool cmp( pair<int,int> const&a, pair<int,int>const&b ) {
//    return a.first < b.first;
//}
inline void disPlay( );
#define Pos(ch) ((i)-'A'+1)
#define Line 1
#define Column 2
int FillCnt = 0;
inline void GetPire( int x,int y ) {
    if ( x > y ) swap(x,y);
    isUsed[ make_pair(x,y) ] = 1;
    //tile.erase( find( tile.begin(),tile.end(),make_pair(x,y)));
}
inline void PushPire( int x,int y ) {
    if ( x > y ) swap(x,y);
    isUsed[ make_pair(x,y) ] = 0;
    //tile.push_back(make_pair(x,y));
}
inline bool CheckPos( int x, int y ) {
    if ( chess[x][y] != 0 ) return false;
    if ( x == 9 )return chess[x][y+1] == 0 ;
    if ( y == 9 )return chess[x+1][y] == 0 ;
    return chess[x+1][y] == 0 || chess[x][y+1] == 0 ;
}
inline bool CheckLine( int li,int x,int y=-1 ) {
    for ( int i = 1; i <= 9 ; ++i )
        if ( chess[li][i] == x || chess[li][i] == y )
            return false;
    return true;
}
inline bool CheckColumn( int col,int x,int y=-1 ) {
    for ( int i = 1; i <= 9; ++i )
        if ( chess[i][col] == x || chess[i][col] == y )
            return false;
    return true;
}
inline bool CheckCell( int i,int j,int x) {
    int si = (i % 3 == 0) ? i/3-1 : i/3;
    int sj = (j % 3 == 0) ? j/3-1 : j/3;
    for (int ti = si*3 + 1; ti <= si*3 + 3; ++ti )
        for ( int tj = sj*3 + 1; tj <= sj*3 + 3; ++tj )
            if ( chess[ti][tj] == x ) return false;
    return true;
}
inline bool check( int i ,int j ,int x,int y ,int Pattern ){

    if ( CheckCell( i,j,x ) == 0  ) return false;
    if ( Pattern == Line ){
        if (
            CheckCell(i,j+1,y) &&
            CheckLine(i,x,y) &&
            CheckColumn(j,x) &&
            CheckColumn(j+1,y))
            return true;
        return false;
    }
    if ( Pattern == Column ){
        if ( CheckColumn(j,x,y) &&
            CheckCell(i+1,j,y)&&
            CheckLine(i,x) &&
            CheckLine(i+1,y))
            return true;
        return false;
    }
}
inline void Reset( int i,int j,int Pattern) {
    int x  = chess[i][j];
    chess[i][j] = 0;
    int si = (Pattern == Line) ? i : i+1 ;
    int sj = (Pattern == Line) ? j+1 : j ;
    int y = chess[si][sj];
    chess[si][sj] = 0 ;
    FillCnt -= 2;
    PushPire(x,y);
}
inline bool Fill( int i, int j,int x,int y,int Pattern) {
    int fi = i;
    int fj = j;
    int si = (Pattern == Line) ? i : i+1 ;
    int sj = (Pattern == Line) ? j+1 : j ;

    if ( si > 9 || sj > 9 ) return false;
    if ( chess[si][sj] ) return false;

    if ( check(fi,fj,x,y,Pattern) ){
        chess[fi][fj] = x , chess[si][sj] = y;
        GetPire(x,y);
        FillCnt += 2;
        return true;
    }
    return false;
}
bool isok = 1;
void dfs( int ni,int nj ) {
    //disPlay() ;
    if ( ni > 9 ) {
        if ( FillCnt >= 81 && isok ){
            disPlay();
            isok = 0;
        }
        return;
    }
    int tx,ty;
    if ( nj > 9 ){
        dfs(ni+1,1);
        return ;
    }
    if ( chess[ni][nj] != 0 ){
        dfs(ni,nj+1);
        return ;
    }
    if ( 1 == CheckPos(ni,nj) ) {
        for ( auto i : tile ) {

            if ( isUsed[i] == 1 ) continue;
            tx = i.first;
            ty = i.second;

            if ( Fill(ni,nj,tx,ty,Line) ){
                dfs(ni,nj+2);
                Reset(ni,nj,Line);
            }
            if (  Fill(ni,nj,tx,ty,Column) ){
                dfs(ni,nj+1);
                Reset(ni,nj,Column);
            }
            swap(tx,ty);
            if ( Fill(ni,nj,tx,ty,Line) ){
                dfs(ni,nj+2);
                Reset(ni,nj,Line);
            }
            if ( Fill(ni,nj,tx,ty,Column) ){
                dfs(ni,nj+1);
                Reset(ni,nj,Column);
            }
        }
    }
}

void init ( ) {
    tile.clear();
    isUsed.clear();
    for (int i = 1 ; i <= 9 ; ++i ) {
        for (int j = i+1; j <= 9; ++ j ) {
            tile.push_back( make_pair(i,j));
            isUsed[ make_pair(i,j) ] = 0;
        }
    }
    isok = 1;
    memset( chess, 0,sizeof ( chess ) ) ;
//    memset( IsFill,0,sizeof ( IsFill) ) ;
    FillCnt = 0;
}

int main() {
    //freopen( "in.txt","r",stdin);
    //freopen( "out.txt", "w",stdout);
    int n;
    int kase = 1;
    while( scanf("%d",&n ) && n ) {
        init();
        int x,y;
        char ch1[3],ch2[3];
        int ti,tj;
        for (int i = 0; i < n; ++i ) {
            scanf("%d %s %d %s",&x,ch1,&y,ch2);
//            cout << x << " " << ch1 << " " << y << " " << ch2 << endl;
            ti = ch1[0]-'A'+1  ,  tj = ch1[1]-'1'+1;
            chess[ti] [tj] = x;
            ti = ch2[0]-'A'+1  ,  tj = ch2[1]-'1'+1;
            chess[ti] [tj] = y;
            FillCnt += 2;
            if ( x > y ) swap(x,y);
            tile.erase( find( tile.begin(),tile.end(),make_pair(x,y)));

            isUsed.erase( make_pair(x,y) );
            //isUsed[ make_pair(x,y) ] = 1;
        }
        for (int i = 1; i <= 9 ; ++i ) {
            scanf("%s",ch1);
            ti = ch1[0]-'A'+1 , tj = ch1[1]-'1'+1;
            chess[ti] [tj] = i;
            FillCnt++;
        }
        //cout << FillCnt <<endl;
        //disPlay();

        //cout << Check(1,1,3,4,Line)<<endl;
        printf("Puzzle %d\n",kase++);
        dfs(1,1) ;

        //cout <<123<<endl;
    }

    return 0;
}


inline void disPlay( ) {
    for (int i = 1; i <= 9; ++i ) {
        for (int j = 1; j <= 9; ++j ) {
            cout <<chess[i][j];
        }
        cout <<endl;
    }
    //for ( auto i : tile )cout << i.first << " " << i.second << endl;
    //for ( auto i : isUsed)cout << "<" << i.first.first << " , " << i.first.second <<"> : " << i.second << endl;
}
