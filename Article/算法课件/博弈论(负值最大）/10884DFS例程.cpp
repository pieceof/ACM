#include <stdio.h>

char Board[4][4];

#define true 1
#define false 0

int isVic(char ch){
	int i,j;
	//右、右下、下三种可能
	for(i=0;i<=1;i++)for(j=0;j<=1;j++){
		if ( ch == Board[i][j] ){
			//you
			if ( ch == Board[i][j+1] && ch == Board[i][j+2] )
				return true;
			//xie
			if ( ch == Board[i+1][j+1] && ch == Board[i+2][j+2] )
				return true;
			//xia
			if ( ch == Board[i+1][j] && ch == Board[i+2][j] )
				return true;
		}
	}
	//下、左下的一种可能
	for(i=0;i<=1;i++)for(j=2;j<=3;j++){
		if ( ch == Board[i][j] ){
			if ( ch == Board[i+1][j] && ch == Board[i+2][j] )
				return true;
			if ( ch == Board[i+1][j-1] && ch == Board[i+2][j-2] )
				return true;
		}
	}
	//右
	for(i=2;i<=3;i++)for(j=0;j<=1;j++){
		if ( ch == Board[i][j] ){
			if ( ch == Board[i][j+1] && ch == Board[i][j+2] )
				return true;
		}
	}
	return false;
}

int dfs(int depth,char ch){
	int i,j;
	int failflag = true;
    
	if ( 17 == depth ) return 0;

	for(i=0;i<4;i++)for(j=0;j<4;j++){
		if ( '_' == Board[i][j] ){
            Board[i][j] = ch;
			//如果当前胜利，则胜
			if ( isVic(ch) ){
				Board[i][j] = '_';
				return 1;
			}
			//深搜
			int t = dfs(depth+1,'X'-ch+'O');
			//如果对方失利，则本方胜
			if ( -1 == t ){
                 Board[i][j] = '_';
				return 1;
			}
			//如果存在平局的可能，则本方必然不会败
			if ( 0 == t ) failflag = false;
            Board[i][j] = '_';
		}
	}
    
	//如果从头到尾都没发现胜或者平的可能，那只能输
	if ( failflag ) return -1;

	return 0;
}

int main(){
	int i,j;
	int x_num = 0;
	int o_num = 0;
	int ans;

	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
            Board[i][j] = getchar();
			if ( 'X' == Board[i][j] ){
				x_num++;
			}
			else if ( 'O' == Board[i][j] ) {
				o_num++;
			}
		}
		getchar();
	}

	if ( x_num == o_num ) ans = dfs(x_num+o_num+1,'X');
	else                  ans = dfs(x_num+o_num+1,'O');

	switch(ans){
		case 0:printf("Draw\n");break;
		case 1:printf("Win\n");break;
		case -1:printf("Lose\n");break;
	}

	return 0;
}