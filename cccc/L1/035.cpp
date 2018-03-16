//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    int cnt = 0;
    string name1 = "", name2 = "", name;
    while (cin >> name) {
        if (name[0] == '.')break;
        cnt++;
        if (cnt == 2) name1 = name;
        if (cnt == 14) name2 = name;
    }
    if (name1 != "" && name2 != "")
        cout << name1 << " and " << name2 << " are inviting you to dinner..." << endl;
    else if (name1 != "") {
        cout << name1 << " is the only one for you..." << endl;
    } else {
        cout << "Momo... No one is for you ..." << endl;
    }


    return 0;
}