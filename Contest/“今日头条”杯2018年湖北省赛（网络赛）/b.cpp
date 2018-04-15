//
// Created by bitwater on 18-4-15.
//

#include<bits/stdc++.h>

using namespace std;
double const PI = acos(-1.0);

inline double Heron(double a, double b, double c) {
    double _p = (a + b + c) / 2.0;
    return sqrt(_p * (_p - a) * (_p - b) * (_p - c));
}

double area(double r) {
    return 4 * PI * r * r;
}

double guan(double r, double h) {
    return 2 * PI * r * h;
}

int main() {

    double r1, r2, l;
    while (scanf("%lf%lf%lf", &r1, &r2, &l) != EOF) {
        if (r1 + r2 <= l) {
            printf("%.12f\n", area(r1) + area(r2));
            continue;
        }
        if (r1 < r2)swap(r1, r2);
        if (r1 - r2 >= l) {
            printf("%.12f\n", area(r1));
            continue;
        }
        double mid = sqrt(r1 * r1 - r2 * r2);
        double h = Heron(r1, r2, l) * 2 / l;
        double H1 = r1 - sqrt(r1 * r1 - h * h);
        double j1 = guan(r1, H1);
        double H2 = r2 - sqrt(r2 * r2 - h * h);
        double j2 = guan(r2, H2);
        if (l <= mid) {
            printf("%.12f\n", area(r1) - j1 + j2);
        } else {
            printf("%.12f\n", area(r1) + area(r2) - j1 - j2);
        }

    }

    return 0;
}