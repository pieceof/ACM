//
// Created by bitwater on 18-3-14.
//

#include<bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
	int x,y;
    while(scanf("%d%d",&x,&y)!=EOF){
        for (int i = x;i <= y; ++i) {
            printf("%5d",i);
            if ((i-x+1) % 5 == 0 )printf("\n");
        }
        if((y-x+1)%5 != 0 )printf("\n");

        printf("Sum = %d\n",(y-x+1)*(x+y)/2 );
    }

	return 0;
}
