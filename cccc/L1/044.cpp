//
// Created by bitwater on 18-3-16.
//

#include<bits/stdc++.h>
using  namespace std;

map<string , string > mp;

int main(int argc, char *argv[]) {
    int k;
    mp["JianDao"] = "ChuiZi";
    mp["Bu"] = "JianDao";
    mp["ChuiZi"] = "Bu";
    string str;
    scanf("%d",&k);
    int cnt = 0;
    while (1){
        cin>>str;
        if( str == "End")break;
        if( cnt == k ){
            cout << str << endl;
            cnt = 0;
        }else {
            cout << mp[str] << endl;
            cnt++;
        }

    }

	return 0;
}