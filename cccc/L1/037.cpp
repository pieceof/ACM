//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    double a,b;
    while(cin>>a>>b){
        cout << a  << "/";
        if ( b < 0 )cout  << "(" << b<< ")";
        else cout << b ;
        cout << "=";
        if ( b == 0 ) cout << "Error"<<endl;
        else printf("%.2f\n",a/b);
    }
    return 0;
}
