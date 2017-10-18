#include "../../headers.h"

int tran[50][3];

void init() {
    CLEAR(tran);
    for (int i = 1; i < 40 ; ++i ) tran[i][0] = i+1;
    for (int i = 1; i < 8; ++i )
        tran[i*5][0] = 0, tran[i*5][1] = i*5+1;
    for (int i = 1; i < 40; i+=10 )
        tran[i+1][1] = tran[i+2][1] = tran[i+3][1] = i+5,
                                      tran[i+6][1] = tran[i+7][1] = tran[i+8][1] = i+10;
    tran[37][1] = tran[38][1] = tran[39][1] = 0;
}
inline bool isin(char x) {
    return (x >= '0' && x <= '9') || (x >= 'a' && x <= 'f') ||(x >= 'A'&&x <= 'F');
}
inline int tr( char ch ) {
    if ( isin(ch) ) return 0;
    if ( ch == ':' ) return 1;
    return 2;
}

int Test(char const* str,int len ) {
    int statu = 1;
    for (int i = 0; i < len; ++i ) {
        statu = tran[statu][ tr(str[i]) ];
        if ( 0 == statu ) return 0;
    }
    return statu;
}

char tar[10000];

int main() {
    init();
    while( scanf("%s",tar) != EOF ) {

        int len = strlen(tar);
        int Colon = 0 ;
        int doubColon = 0;
        int DCidx = 0;

        for( int i = 0; i < len; ++i ){
            if ( tar[i] == ':' ) {
                Colon ++;
                if (tar[i+1] == ':' ) doubColon ++ , DCidx = i+1;
            }
        }

        if ( doubColon > 1              || /*!< 去掉两个:: */
            ( doubColon==0 && Colon !=7)||
            ( doubColon==1 && Colon > 8 )){ /*!< 去掉 */
            printf("No\n");
            continue;
        }

        /*!< 把:: 变成: ,如果在起始位置直接删除 */
        int st = 0;
        if ( doubColon == 1 ) {
            len --;
            for (int i = DCidx; i < len; ++i ) tar[i] = tar[i+1];
            if (DCidx == len) len--;
            if (DCidx == 1 )st++,len--;
        }
        int r = Test(tar+st,len);

        if (   (doubColon==0 && r>=37 &&r <= 40)
            || (doubColon==1 && r&&(r==1||r%5!=1)&&r<=35) ) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }

    }
    return 0;
}
