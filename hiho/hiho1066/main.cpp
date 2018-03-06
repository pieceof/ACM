#include "../../headers.h"

vector<string > nameTable;

map<string ,int > nameId;
int nameCnt;

int getNameId(string name){
    if (nameId.count(name))
        return nameId[name];
    else {
        nameTable.push_back(name);
        return nameId[name] = nameCnt++;
    }
}

int fa[200000+200];

void init( int n ){
    nameCnt = 0;
    nameId.clear();
    nameTable.clear();

    for (int i = 0 ;i < n;++i )
        fa[i] = i;
}
int find( int x ){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void unite( int x,int y ){
    if ( find(x) == find(y) ) return;
    fa[find(x)] = find(y);
}


int main(){

    int n;
    string name1,name2;
    while( scanf("%d",&n) != EOF ){
        init(n+n);
        int op;
        for (int i = 0;i < n;++i){
            scanf("%d",&op);
            cin>>name1>>name2;
            int x = getNameId(name1);
            int y = getNameId(name2);
            if ( op == 0 ){
                unite(x,y);
            }else{
                if ( find(x) == find(y) )
                    printf("yes\n");
                else
                    printf("no\n");
            }
        }

    }

    return 0;
}
