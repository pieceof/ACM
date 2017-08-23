#include "../../headers.h"

typedef int weight_t;
/** \����ͼƥ�䣨�������㷨��DFSʵ�֣�
 * �ٽ�� �����( /2 )
 * CALL:ret=hungary();������ƥ����
 * ʱ�临�Ӷ�:O(VE);
 *********
 */
// �洢����ͼ ��ߵļ��ϸ��ұ߼��ϱߵ���Ϣ
// ����б�Ϊ 1 , û��Ϊ 0
const int SIZE_V = 2000+500;
const int SIZE_E = 10000+500;
struct edge_t{
    int node;
    int next;
}Edge[SIZE_E];
int Ecnt ; // = 0
int Ver[SIZE_V];
void mkEdge( int a,int b ){
    Edge[Ecnt].node = b;
    Edge[Ecnt].next = Ver[a];
    Ver[a] = Ecnt++;

    Edge[Ecnt].node = a;
    Edge[Ecnt].next = Ver[b];
    Ver[b] = Ecnt++;
}
void init_Graph(){
    Ecnt = 1;
    CLEAR(Ver);
}
int Link[SIZE_V]; //�����ұ߼��ϵ� i, link[i]����Ӧ��߼��ϵ� node
bool vis[SIZE_V];
/**< ������ߵļ��ϵ�node�ڵ� ������·�� */
bool DFS( int u){
    /**< ���ұ߼��ϵ�ÿ��������һ�� */
    for (int next = Ver[u];next;next = Edge[next].next ){
        int v = Edge[next].node;
        /**< ����Ѿ��ҹ� */
        if ( vis[v] )continue; vis[v] = true;
        /**< ����������δ�ǵ� ���߸õ㻹���ҵ�����·�� */
        if ( Link[v] == -1 || DFS( Link[v] ) ){
            Link[v] = u;
            return true;
        }
    }
    return false;
}

int hungary(int n ){
    int ret = 0;
    memset(Link , -1 ,sizeof(Link));
    //����߼��ϵ�ÿ����������·��
    for (int u = 1;u <= n;++u){
        memset(vis,0,sizeof(vis));
        if (DFS(u)) ret++;
    }
    return ret;
}

int main(){
    int n,m;
//    int t;scanf("%d",&t);while( t-- ){
    while ( scanf("%d%d",&n,&m) != EOF ){
        int x,y;
        init_Graph();
        while ( m-- ){
            scanf("%d%d",&x,&y);
            mkEdge(x,y);
        }
        int ans = hungary(n)/2;
        printf("%d\n%d\n",ans,n-ans);
    }
    return 0;
}
