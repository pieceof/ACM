//
// Created by bitwater on 18-4-7.
//

#include<iostream>

using namespace std;

int main(){
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0)break;
        int t1 = a * 30 + b * 40;
        int t2 = a * 35 + b * 30;
        int t3 = a * 40 + b * 20;
        cout << min(t1, min(t2, t3)) << endl;
    }
    return 0;
}