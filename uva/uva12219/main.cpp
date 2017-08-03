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
struct _t{
    int rcode, lch, rch;        //code of root. treeid of left and right sub-tree.
    _t(){};
    _t(int a, int b, int c):rcode(a), lch(b), rch(c) { }
    bool operator < (const _t& rhs) const {
        if(rcode == rhs.rcode){
            if(lch == rhs.lch) return rch < rhs.rch;
            return lch < rhs.lch;
        }
        return rcode < rhs.rcode;
    }
};
const int SIZE = 50000+5;
bool vis[SIZE];

_t tree_cache[SIZE];
map< _t , int > tree_ID;
int tree_cnt = 0;

int Get_tree_id( _t const&a  ){
    if ( tree_ID.count(a) != 0 ) return tree_ID[a];
    tree_cache[++tree_cnt] = a ;
    return tree_ID[a] = tree_cnt;
}

char str[5*(SIZE+10000)] ,*p ;

int oper_cnt = 0;
map<int,int> oper;


int cnt = 0;

int Expretree(  ){
    int lch = -1, rch = -1;
    int name = 0;
    while(isalpha(*p)) {
        name = name*27 + (*p-'a'+1);
        p ++;
    }
    if(*p == '(') {
        p++;
        lch = Expretree();
        p ++;
        rch = Expretree();
        p ++;
    }
    _t tmp = _t(name, lch, rch);
    return Get_tree_id(tmp);
}


int ans[SIZE];
void decode(int a) {
    vector<char> result;
    while(a) { result.push_back(a%27+'a'-1); a/=27; }       //%27+1
    for(int i = result.size() - 1; i >= 0; i --) {
        cout<<result[i];
    }
}

void print_ans(int id) {
    if(ans[id] != -1) cout<<ans[id];
    else {
        ans[id] = ++cnt;
        decode(tree_cache[id].rcode);
        if(tree_cache[id].lch != -1) {
            cout<<"(";
            print_ans(tree_cache[id].lch);
            cout<<",";
            print_ans(tree_cache[id].rch);
            cout<<")";
        }
    }
}


int main()
{
//    ios::sync_with_stdio(false);
    //freopen("B.in", "r", stdin);
    //freopen("cout.txt", "w", stdout);
    int t;
    scanf("%d",&t);
    while ( t-- ){
        scanf("%s",str);
        p = str;
        cnt = tree_cnt = 0;
        tree_ID.clear();
        FLAG(ans);
        int h = Expretree();

//        deBug(h);
//        deBug( tree_cnt );
        print_ans(h);
        puts("");
    }


    return 0;
}
