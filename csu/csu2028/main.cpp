//
// Created by bitwater on 18-4-8.
//

#include <iostream>
#include <cstdio>

using namespace std;

int card[20];

bool input() {
    for (int i = 1; i <= 16; i++)scanf("%1d", &card[i]);
    for (int i = 1; i <= 16; i++)if (card[i] != 0) return true;
    return false;
}

int main() {
    while (input()) {
        int sum = 0;
        for (int i = 1; i <= 16; i += 2) {
            card[i] *= 2;
            if (card[i] > 9) card[i] -= 9;
            sum += card[i];
        }
        for (int i = 2; i <= 16; i += 2)sum += card[i];
        if (sum % 10 == 0)printf("Yes\n");
        else printf("No\n");
    }
}