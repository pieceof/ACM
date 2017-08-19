#include "../../headers.h"
/// ------------------------------ code line ------------------------------//



//拓扑排序
/*注意初始化init();
 *点从0开始计算; 读入数据的时候要-1;输出的时候要加1
*/


int const SIZE_E = 1000010;
int const SIZE_V = 10010;
struct edge_t{
    int v;
    int next;
}Edge[SIZE_E];
int Ecnt;
int Ver[SIZE_V];
int InDeg[SIZE_V];

inline void mkEdge(int a,int b){
    Edge[Ecnt].v = b;
    Edge[Ecnt].next = Ver[a];
    Ver[a] = Ecnt++;
    InDeg[b]++;
}

//存储排序的结果
int ansSort[SIZE_V];
int n;
int AScnt;


int topoSort(){

    int isMUlt = 0;
    queue <int> q;
    for (int i = 1; i <= n;++i)
        if (InDeg[i] == 0)
            q.push(i);
    if ( q.size() > 1 ) isMUlt = 1;
    while(!q.empty()){
        int u = q.front();
        ansSort[AScnt++] = u;
        q.pop();
        int InCnt = 0;
        for (int next = Ver[u]; next != -1 ;next = Edge[next].next){
            int v = Edge[next].v;
            InDeg[v]--;
            if (0 == InDeg[v])
                q.push(v),InCnt++;
        }
        if ( InCnt > 1 )isMUlt = 1;
    }
    for (int i = 1;i <= n;++i )
        if ( InDeg[i] != 0 ) return 0;

    if ( isMUlt ) return 2;
    return 1;
}
inline void init(){
    Ecnt = 0;
    AScnt = 0;
    FLAG(Ver);
    CLEAR(InDeg);
}

char str[1024][1024];
int len[1024];
char word[3];

int main()
{
    while( ~scanf("%s%d",word,&n) ){
        for (int i = 0;i < n;++i ){
            scanf("%s",str[i]);
            len[i] = strlen(str[i]);
        }
        init();
        for (int i = 0;i < n-1;++i){
            int l = min(len[i],len[i+1]);
            for (int j = 0;j < l;++j ){
                if ( str[i][j] == str[i+1][j] ) continue;
                else {
                    int x = str[i][j]-'a'+1;
                    int y = str[i+1][j]-'a'+1;
                    mkEdge( x , y );
                    break;
                }
            }
        }
        n = *word-'a'+1;
        int ans = topoSort();
        if (ans == 2 ){
            printf("AMBIGUOUS\n");
        }else if ( ans == 1 ){
            for (int i = 0;i < AScnt;++i )
                printf("%c",ansSort[i] + 'a' - 1);
            printf("\n");
        }else {
            printf("IMPOSSIBLE\n");
        }

    }
    return 0;
}
