//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

vector<string> persion;
bool isUsed[100];
int sex[100];

int main(int argc, char *argv[]) {

    int n;
    while (scanf("%d", &n) != EOF) {
        string p;
        int x;
        for (int i = 0; i < n; ++i) {
            cin >> sex[i] >> p;
            persion.push_back(p);
        };
        memset(isUsed, 0, sizeof(isUsed));
        for (int i = 0; i < n; ++i) {
            if (isUsed[i]) continue;
            int s = sex[i];
            for (int j = n - 1; j >= 0; --j) {
                if (isUsed[j])continue;
                if (sex[j] ^ sex[i] == 1) {
                    cout << persion[i] << " " << persion[j] << endl;
                    isUsed[i] = 1;
                    isUsed[j] = 1;
                    break;
                }
            }
        }

    }

    return 0;
}