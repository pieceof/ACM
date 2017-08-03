#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef int weight_t;

const int SIZE_E = 30050;
const int SIZE_V = 25050;
int Start,End;
struct edge_t{
    int node;
    weight_t c;
    edge_t *next;
    edge_t *redge;
}Edge[SIZE_E];

int Ecnt = 0;

edge_t *Ver[SIZE_V] ;

void init(){
    Ecnt = 0;
    memset(Ver,0,sizeof(Ver));
}

void mkEdge(int a,int b,weight_t c){
//    cout << " >> a : " << a << " >> b : " << b << endl;
    int t1 = Ecnt++;
    int t2 = Ecnt++;

    Edge[t1].node = b;
    Edge[t1].c = c;
    Edge[t1].next = Ver[a];
    Edge[t1].redge = Edge + t2;
    Ver[a] = Edge + t1;

    Edge[t2].node = a;
    Edge[t2].c = 0;
    Edge[t2].next = Ver[b];
    Edge[t2].redge = Edge + t1;
    Ver[b] = Edge + t2;
}
int L[SIZE_V];  //���ͼ

//�������������Դ����Ĳ��ͼ
bool bfs( int s,int t){
    memset(L,-1,sizeof(L));
    vector<int> q;
    q.push_back(s);
    L[s] = 0;

    while( !q.empty() ){
        int u = q.back();
        q.pop_back();

        //Ѱ�һ��в����ı�
        for ( edge_t *p = Ver[u]; p ; p=p->next){
            if ( p->c <= 0) continue;

            int v = p->node;
            if ( -1 != L[v]) continue;

            q.push_back(v);
            L[v] = L[u] + 1;
        }
    }
    return -1 != L[t];
}

//�ڲ��ͼ����������·���������Ͼ��������������������
//��������Ǹ���֮����������Сֵ
//uΪ��ǰ�ڵ㣬cfΪ�Ѿ��������Ľ����tΪ���

int DFS( int u,int cf,int t){

    if ( u == t ) return cf;

    int tf = 0; //tf ��¼u����һ����ܿ�������
    for ( edge_t *p = Ver[u]; p ;p=p->next){

        int v = p->node;
        weight_t c = p->c;

        if ( L[u] + 1 == L[v] && c > 0 && cf > tf ){

            int f = DFS( v, min(c , cf-tf) ,t);
            if ( 0 == f ) continue;

            p->c  -= f;
            p->redge->c += f;
            tf += f;
        }
    }
    if ( 0 == tf ) L[u] = -1;
    return tf;
}

//dinic �㷨 s ΪԴ t Ϊ��
int Dinic( int s, int t ){
    int ret = 0;
    while( bfs(s,t) ){ // ��һ�� �����ֲ�ͼ
        int ans ;
        // �ڶ����ڷֲ�ͼ�ϲ���һ������·���Ŀ�������
        while( ans = DFS(s,INT_MAX,t) )
            ret += ans;
    }
    return ret;
}
bool isLead[SIZE_V];
bool flag( int n ){
    if ( isLead[n] ) return false;
    isLead[n] = 1; return true;
}
int main( ){
    int n,m;
    while ( scanf("%d%d",&n,&m) != EOF ){
        int a,b;
        int s = 0,e = n+1;
        init();
        memset(isLead,0,sizeof(isLead));
        int k = n+2;
        while ( m-- ){
            scanf("%d%d",&a,&b);
            if ( a > b )swap(a,b);

            if ( 1 != a%3 && 1 != b%3 ) continue;
            if ( 1 == a%3 && 1 == b%3 ) continue;

            if ( a % 3 == 0 )mkEdge( s,a,1);
            if ( b % 3 == 0 )mkEdge( s,b,1);
            if ( a % 3 == 1 && flag(a) )mkEdge( a,a+k,1);
            if ( b % 3 == 1 && flag(b) )mkEdge( b,b+k,1);
            if ( a % 3 == 1 && b % 3 == 2 ) mkEdge(a+k,b,1);
            if ( a % 3 == 2 && b % 3 == 1 ) mkEdge(b+k,a,1);
            if ( a % 3 == 0 && b % 3 == 1 ) mkEdge(a,b,1);
            if ( a % 3 == 1 && b % 3 == 0 ) mkEdge(b,a,1);
            if ( a % 3 == 2 ) mkEdge(a,e,1);
            if ( b % 3 == 2 ) mkEdge(b,e,1);
        }
        printf("%d\n",Dinic(s,e));
    }



}
