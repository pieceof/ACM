#include <bits/stdc++.h>
using namespace std;

int RandomNumble(int a,int b){
    static int  t = time(0);
    t += 1000 ;
    srand(t);
    return (rand() % (b-a+1) )+a;
}

const int SIZE = 1000;
void mult( int (*x)[SIZE], int *c,int *ret ,int n ){
    for (int i = 0;i < n;++i ){
        ret[i] = 0;
        for (int j = 0;j < n ;++j ){
            ret[i] += x[i][j]*c[j];
        }
    }
}
int a[SIZE][SIZE],b[SIZE][SIZE];
int c1[SIZE],c2[SIZE],c3[SIZE];
int d1[SIZE];
int main(){
    int n;
    ios::sync_with_stdio(false);

    while ( cin>>n && n ){

        for (int i = 0;i < n;++i )for (int j = 0;j < n;++j)cin>>a[i][j];
        for (int i = 0;i < n;++i )for (int j = 0;j < n;++j)cin>>b[i][j];

        bool flag = 1;
        for (int ti = 0;ti < 10;++ti ){
            if ( flag == 0 ) break;
            for (int i = 0;i < n;++i )c1[i] = RandomNumble(1,3);
            mult(a,c1,c2,n);
            mult(a,c2,c3,n);
            mult(b,c1,d1,n);
            for (int i = 0;i < n;++i ){
                if ( c3[i] != d1[i] ) {
                    flag = 0;
                    break;
                }
            }
        }
        if ( flag ) puts("YES");
        else puts("NO");
    }
}
