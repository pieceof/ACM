---
title: 字符串专题模板 - Next数组
tags: 字符串,模板
grammar_cjkRuby: true
---
## Next数组
```cpp
template<class DATA>
void getNext( DATA const P[],int *Next,int n ) {
    Next[0] = 0;
    for (int i = 1; i < n ; ++i ) {
        int k = Next[i-1];
        while ( k > 0 && P[i] != P[k] )
            k = Next[k-1];
        Next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
    }
}
```