#include <bits/stdc++.h>
#define CLEAR(a) memset((a),0,sizeof(a))
#define FLAG(a) memset((a) , -1 , sizeof(a))
#define  varName(x) #x
#define  deBug(exp) cout<< " == > " << #exp<<" : "<< (exp) << endl

typedef long long llt;
using namespace std;

/*
    ios.sync_with_stdio(false);  /// 那么cin, 就不能跟C的 scanf，sscanf, getchar, fgets之类的一起使用了。
    freopen("cin.txt", "r", stdin);
    freopen("cout.txt", "w", stdout);
*/


struct hash_t{

    typedef string key_t;
    typedef int value_t;

    enum{ MOD = 0x1FFFFF};

    key_t keys[MOD+1];
    value_t values[MOD+1];

    int next[MOD+1];
    int head[MOD+1];

    int toUsed;

    hash_t():toUsed(0){FLAG(head);};

    void clear(){toUsed=0;FLAG(head);};

    void insert(key_t const&key,value_t const&value ){

        int k = Hash(key)&MOD;
        keys[toUsed] = key;
        values[toUsed] = value;

        next[toUsed] = head[k];
        head[k] = toUsed++;

    }

    value_t find( key_t const&key ){
        int k = Hash(key)&MOD;
        for ( int i = head[k] ; i !=-1 ;i = next[i] )
            if( keys[i] == key )
                return values[i];
        return -1;
    }


};

int main()
{

    return 0;
}
