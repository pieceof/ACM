//
// Created by bitwater on 18-4-11.
//

#include<bits/stdc++.h>
using namespace std;

char str[1000000];
int ans = -1;
/*!< 假设右边正确,检查左边出错, len|2 , 从里往外对比 */
int checkl(int idx, int len) {
    int ret = 0, i, j;
    for (i = idx - 1, j = idx + 1; i >= 0 && j < len; i--, j++)if (str[i] != str[j])
        ret++, ans = i, j--;
    if (i == 0 && ret == 0)ret++, ans = 0;
    return ret;
}

/*!< 假设左边正确,检查右边出错, len|2 , 从外往里对比 */
int checkr(int idx, int len) {
    int ret = 0, i, j;
    for (i = 0, j = len - 1; i < idx && j > idx; i++, j--)if (str[i] != str[j])
        ret++, ans = j, i--;
    if (i == idx && ret == 0)ret++, ans = idx + 1;
    return ret;
}

/*!< 假设右边正确,检查左边出错, (len+1)|2 , 从里往外对比 */
int check2l(int idx, int len) {
    int ret = 0, i, j;
    for (i = idx, j = idx + 1; i >= 0 && j < len; i--, j++)if (str[i] != str[j])
        ret++, ans = i, j--;
    if (i == 0 && ret == 0)ret++, ans = 0;
    return ret;
}
/*!< 假设左边正确,检查右边出错, (len+1)|2 , 从外往里对比 */
int check2r(int idx, int len) {
    int ret = 0, i, j;
    for (i = 0, j = len - 1; i < idx && j >= idx; i++, j--)if (str[i] != str[j])
        ret++, ans = j, i--;
    return ret;
}

int main() {
    while (scanf("%s", str) != EOF) {
        int len = strlen(str);
        if (len % 2 == 0) {
            /*!< 假设左边错误 */
            if (1 == checkl(len / 2, len))printf("%d\n", ans + 1);

            /*!< 假设右边错误 */
            else if (1 == checkr(len / 2 - 1, len))printf("%d\n", ans + 1);

        } else {
            /*!< 假设左边错误 */
            if (1 == check2l(len / 2, len))printf("%d\n", ans + 1);

            /*!< 中间不可能错误, 如果中间错误,删除是回文串,那中间不删也是回文串 */

            /*!< 假设右边错误 */
            else if (1 == check2r(len / 2, len))printf("%d\n", ans + 1);
        }
    }
    return 0;
}

/*
 *
 *
12345321   4

abaa       2
aaba       1

1233421    5
123455321  4

12345321    4
1234546654321  6
123251      5

1233212     7

23322      4
22332       1

123443321  6

1233212    7
2123321     1
*/
