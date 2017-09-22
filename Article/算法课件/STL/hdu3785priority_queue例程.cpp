#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

int N,M;
vector<int> V;
bool read(){
    scanf("%d%d",&N,&M);
    if ( 0 == N && 0 == M ) return false; 
    V.clear();
    for(int i=0;i<N;++i){
        int x;
        scanf("%d",&x);
        V.push_back(x);        
    }
    return true;
}
void proc(){
    priority_queue<int> q(less<int>(),V); 
    if ( M > N ) M = N;    
    printf("%d",q.top());
    q.pop();  
    for(int i=1;i<M;++i){
        printf(" %d",q.top());
        q.pop();          
    }  
    printf("\n");
}
int main(){
    V.reserve(100000);
    while ( read() ) proc();
    return 0;    
}
