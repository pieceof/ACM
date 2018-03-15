//
// Created by bitwater on 18-3-15.
//
#include<bits/stdc++.h>

using namespace std;
char say[11][5]{
        "ling",
        "yi",
        "er",
        "san",
        "si",
        "wu",
        "liu",
        "qi",
        "ba",
        "jiu", "fu"
};

int main(int argc, char *argv[]) {

    char nub[100];
    while (scanf("%s", nub) != EOF) {
        int len = strlen(nub);
        for (int i = 0; i < len - 1; ++i) {
            if (nub[i] == '-')printf("fu ");
            else
                printf("%s ", say[nub[i] - '0']);
        }
        if (nub[len - 1] == '-')printf("fu\n");
        else
            printf("%s\n", say[nub[len - 1] - '0']);
        
    }

    return 0;
}
