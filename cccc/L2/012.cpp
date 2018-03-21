//
// Created by bitwater on 18-3-21.
//

#include <bits/stdc++.h>

using namespace std;

int main(int argc, char *argv[]) {
    vector<int> heap;
    make_heap(heap.begin(), heap.end(), greater<int>());
    int n, m, x, a, b;
    scanf("%d%d", &n, &m);
    while (n--) {
        scanf("%d", &x);
        heap.push_back(x);
        push_heap(heap.begin(), heap.end(), greater<int>());
    }
    char str[1000];
    getchar();
    while (m--) {
        gets(str);
        int len = strlen(str);
        if (str[len - 1] == 't') {
            sscanf(str, "%d is the root", &x);
            if (heap[0] == x)printf("T\n");
            else printf("F\n");
            continue;
        }
        if (str[len - 1] == 's') {
            sscanf(str, "%d and %d are siblings", &a, &b);
            if (a == heap[0] || b == heap[0]) {
                printf("F\n");
            } else {
                int adx, bdx;
                for (int i = 0; i < heap.size(); ++i) {
                    if (heap[i] == a)adx = i;
                    if (heap[i] == b)bdx = i;
                }
                adx++, bdx++;
                if (adx / 2 == bdx / 2) printf("T\n");
                else printf("F\n");
            }
            continue;
        }

        int sdx = 0;
        while (str[sdx] != 's') sdx++;
        if (str[sdx + 2] == 'a') {
            sscanf(str, "%d is a child of %d", &a, &b);
            if (a == heap[0]) {
                printf("F\n");
            } else {
                int adx, bdx;
                for (int i = 0; i < heap.size(); ++i) {
                    if (heap[i] == a)adx = i;
                    if (heap[i] == b)bdx = i;
                }
                adx++, bdx++;
                if (adx / 2 == bdx) printf("T\n");
                else printf("F\n");
            }
            continue;
        }
        if (str[sdx + 2] == 't') {
            sscanf(str, "%d is the parent of %d", &a, &b);
            if (b == heap[0]) {
                printf("F\n");
            } else {
                int adx, bdx;
                for (int i = 0; i < heap.size(); ++i) {
                    if (heap[i] == a)adx = i;
                    if (heap[i] == b)bdx = i;
                }
                adx++, bdx++;
                if (bdx / 2 == adx) printf("T\n");
                else printf("F\n");
            }
            continue;
        }
    }

    return 0;
}