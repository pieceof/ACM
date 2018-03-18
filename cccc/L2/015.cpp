//
// Created by bitwater on 18-3-18.
//

#include<bits/stdc++.h>

using namespace std;

double  allscore[20000];
int main(int argc, char *argv[]) {
    int n, k, m;
    while (scanf("%d%d%d", &n, &k, &m) != EOF) {


        double score[100];

        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < k; ++j) {
                scanf("%lf", score + j);
                sum += score[j];
            }
            sort(score, score + k);
            sum -= score[0] + score[k - 1];
            allscore[i] = (sum / (k - 2));
        }
        sort(allscore,allscore+n);
        for(int i = n-m;i < n-1;++i)
            printf("%.3f ",allscore[i]);
        printf("%.3f\n",allscore[n-1]);
    }
    return 0;
}