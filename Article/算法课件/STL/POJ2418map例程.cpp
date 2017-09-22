#include <map>
#include <iostream>
#include <string>
using namespace std;

int main(){
	map<string,int> m;
	int total = 0;
	char str[33];
	while( gets(str) ){
        ++ m[string(str)];
		++total;
	}
	for(map<string,int>::iterator it=m.begin();it!=m.end();++it)
		printf("%s %.4f\n",it->first.c_str(),(float)it->second*100.0/(float)total);
	return 0;
}
