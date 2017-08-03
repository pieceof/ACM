#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <climits>
#include <map>
#include <string>
using namespace std;
char chess[5][5];
map< string,int > mp;

int just( ){

    for (int i = 0;i < 4;++i ){
        int cnt1 = 1;
        int cnt2 = 1;
        for ( int j = 1;j < 4;++j ){

            if( cnt2 >= 3 || cnt1 >= 3 ) return 1;
            if ( chess[i][j] == chess[i][j-1] && chess[i][j] != '_' )
                cnt1++;
            else cnt1 = 1;
            if ( chess[j][i] == chess[j][i-1] && chess[j][i] != '_' )
                cnt2++;
            else cnt2 = 1;
        }
    }
    if ((chess[0][0] == chess[1][1] && chess[1][1] == chess[2][2] && chess[2][2] != '_' )||
        (chess[1][1] == chess[2][2] && chess[2][2] == chess[3][3] && chess[3][3] != '_' )||
        (chess[0][1] == chess[1][2] && chess[1][2] == chess[2][3] && chess[2][3] != '_' )||
        (chess[1][0] == chess[2][1] && chess[2][1] == chess[3][2] && chess[3][2] != '_' ) )
        return 1;
    if ((chess[3][0] == chess[2][1] && chess[2][1] == chess[1][2] && chess[1][2] != '_' )||
        (chess[2][1] == chess[1][2] && chess[1][2] == chess[0][3] && chess[0][3] != '_' )||
        (chess[3][1] == chess[2][2] && chess[2][2] == chess[1][3] && chess[1][3] != '_' )||
        (chess[2][0] == chess[1][1] && chess[1][1] == chess[0][2] && chess[0][2] != '_' ) )
        return 1;
    return 0;

//  0123
//0 __XX
//1 __OO
//2 ____
//3 ____
}
int isVic(char ch){
	int i,j;
	//右、右下、下三种可能
	for(i=0;i<=1;i++)for(j=0;j<=1;j++){
		if ( ch == chess[i][j] ){
			//you
			if ( ch == chess[i][j+1] && ch == chess[i][j+2] )
				return true;
			//xie
			if ( ch == chess[i+1][j+1] && ch == chess[i+2][j+2] )
				return true;
			//xia
			if ( ch == chess[i+1][j] && ch == chess[i+2][j] )
				return true;
		}
	}
	//下、左下的一种可能
	for(i=0;i<=1;i++)for(j=2;j<=3;j++){
		if ( ch == chess[i][j] ){
			if ( ch == chess[i+1][j] && ch == chess[i+2][j] )
				return true;
			if ( ch == chess[i+1][j-1] && ch == chess[i+2][j-2] )
				return true;
		}
	}
	//右
	for(i=2;i<=3;i++)for(j=0;j<=1;j++){
		if ( ch == chess[i][j] ){
			if ( ch == chess[i][j+1] && ch == chess[i][j+2] )
				return true;
		}
	}
	return false;
}
bool flag = 0;
char ch[3] = "XO";
int dfs ( int depth , int flag ){


    if ( depth == 17 ) return 0;
//    string str = string(chess[0],4) + string(chess[1],4) +
//                 string(chess[2],4) +string(chess[3],4) ;
//    if ( mp.count( str ) ) return mp[str];
//    int tj = just();
    // if ( 2 == tj ) return 2;
    // if ( 1 == tj ) return 1;

    int isLose = 1;
    for (int i = 0 ;i < 4;++i )
        for ( int j = 0;j < 4;++j ){
            if( chess[i][j] != '_' )continue;
            char tc = chess[i][j] ;

            chess[i][j] = flag ? 'X' : 'O' ;
            //char cc = flag ? 'X' : 'O' ;
            if ( isVic(chess[i][j]) ) {
                chess[i][j] = tc;
                return 1;
            }
            int td = dfs( depth + 1 , flag ^ 1 );
            if ( td == -1 ){
                chess[i][j] = tc;
                return 1;
            }
            if ( 0 == td ) isLose = 0;
            chess[i][j] = tc;
        }
    if ( isLose )return  -1;
    return 0 ;
}
int main()
{
    scanf("%s",chess[0] );
        scanf("%s",chess[1]);
        scanf("%s",chess[2]);        scanf("%s",chess[3]);

        int cntx = 0;
        int cnto = 0;        for (int i = 0;i < 4;++i )
        for (int j = 0;j < 4;++j ){
            if( chess[i][j] == 'O' ) cnto++;
            if( chess[i][j] == 'X' ) cntx++;
        }

        //mp.clear();
        // flag == 1 , x move
        flag = cnto >= cntx ? 1 : 0 ;
        int ans = dfs( cnto+cntx+1, flag );
        if ( ans == 1 ) puts("Win");
        if ( ans == 0 ) puts("Draw");
        if ( ans == -1 ) puts("Lose");





    return 0;
}

