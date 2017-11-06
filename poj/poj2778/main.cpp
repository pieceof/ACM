#include "../../headers.h"


const int CHILD_SIZE = 4;
const int TRIE_SIZE = 200;
const int ROOT = 0;
struct node_t {
    int child[CHILD_SIZE];
    int failer;
    bool suffix; /*!< 是否为结束 */
//    int cnt;    /*!< 以该节点结束字符串的数量*/

}Node[TRIE_SIZE];
int toUsed;

inline int tr(char ch ){
    if ( ch == 'A' ) return 0;
    if ( ch == 'C' ) return 1;
    if ( ch == 'G' ) return 2;
    if ( ch == 'T' ) return 3;
//    while (1);
}
inline int _NewNode(){
    memset(Node+toUsed,-1,sizeof(node_t));
    Node[toUsed].suffix = 0;
    Node[toUsed].failer = 0;
    return toUsed++;
}

inline void initTrie( ){
    toUsed = 0;
    _NewNode();
}

//插入单词
void Insert(char const word[] ) {
    int loc = 0;
    for(int i = 0; word[i]; ++i) {
//        loc->cnt++;
        int sn = tr(word[i]) ;

        if ( Node[loc].child[sn] == -1 ) {
            Node[loc].child[sn] = _NewNode();
        }
        loc = Node[loc].child[sn];
    }
    Node[loc].suffix = 1;
}

void ACbuild(){
//    Node[ROOT].failer = 0; /*!< root节点的failer为空  */
    queue<int> q;
    for (int i = 0;i < CHILD_SIZE;++i ){
        int p = Node[ROOT].child[i];
        if ( p != -1 ){
            Node[ROOT].failer = ROOT;
            q.push(p);
        }else {
            Node[ROOT].child[i] = ROOT;    // 直接链在root
        }
    }
    while ( !q.empty() ){
        int fa = q.front();q.pop();
        Node[fa].suffix |= Node[Node[fa].failer].suffix;
        for(int i = 0;i < CHILD_SIZE;++i ){
            int p = Node[fa].child[i];
            if ( p != -1){
                Node[p].failer = Node[ Node[fa].failer].child[i];
                q.push(p);
            }else {
                Node[fa].child[i] = Node[ Node[fa].failer ].child[i];
            }
        }
    }
}




struct Cube{
//private:
    enum {Cube_SIZE=200,mod=100000};
//public:
    int spec;
    llt mat[Cube_SIZE][Cube_SIZE];
    Cube(int s=0):spec(s){ init(); };
    void init(int sp = -1 ){
        CLEAR(mat);
        if ( sp != -1 ) spec = sp;
        for (int i = 0;i < spec;++i ) mat[i][i] = 1;
    }
    ///矩阵乘法
    Cube operator * ( Cube const&B ){
        Cube _tmpCube(spec);
        for (int i = 0;i < spec;++i)for (int j = 0;j < spec;++j){
            _tmpCube.mat[i][j] = 0;
            for (int k = 0;k < spec;++k){
                _tmpCube.mat[i][j] += mat[i][k]*B.mat[k][j]%mod;
//                _tmpCube.mat[i][j] %= mod;
            }
            _tmpCube.mat[i][j] %= mod;
        }
        return _tmpCube;
    }
    ///矩阵快速幂
    Cube operator ^ (llt n){
        Cube _tmpCube(spec);
        Cube A = *this;
        while(n){
            if(n & 1)
                _tmpCube = _tmpCube * A;
            A = A * A;
            n >>= 1;
        }
        return _tmpCube;
    }
    void Disp(){
        cout << endl;
        for (int i = 0;i < spec;++i ){
            for (int j = 0;j < spec;++j )
                cout << std::right << setw(3) << mat[i][j];
            cout << endl;
        }cout << endl;
    }
};


//const int SIZE = 300;


char par[100];
int main(){


    Cube arr;
    int n ;
    llt k;
    while ( scanf("%d%lld",&n,&k) !=EOF  ){
        initTrie();
        for (int i = 0;i < n;++i ){
            scanf("%s",par);
            Insert( par );
        }
        ACbuild();
//        deBug( toUsed );

        arr.spec = toUsed ;
        for( int i = 0;i < toUsed;++i ){
            if ( Node[i].suffix ) continue;
            for ( int j = 0;j < 4;++j ){
                int v = Node[i].child[j];
                if ( Node[v].suffix == 0 ) arr.mat[i][v]++;
            }
        }
//        arr.Disp();
        arr = arr ^ k;
//        arr.Disp();
        llt ans = 0;
        for ( int i = 0;i < toUsed;++i ){
            ans += arr.mat[0][i];
        }
        printf("%lld\n",ans%Cube::mod);
    }
    return 0;
}
