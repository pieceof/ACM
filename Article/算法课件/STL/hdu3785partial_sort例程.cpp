#include <cstdio>
#include <algorithm>
#include <vector>
#include <functional>
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
    partial_sort(V.begin(),V.begin()+M,V.end(),greater<int>()); 
       
    printf("%d",V.front());
    for(vector<int>::iterator it=++V.begin();it!=V.begin()+M;++it){
        printf(" %d",*it);
    }  
    printf("\n");
}
int main(){
    V.reserve(100000);
    while ( read() ) proc();
    return 0;    
}
