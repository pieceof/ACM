#include "../../headers.h"


int tran[20][4] = {
    {0},
    {2},
    {3,5},
    {4,5},
    {0,5},
    {6},
    {7,9},
    {8,9},
    {0,9},
    {10},
    {11,13},
    {12,13},
    {0,13},
    {14},
    {15},
    {16}
};

int tr( char ch ){
    if ( ch <= '9' && ch >= '0' ) return 0;
    if ( ch == '.' ) return 1;
    return 2;
}

int Test(char const* str,int len ){
    int statu = 1;
    for (int i = 0;i < len;++i ){
        statu = tran[statu][ tr(str[i]) ];
        if ( 0 == statu ) return 0;
    }
    if ( statu >= 14 && statu <= 16 ) return 1;
    return 0;
}

bool isin(int x){
    return x >= 0 && x <= 255;
}
char tar[100];
int main(){

    while( gets(tar) ){
        if ( 0 == Test(tar,strlen(tar)) ) {
            printf("NO\n");
            continue;
        }
        int a,b,c,d;
        sscanf(tar,"%d.%d.%d.%d" ,&a,&b,&c,&d);
        if ( !isin(a) || !isin(b) || !isin(c) || !isin(d) ){
            printf("NO\n");
            continue;
        }
        printf("YES\n");
    }

    return 0;
}
