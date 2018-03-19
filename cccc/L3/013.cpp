//
// Created by bitwater on 18-3-19.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    double w, p;
    scanf("%lf%lf", &w, &p);
    w = w / 100;
    double v2 = 2 * 1000 / w;
    double v = sqrt(v2);
    double s = 0;
    double g = 9.8;
    while (v > 0.000001) {
        double t = v * sqrt(2) / g;
        s += v / sqrt(2) * t;
        v = sqrt(v * v * (100 - p) / 100);
    }
    printf("%0.3f\n", s);

    return 0;
}