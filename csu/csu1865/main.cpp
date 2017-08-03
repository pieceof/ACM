#include <bits/stdc++.h>
using namespace std;a
typedef long long llt ;
const int maxn = 20005;

#define B(n) (1<<n)

#define B0 B(0)
#define B1 B(1)
#define B2 B(2)
#define B3 B(3)
#define B4 B(4)
#define B5 B(5)
#define B6 B(6)
#define B7 B(7)
#define B8 B(8)
#define B9 B(9)
#define Ba B(10)
#define Bb B(11)
#define Bc B(12)
#define Bd B(13)
#define Be B(14)
#define Bf B(15)
#define Bg B(16)
#define Bh B(17)

const int EdegePoint[11][11]={
    ///0  1  2  3  4  5  6  7  8  9  10
/*0*/ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
/*1*/ {0, 0, B0,B1,0, 0, 0, 0, 0, 0, 0},
/*2*/ {0, B0,0, B2,B3,B4,0, 0, 0, 0, 0},
/*3*/ {0, B1,B2,0, 0, B5,B6,0, 0, 0, 0},
/*4*/ {0, 0, B3,0, 0, B7, 0,B9,Ba,0, 0},
/*5*/ {0, 0, B4,B5,B7,0, B8,0, Bb,Bc,0},
/*6*/ {0, 0, 0, B6,0, B8,0, 0, 0, Bd,Be},
/*7*/ {0, 0, 0, 0, B9,0, 0, 0, Bf,0, 0},
/*8*/ {0, 0, 0, 0, Ba,Bb,0, Bf,0,Bg, 0},
/*9*/ {0, 0, 0, 0, 0, Bc,Bd,0, Bg,0, Bh},
/*10*/{0, 0, 0, 0, 0, 0, Be,0, 0, 0, Bh},
};

int state,ans;
int DP[0x3ffff+1];

int move(int edge){
    state |= edge;
    switch (edge){
    case B0: return  (state&B1)&&(state&B2);
    case B1: return  (state&B0)&&(state&B2);
    case B2: return ((state&B0)&&(state&B1))+((state&B4)&&(state&B5));
    case B3: return  (state&B4)&&(state&B7);
    case B4: return (((state&B3)&&(state&B7))+((state&B2)&&(state&B5)));
    case B5: return ((state&B2)&&(state&B4))+((state&B6)&&(state&B8));
    case B6: return  (state&B5)&&(state&B8);
    case B7: return ((state&B3)&&(state&B4))+((state&Ba)&&(state&Bb));
    case B8: return ((state&B5)&&(state&B6))+((state&Bc)&&(state&Bd));
    case B9: return  (state&Ba)&&(state&Bf);
    case Ba: return ((state&B9)&&(state&Bf))+((state&B7)&&(state&Bb));
    case Bb: return ((state&B7)&&(state&Ba))+((state&Bc)&&(state&Bg));
    case Bc: return ((state&Bb)&&(state&Bg))+((state&B8)&&(state&Bd));
    case Bd: return ((state&B8)&&(state&Bc))+((state&Be)&&(state&Bh));
    case Be: return  (state&Bd)&&(state&Bh);
    case Bf: return  (state&B9)&&(state&Ba);
    case Bg: return  (state&Bb)&&(state&Bc);
    case Bh: return  (state&Bd)&&(state&Be);
    }
    return 0;
}
void init(){
    state = ans = 0;
    fill(DP,DP+0x3ffff+1,INT_MIN);
}

int read(){
    int m,from,to,flag = 1;
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&from,&to);
        int sum = move(EdegePoint[from][to]);

        if(sum > 0) ans += flag * sum;
        else flag *= -1;
    }
    return flag;
}

int DFS(){
    if (state == 0x3ffff) return 0;
    if (INT_MIN != DP[state]) return DP[state];

    int ret = INT_MIN;
    for (int i = 0;i < 18;++i){
        if (state & B(i)) continue;
        int sum = move(B(i));
        if (sum > 0) sum += DFS();
        else sum -= DFS();
        ret = max(ret,sum);
        state ^= B(i);
    }
    return DP[state] = ret;
}
int main(){

    int t;
    scanf("%d",&t);
    for (int kase = 1;kase <= t;++kase ){
        init();
        int flag = read();
        ans += flag * DFS();
        printf(ans > 0? "Game %d: A wins.\n" : "Game %d: B wins.\n",kase);
    }
    return 0;
}
