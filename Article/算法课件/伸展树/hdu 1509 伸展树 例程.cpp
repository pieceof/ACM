#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

const int SIZE = 1000000;
#define LEFT 0
#define RIGHT 1
struct key_t{
    int priority;
    int order;
    friend bool operator < (key_t const &l,key_t const &r){
        return l.priority < r.priority ||
            (l.priority == r.priority && l.order < r.order);
    }
    friend bool operator ==(key_t const &l,key_t const &r){
        return
            l.priority == r.priority && l.order == r.order;
    }
    friend bool operator != (key_t const &l,key_t const &r){
        return ! ( l == r );
    }
};

struct value_t{
    char name[100];
    int para;
};

//typedef int key_t;
//typedef int value_t;
struct node_t{//2  1 20 14  1 30 3  2  1 10 99 3 2 2  0
    int sn;
    int parent;
    int child[2];
    key_t key;
    value_t value;

}Node[SIZE];
int toUsed = 0;

///pµÄsn¶ù×ÓÉèÖÃÎªt
inline void _lick( int p,int sn,int t){
    Node[p].child[sn] = t;
    Node[t].parent = p;
    Node[t].sn = sn;
}

inline void _rotate(int t){
    int p = Node[t].parent;
    int sn = Node[t].sn;
    int osn = sn ^ 1;

    _lick( p ,sn , Node[t].child[osn]);
    _lick( Node[p].parent,Node[p].sn,t);
    _lick( t,osn,p);
}

void _splay( int t,int &root){
    while( Node[t].parent ) _rotate(t);
    root = t;

}

void splay(int t, int& root){

    while(Node[t].parent){

        int p = Node[t].parent;

        if ( p != root ) Node[p].sn == Node[t].sn ? _rotate(p) : _rotate(t);

        _rotate(t);
    }
    root = t;
}

void splay(int t,int p,int& root){

    while( Node[t].parent != p ){
        int pp = Node[t].parent;
        if ( Node[pp].parent != p ) Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }
    if ( 0 == p ) root = t;
}
inline void init()
{
    toUsed = 0;
    memset( Node,0,sizeof(node_t) );
}

inline int _newNode(){
    ++toUsed;
    memset(Node+toUsed,0,sizeof(node_t));
    return toUsed;
}
int _advance(int root,int &parent,key_t key){
    if ( root == 0) return parent = 0;

    int t = root;
    parent  = Node[t].parent;
    while(t && key != Node[t].key){
        parent = t;
        t = key < Node[t].key ?
        Node[t].child[LEFT] :
        Node[t].child[RIGHT];
    }
    return t;
}
void Insert(int &root,key_t key,value_t value ){
    int t = _newNode();
    Node[t].key = key;
    Node[t].value = value;

    int p ;
    _advance(root,p,key);

    if (0 == root){
        root = t;
        return ;
    }

    int sn =  key < Node[p].key ? LEFT:RIGHT;
    _lick(p,sn,t);
    splay(t,0,root);
}
int getMax(int &root){
    if ( 0 == root) return 0;
    int t = root;
    while(Node[t].child[RIGHT])
        t = Node[t].child[RIGHT];
    splay(t,0,root);
    return t;
}
int getMin(int &root){
    if ( 0 == root) return 0;
    int t = root;
    while(Node[t].child[LEFT])
        t = Node[t].child[LEFT];
    splay(t,0,root);
    return t;
}

int main()
{
    init();
    int root = 0;
    char cmd[100];
    int order = 0;
    while(scanf("%s",cmd) != EOF){
        if ('G' == *cmd){
            if ( 0 == root ){

                printf("EMPTY QUEUE!\n");
                continue;
            }else {
                int t = getMin(root);
                printf("%s %d\n",Node[t].value.name,Node[t].value.para);

                if (root){
                    root = Node[root].child[RIGHT];
                    Node[root].parent = 0;
                }
            }

        }else {
            key_t key;
            value_t value;
            scanf("%s%d%d",value.name,&value.para,&key.priority);
            key.order = order ++;
            Insert(root,key,value);
        }
    }

    return 0;
}
