//
// Created by bitwater on 18-3-19.
//

#include<bits/stdc++.h>

using namespace std;

map<string, int> value;
map<string, string> next_;
map<string, string> front;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    string start, end, a, c;
    int n, x;
    cin >> start >> n;
    while (n--) {
        cin >> a >> x >> c;
        value[a] = x;
        next_[a] = c;
        front[c] = a;
        if (c == "-1") end = a;
    }
    while (1) {
        cout << end << " " << value[end] << " " << start << endl;
        cout << start << " " << value[start] << " ";
        if (next_[start] == end) {
            cout << -1 << endl;
            break;
        } else {
            cout << front[end] << endl;
        }
        start = next_[start];
        end = front[end];
        if (start == end) {
            cout << end << " " << value[end] << " " << -1 << endl;
            break;
        }
    }

    return 0;
}