//
// Created by bitwater on 18-3-15.
//

#include<bits/stdc++.h>
//#include"../../headers.h"

using namespace std;
int main(int argc, char *argv[]) {
	int x,y;
    while(scanf("%d:%d",&x,&y) !=EOF){
//        deBugp(x,y);
        if ( (x >= 0 && x <= 11)||(x==12&&y==0)){
            printf("Only %02d:%02d.  Too early to Dang.\n",x,y);
            continue;
        }
        if ( y > 0 ) x++;
        x -= 12;
        while(x--)printf("Dang");

        printf("\n");
    }
	return 0;
}