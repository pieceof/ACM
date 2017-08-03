#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int SIZE = 1000;
int startx[SIZE];
int endx[SIZE];
bool isVis[SIZE];
void just( int t,int n  ) {
    //cout << "t : " << t << endl;
    for( int i = 0 ; i < n;++i ){
        if ( isVis[i] )continue;
        if ( t >= startx[i] && t <= endx[i] ){
            isVis[i] = 1;
        }
    }
}
int Cnt( int n ){
    int ret = 0;
    for (int i = 0 ;i < n;++i ){
        ret += isVis[i];
    }
    return ret;
}
int ALLtime[SIZE+SIZE];
int main()
{
    int n;
    while (scanf("%d",&n)!=EOF){

        for ( int i = 0 ;i < n;++i  ){
            scanf("%d%d",startx+i,endx+i);
            endx[i] += startx[i];
            ALLtime[i*2]=startx[i];
            ALLtime[i*2+1]=endx[i];
        }
        //for (int i = 0 ;i < n+n ;++i ) cout << ALLtime[i] << endl;
        int ans = 0;
        memset(isVis,0,sizeof(isVis));
        just(7,n);
        //cout <<Cnt(n)<<endl;
        for (int i = 0;i < n+n;++i ){
            for (int j = i+1;j < n+n;++j ){
                //int tmp = 0;
                memset(isVis,0,sizeof(isVis));
                just(ALLtime[i],n);
                just(ALLtime[j],n);
                ans = max(ans,Cnt(n));

            }
        }

        printf("%d\n",ans);

    }
    return 0;
}
