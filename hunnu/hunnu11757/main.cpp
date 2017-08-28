//#include "../../headers.h"
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int SIZE = 5100;
bool Left[SIZE];
bool Right[SIZE];
int Leftcnt[SIZE];
int Rightcnt[SIZE];
char str[SIZE];
int main(){
    while( scanf("%s",str) != EOF ){
        int len = strlen(str);
        int l = 0;
        bool flag = 1;
        for (int i = 0;i < len;++i ){
            if ( str[i] == '(' )l++;
            else l--;
            if ( l < 0 ) flag = 0;
            Leftcnt[i] = l;
            Left[i] = flag;
        }

        int r = 0;
        flag = 1;
        for (int i = len-1;i >= 0;--i ){
            if ( str[i] == '(' )r++;
            else r--;
            if ( r > 0 ) flag = 0;
            Rightcnt[i] = r;
            Right[i] = flag;
        }
        Rightcnt[len] = 0;
        Right[len] = 1;
        bool isok = 0;
        if ( Right[0] && Left[len-1] ) isok = 1;
        for (int i = 0;i < len;++i ){
            if ( isok ) break;
            if ( i == 0 || Left[i-1] ){
                int cc;
                if ( i == 0 )cc=0;
                else cc = Leftcnt[i-1];
                int j = i;
                while ( j < len ){
                    if ( str[j] == ')' )cc++;
                    else cc--;
                    if ( cc < 0 ) break;
                    if ( Right[j+1] )if ( Rightcnt[j+1] + cc == 0 ){
                        isok = 1;
                    }
                    j++;
                }
            }
        }
        if ( isok ) printf("possible\n");
        else printf("impossible\n");

    }
    return 0;
}
