//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
	int a[3];
    while(scanf("%d%d%d",a+0,a+1,a+2)!=EOF){
        sort(a,a+3);
        printf("%d->%d->%d\n",a[0],a[1],a[2]);
    }
	return 0;
}