---
title: 计算几何专题模板 - other&&公式
tags: 计算几何,模板
grammar_cjkRuby: true
---

## 
```cpp
/**< 两点计算 直线一般式方程 */
void LineEquation(point_t const&a,point_t const&b ,int_t&A,int_t&B,int_t&C ){
    assert( !(a==b) ); // assert( !(a.x==b.x));
    A = b.y - a.y;
    B = a.x - b.x;
    C = b.x*a.y - a.x*b.y;
}

/**< 三角形外接圆  */
circle_t CircumscribedCircle(point_t p1, point_t p2, point_t p3) {
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx*Cy - By*Cx);
    double cx = (Cy*(Bx*Bx + By*By) - By*(Cx*Cx + Cy*Cy)) / D + p1.x;
    double cy = (Bx*(Cx*Cx + Cy*Cy) - Cx*(Bx*Bx + By*By)) / D + p1.y;
    point_t _p = point_t(cx, cy);
    return circle_t(_p, Point2Point(p1,_p));
}    //三角形外接圆

/** 线段上的整数点
 *  两个端点坐标差的绝对值的 gcd + 1
 */
/**  pick 公式
 *  面积 = 边界点数 ÷ 2 ＋ 内部点数 － 1
 */
/** 正方形ABCD,已知对顶点A(X1,Y1),C(X3,Y3) (利用对角线可得另外两点)
 *  x2:=(x1+x3+y3-y1)/2; y2:=(y1+y3+x1-x3)/2;
 *  x4:=(x1+x3-y3+y1)/2; y4:=(y1+y3-x1+x3)/2;
 */
 ```