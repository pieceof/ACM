/*
    ����һ���ʵ䣬����һЩ���ʣ�����
*/

#include <string>
#include <cstdio>
#include <map>
using namespace std;

map<string,string> dictionary;
/*��map<key,value>����*/

/*ע������Ķ���*/
int main(){
    char ch[23],ch1[11],ch2[11];
	while( gets(ch) && *ch ){
		sscanf(ch,"%s%s",ch1,ch2);
        dictionary[string(ch2)] = string(ch1);
	}
	map<string,string>::iterator it;
	while( gets(ch1) ){
        it = dictionary.find(string(ch1));
		if ( dictionary.end() == it ) printf("eh\n");
		else  printf("%s\n",it->second.c_str());
	}
	return 0;
}
