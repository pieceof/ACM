#include "../../headers.h"
int const SIZE = 1000000+400;
double bits[SIZE];
void pre( ){
    bits[1] = log10(1);
    for (int i = 2;i < SIZE;++i ){
        bits[i] = bits[i-1] + log10(i);
    }

}
char str[SIZE];

int main(){
    pre();
//    ArrayDisp(bits,100);

    while ( scanf("%s",str ) != EOF ){
        int len = strlen( str );
        if (len == 1 ){
            if ( *str == '1' )Ans(1);
            if ( *str == '2' )Ans(2);
            if ( *str == '6' )Ans(3);
            continue;
        }
        int ans = 0;
        for (int i = 1;i < SIZE;++i ){
            if ( len-1 == (int)bits[i] ){
                ans = i;
                break;
            }
        }
        Ans(ans);
    }
    return 0;
}
