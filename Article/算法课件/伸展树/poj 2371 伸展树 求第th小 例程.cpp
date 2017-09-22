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

typedef int value_t;
struct node_t{//2  1 20 14  1 30 3  2  1 10 99 3 2 2  0
    int sn;
    int parent;
    int child[2];
    key_t key;
    value_t value;
    int size;
}Node[SIZE];
int toUsed = 0;

inline void _pushUp(int t){
     Node[t].size = 1;
     int son = Node[t].child[LEFT];
     if(son) Node[t].size += Node[son].size;
     son = Node[t].child[RIGHT];
     if(son) Node[t].size += Node[son].size;
}

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

    _pushUp(p);
    //_pushUp(t); //没用到，节约时间。
}


void _splay(int t, int& root){

    while(Node[t].parent){

        int p = Node[t].parent;
        if ( p != root ) Node[p].sn == Node[t].sn ? _rotate(p) : _rotate(t);
        _rotate(t);
    }
    _pushUp(t);
    root = t;
}

void _splay(int t,int p,int& root){

    while( Node[t].parent != p ){
        int pp = Node[t].parent;
        if ( Node[pp].parent != p ) Node[pp].sn == Node[t].sn ? _rotate(pp) : _rotate(t);
        _rotate(t);
    }
    _pushUp(t);
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
    Node[t].size = 1;
    int p ;
    _advance(root,p,key);

    if (0 == root){
        root = t;
        return ;
    }

    int sn =  key < Node[p].key ? LEFT:RIGHT;
    _lick(p,sn,t);
    _splay(t,0,root);
}
int getMax(int &root){
    if ( 0 == root) return 0;
    int t = root;
    while(Node[t].child[RIGHT])
        t = Node[t].child[RIGHT];

    _splay(t,0,root);
    return t;
}
int getMin(int &root){
    if ( 0 == root) return 0;
    int t = root;
    while(Node[t].child[LEFT])
        t = Node[t].child[LEFT];
    _splay(t,0,root);
    return t;
}
///1 base index
int select(int root,int kth){

    int son = Node[root].child[0];
    int sz = son ? Node[son].size + 1: 1;

    if ( kth < sz ) return select( son,kth );
    if ( kth > sz ) return select( Node[root].child[1],kth - sz);
    return root;

}
//
//void dispTree(int root);
//void dispitree(int root);
//void disNode(int node);
int main()
{
    init();
    int root = 0;
    int n,x;
    int order = 1;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&x);
        key_t k;
        k.priority  = x;
        k.order = order++;
        Insert(root,k,0);
        //dispTree(root);
    }
    char a[100];
    scanf("%s",a);
    scanf("%d",&n);
    while(n--){
        scanf("%d",&x);
        //dispitree(select( root , x));


        printf("%d\n",Node[ select( root , x) ].key.priority);

    }

    return 0;
}

//void disNode(int node){
//    printf("   Node %d:\n",node);
//    printf("         Parent: %d,LEFT:%d, RIGHT :%d\n",Node[node].parent,Node[node].child[0],Node[node].child[1]);
//    printf("         Key :%d , Value:%d ,Size:%d\n",Node[node].key,Node[node].value,Node[node].size);
//}
//
//void dispitree(int root){
//    disNode(root);
//    if (Node[root].child[0]) dispitree(Node[root].child[0]);
//    if (Node[root].child[1]) dispitree(Node[root].child[1]);
//
//}
//void dispTree(int root){
//    if (root == 0){
//        printf("Tree is NONE\n");
//        return;
//    }
//    printf("tree %d is :\n",root);
//    dispitree(root);
//}
