#include <cstdio>
#include <algorithm>
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
    if ( M > N ) M = N; 
    make_heap(V.begin(),V.end());
       
    printf("%d",V.front());
    pop_heap(V.begin(),V.end());
    V.pop_back();
    for(int i=1;i<M;++i){
        printf(" %d",V.front());
        pop_heap(V.begin(),V.end());
        V.pop_back();
    }  
    printf("\n");
}
int main(){
    V.reserve(100000);
    while ( read() ) proc();
    return 0;    
}
