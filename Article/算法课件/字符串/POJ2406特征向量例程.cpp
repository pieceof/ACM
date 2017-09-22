//���ַ���S=s^n��������n
//����aaaa = a^4 = (aa)^2�������4
//���S����ΪL,s�ĳ���Ϊl,��S���һ��������һ����L-l
//����L��l��n��
#include <cstdio>
#include <cstring>
using namespace std;
#define SIZE 1000005

void getNext(char const P[],int n,int next[]){
	next[0] = 0;
	for(int i=1;i<n;++i){
		int k = next[i-1];
		while( k > 0 && P[k] != P[i] ) k = next[k-1];
		next[i] = ( P[i] == P[k] ) ? k + 1 : 0;
	}
	return;
}

char P[SIZE];
int Next[SIZE];
int main() {
	while( scanf("%s",P) ){
		if ( '.' == *P && '\0' == P[1] ) return 0;
        int len = strlen(P);
		getNext(P,len,Next);
		/*
		void dispArray(int const [],int);
		dispArray(Next,len);
		//*/
        if ( len % ( len - Next[len-1] ) ) printf("1\n");
        else printf("%d\n",len/(len-Next[len-1]));
	}
	return 0;
}

//������ 
void dispArray(int const a[],int n){
	for(int i=0;i<n;++i){
		printf("%d ",a[i]);
	}
	printf("\n");
}
