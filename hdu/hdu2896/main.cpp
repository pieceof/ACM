#include "../../headers.h"


const int CHILD_SIZE = 100;
const int TRIE_SIZE = 100000;
struct node_t {
    node_t* child[CHILD_SIZE];
    node_t* failer;
	int idx;//对应解释的序号
//    bool suffix; /*!< 是否为结束 */
//    int cnt;    /*!< 以该节点结束字符串的数量*/

}Node[TRIE_SIZE];
int toUsed;

//插入单词
void Insert(char const word[] ,int idx) {
    node_t* loc = Node;
    for(int i = 0; word[i]; ++i) {
//        loc->cnt++;
        int sn = word[i] - ' ' ;

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
queue<node_t*> q;
void ACbuild(){
    while ( !q.empty( ) ) q.pop();
    Node[0].failer = NULL; /*!< root节点的failer为空  */

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

int Viruses[10];
int VirCnt ;

int Search( char const word[] ){
    int ans = 0;
    node_t* loc = Node;
    for (int i = 0;word[i];++i ){
        int sn = word[i] - ' ';
        while(loc && !loc->child[sn] )
            loc = loc->failer;
        loc = loc ? loc->child[sn] : Node;
        node_t* p = loc;
        while ( p != NULL ){
            if ( p->idx )
            Viruses[VirCnt++] = p->idx;
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
char par[300];
char tar[20050];


int main(){
//    CLEAR(Node);
int n;
while ( scanf("%d",&n) != EOF ){

    initTrie();

    getchar();
    for (int i = 1;i <= n ;++i ){
//        scanf("%s",par);
        gets(par);
        Insert( par, i );
    }
    ACbuild();
    int m;scanf("%d",&m);
    getchar();
    int sum = 0;
    for (int i = 1;i <= m;++i ){
//        scanf("%s",tar);
        gets(tar);
        VirCnt = 0;
        Search( tar );

        if ( VirCnt ){
            sort(Viruses,Viruses+VirCnt);
            printf("web %d:",i);
            for ( int j = 0;j < VirCnt;++j )
                printf(" %d",Viruses[j]);
            printf("\n");
            sum ++;
        }
    }
    printf("total: %d\n",sum );
}
    return 0;
}
