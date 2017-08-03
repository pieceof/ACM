#include <bits/stdc++.h>
typedef long long llt;

using namespace std;
const int SIZE = 200050;

int num[SIZE];

int n;
int  check( llt x ){
    llt tmp = 0;
    int cnt = 0;
    int i;
    llt cha = 0;
    for (i = 0 ;i < n;++i ){

        tmp += num[i];
        if ( tmp > x ) cha = tmp-x , tmp -= cha;
        if ( tmp == x ) tmp = 0, cnt++ , i++ ;
    }

    if ( i == n+1 && cnt == 4 && tmp == 0 && cha == 0) return 0;
    if ( cnt < 4 ) return 1;
    else return -1;
}

int main()
{
    //*
        //freopen("test.in", "r", stdin);
        //freopen("cout.txt", "w", stdout);
    //*/
    while ( scanf("%d",&n) != EOF )
    {
        llt sum = 0;
        for (int i = 0 ; i < n;++i ){scanf("%d",num+i); sum+= num[i];}
        llt l = 0,r = sum;

        llt ans = -1;

        while ( l <= r ){
            llt mid = (l+r)>>1;
            llt c  = check( mid );
            if (  c == 0 ){
                ans = mid;
                r = mid-1;
            }
            else if ( c == 1 ) r = mid-1;
            else l = mid+1;
        }

        if ( sum == 0 ) {
            printf("2 4 6\n");
            continue;
        }
        if ( ans == -1  )printf("%d\n",-1);
        else {
            llt tmp = 0;
            int cnt = 0;
            for (int i = 0 ; i < n;++i ){
                tmp += num[i];
                if ( tmp == ans && i+2 < n){
                    if ( cnt == 0)
                        printf("%d",i+2);
                    else
                        printf(" %d",i+2);
                }
                if ( tmp == ans ) tmp = 0,i++,cnt++;
            }
            printf("\n");
        }
    }

    return 0;
}
