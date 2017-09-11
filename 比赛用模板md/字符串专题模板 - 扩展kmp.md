---
title: 字符串专题模板 - 扩展kmp
tags: 字符串,模板
grammar_cjkRuby: true
---

## 扩展kmp
```cpp
/*
*  扩展KMP算法
*/
//next[i]:x[i...m-1]与x[0...m-1]的最长公共前缀
//extend[i]:y[i...n-1]与x[0...m-1]的最长公共前缀
template<class DATA >
void getExtendKMPNext(DATA const T[],int Next[],int tlen) {
    Next[0] = tlen ;
    int j = 0,k = 1;;
    while ( j+1 < tlen && T[j] == T[j+1] ) j++;
    Next[1] = j;
    for(int i = 2; i < tlen; i++ ){
        int p = Next[k] + k-1;
        int L = Next[i-k];
        if( i+L < p+1 ) Next[i] = L;
        else{
            j = max( 0 , p-i+1 );
            while( i+j < tlen && T[i+j] == T[j] ) j++;
            Next[i] = j;
            k = i;
        }
    }
}
template<class DATA >
void getExtendKMP(DATA const T[],int tlen,DATA const S[],int slen,int Next[], int extend[]) {
    getExtendKMPNext(T,Next,tlen);
    int j = 0,k = 0;
    while( j < slen && j<tlen && T[j] == S[j] ) j++;
    extend[0] = j;
    for(int i = 1; i < slen; i++ ) {
        int p = extend[k] + k-1;
        int L = Next[i-k];
        if( i+L < p+1 ) extend[i] = L;
        else {
            j = max( 0, p-i+1);
            while( i+j < slen && j < tlen && S[i+j] == T[j]) j++;
            extend[i] = j;
            k = i;
        }
    }
}
```