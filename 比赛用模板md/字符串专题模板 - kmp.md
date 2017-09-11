---
title: 字符串专题模板 - kmp
tags: 字符串,模板
grammar_cjkRuby: true
---


## kmp
```cpp
template<class DATA>
void getKMPNext(DATA const P[],int *Next,int n ) {
    Next[0] = -1;
    //int i = 0, k = -1,n++ ; // kmp循环匹配多算一位
    int i = 0, k = -1;
    while( i < n ) {
        while( k >= 0 && P[i] != P[k] )
            k = Next[k];
        ++i,++k;
        if ( i == n ) return;
        Next[i] = ( P[i] == P[k] ) ? Next[k] : k;
    }
}

/**< 循环kmp匹配的时候要多算一位next  */
template<class DATA >
int KMP(DATA const T[],int tlen,DATA const P[],int plen,int Next[],int breakpoint=0) {
    int ans = 0;
    if ( tlen < plen ) return 0;
    int tp = breakpoint, pp = 0;
    while( tp < tlen ) {
        if ( -1 == pp || T[tp] == P[pp] )++tp,++pp;
        else pp = Next[pp];
        if ( plen == pp  ) {
            ans++;
            pp = 0;   // 不重叠
//            pp = Next[pp]; //可以重叠
            /**< 如果不循环匹配 直接return  */
//            return tp-plen;
        }
    }
    return ans;
    return -1;
}

```
