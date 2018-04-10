//
// Created by bitwater on 18-4-10.
//

//
// Created by bitwater on 18-3-14.
//
#include<bits/stdc++.h>

using namespace std;
set<string> st;
string str;

int main(int argc, char *argv[]) {
    int n;
    while (cin >> n) {
        int cnt = 0;
        while (n--) {
            cin >> str;
            if (st.count(str))cnt++;
            reverse(str.begin(), str.end());
            if (st.count(str))cnt++;
            st.insert(str);
        }
        cout << cnt << endl;
    }

    return 0;
}