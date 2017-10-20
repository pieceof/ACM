#include "../../headers.h"

int Viruses[1100];

const int CHILD_SIZE = 30;
const int TRIE_SIZE = 1000000;
struct node_t {
    node_t* child[CHILD_SIZE];
    node_t* failer;
	int idx;//对应解释的序号
//    bool suffix; /*!< 是否为结束 */
//    int cnt;    /*!< 以该节点结束字符串的数量*/

}Node[TRIE_SIZE];
int toUsed;

inline int tr(char ch ){
    return (ch>='A'&&ch<='Z') ? ch-'A' : 29;
}

//插入单词
void Insert(char const word[] ,int idx ) {
    node_t* loc = Node;
    for(int i = 0; word[i]; ++i) {
//        loc->cnt++;
        int sn = tr(word[i]) ;

        if ( !loc->child[sn] ) {
            memset(Node+toUsed,0,sizeof(node_t));
            loc->child[sn] = Node + toUsed ++;
        }
        loc = loc->child[sn];
    }
    loc->idx = idx;
//    loc->cnt++;
//    loc->suffix = 1;
}

void ACbuild(){
    Node[0].failer = NULL; /*!< root节点的failer为空  */
    queue<node_t*> q;
    for (int i = 0;i < CHILD_SIZE;++i ){
        node_t *p = Node[0].child[i];
        if ( p ){
            p->failer = Node;
            q.push(p);
        }
    }
    while ( !q.empty() ){
        node_t* fa = q.front();q.pop();

        for(int i = 0;i < CHILD_SIZE;++i ){
            node_t* p = fa->child[i];
            if ( p ){
                node_t* v = fa->failer;
                while ( v && !v->child[i] ) v = v->failer;
                if ( !v )   p->failer = Node;
                else        p->failer = v->child[i];
                q.push(p);
            }
        }
    }
}


// trie 查找单词,返回出现的次数
/*
int Find(char const word[]) {
    node_t* loc = Node;
    for(int i = 0; word[i] ; ++i) {
//        if ( loc->suffix ) return 1;
        int sn = word[i] - 'a';
        if ( !loc->child[sn] ) return 0;
        loc = loc->child[sn];
    }
    return loc->cnt;
}
//*/

int Search( char const word[] ){
    int ans = 0;
    node_t* loc = Node;
    for (int i = 0;word[i];++i ){
        int sn = tr(word[i]) ;
        if ( sn == 29 ){
            loc = Node;
            continue;
        }
        while(loc && !loc->child[sn] )
            loc = loc->failer;

        loc = loc ? loc->child[sn] : Node;
        node_t* p = loc;
        while ( p != NULL && p->idx ){
//            if ( p->suffix )
            ans ++  , Viruses[p->idx]++;
//            p->idx = -1;
            p = p->failer;
        }
    }
    return ans;
}

inline void initTrie( ){
    toUsed = 1;
    memset(Node,0,sizeof(node_t));
}

//const int SIZE = 300;
//char par[200];
char tar[2000500];

char str[1100][55];


int main(){

    int n;
    while ( scanf("%d",&n) != EOF ){

        initTrie();
        CLEAR(Viruses);
    //    getchar();
        for (int i = 1;i <= n ;++i ){

            scanf("%s",str[i]);
    //        gets(par);
            Insert( str[i],i );
        }
        getchar();
        ACbuild();
//        scanf("%s",tar);
        gets(tar);

        Search( tar ) ;
        for (int i = 1;i <= n;++i ){
            if ( Viruses[i] ){
                printf("%s: %d\n",str[i],Viruses[i]);
            }
        }
    }
    return 0;
}
