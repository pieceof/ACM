#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define SIZE 100000

struct node_t{
	node_t* child[26];//26个儿子
	//int idx;//对应解释的序号
	int cnt;
}Node[SIZE];
int toUsed = 1;

//idx表示单词对应解释的序号
void insert(char const word[]){
    node_t* loc = Node;
    for(int i=0;word[i];++i){
    	int sn = word[i] - 'a';
    	if ( !loc->child[sn] ) loc->child[sn] = Node + toUsed ++;
    	loc = loc->child[sn];
    	loc->cnt++;
    }
    //loc->idx = idx;
}

int find(node_t*loc ,int depth){
    if (loc->cnt <= 1 )
        return 1*depth;
    int ret = 0;
    for (int i = 0;i < 26;++i ){
        if ( loc->child[i] ){
           ret += find(loc->child[i],depth+1);
        }
    }
    return ret;
}

char str[SIZE];
int main()
{

    int t , n;
    scanf("%d",&t);
    while( t-- ){

        toUsed = 1;
        memset(Node,0,sizeof(Node));
        //cout <<sizeof(Node)<<endl;
        scanf("%d",&n);
        for (int i = 0;i < n;++i ){
            scanf("%s",str);
            insert(str);
        }
        int ans = 0;
        node_t *loc = Node;
        for (int i = 0;i < 26;++i)
            if ( loc->child[i] )
                ans += find(loc->child[i],1);
        printf("%d\n",ans);
    }



    return 0;

}
