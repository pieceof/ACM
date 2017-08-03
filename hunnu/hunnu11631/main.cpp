#include <bits/stdc++.h>
using namespace std;
const int N=11000;
int a[N];
int main()
{
    //freopen("input.txt","r",stdin);
    int n;
    string s;
    while(cin>>n)
    {
        cin>>s;
        int j=0;
        for(int i=0; i<n; i++)    //拆成单个正面情况
        {
            if(s[i]=='H')
                a[j++]=i+1;
        }
        for(int i=1; i<j; i++)//异或，计算结果
            a[0]^=a[i];
        if(a[0])//不为0
            cout<<"Alice"<<endl;
        else
            cout<<"Bob"<<endl;
    }
    return 0;
}
