//
// Created by bitwater on 18-3-14.
//
#include "../../headers.h"

const int SIZE = 1050;
int bucket[SIZE];
int A[SIZE];

int N, M, L;

int check(int x) {

    for (int i = 0; i < N; ++i) {
        int j = i + 1;
        int m = M;
        while (j <= i + N) {
            if (bucket[j % N] < x)m--, j += L;
            else j++;
            if (m < 0)break;
        }
        if (m >= 0) return 1;
    }
    return 0;
}

int main() {

    while (scanf("%d%d%d", &N, &M, &L) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%d", bucket + i);
            A[i] = bucket[i];
        }
        sort(A, A + N);
        int l = 0, r = N;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (check(A[mid]))l = mid + 1;
            else r = mid;
        }
        printf("%d\n", A[l - 1]);
    }

    return 0;
}