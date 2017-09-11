---
title: 字符串专题模板 - manacher回文
tags: 字符串,模板
grammar_cjkRuby: true
---

```cpp
/*
 *对于n长度的字符串，存储是从1~n+n+1， 实际长度是n+n+2；
 *注意size范围
 */
///*
const int _SIZE =  SIZE+SIZE;
int p[_SIZE];
template<class DATA >
void manacher(DATA *s ,int len) //manacher 函数
{
    for(int i = len;i >= 0;--i) //将s扩大，中间加#，开头加*
        s[i+i+2] = s[i] , s[i+i+1] = '#';
//        s[i+i+2] = s[i] , s[i+i+1] = -1;
    s[0] = '*';
//    s[0] = -2;
    int id , mx = 0;  //mx代表以id为中心时，到达最远的位置
    for(int i = 1;i <= len+len+1; ++i ){
        if( mx > i ) p[i] = min(p[2*id-i],mx-i ); //如果到达最远位置大于当前匹配的地方，则p[i]取min（id的对称点的p，到达最远距离-i）
        else p[i] = 1; //如果i在mx右方，则p[i]=-1;
        // 如果需要回文串单调不减
//        while( s[i-p[i]] == s[i+p[i]] &&  s[i-p[i]] <= s[i-p[i]+2] ) ++p[i];
        while( s[i-p[i]] == s[i+p[i]] ) ++p[i];   //判断i回文长度
        if( i + p[i] > mx ) //看是否要更新最远距离，如果要，将此点作为中心。
            id = i , mx = p[i] + i;
    }
}
//*/
```