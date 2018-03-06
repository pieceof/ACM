#include "../../headers.h"

int isUsed[30];
int table[30];

inline int _tr(char ch ){ return ch-'A';}

void solve(char str[] ){
    int len = strlen(str);
    for (int i = 0; i < len ;++i )if( str[i] == 'J')
        str[i] = 'I';

    int ti = 0;
    for (int i = 0;i < len ;++i ){
        if ( isUsed[_tr(str[i])] ) continue;

        table[ti++] = _tr(str[i]);
        isUsed[_tr(str[i])] = true;
    }
    for (int i = 0;i < 26;++i ){
        if( i == 'J'-'A' )continue;
        if( isUsed[i] ) continue;
        table[ti++] = i;
    }
    for( int i = 0;i < 25;++i ){
        if( i % 5 == 0 && i)printf("\n");
        printf("%c",'A'+table[i]);
    }

}


int main(){
    char str[300];
    while (scanf("%s",str) != EOF )
        solve(str);
    return 0;
}
