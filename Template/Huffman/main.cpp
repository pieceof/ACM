#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>


const int MaxLen_str = 100;
const int MaxSum_str = 100;
const int MaxLen_code = 100;

struct Node {
    int weight;
    int Lson,Rson,parent;
    Node(int w=0,int l=0,int r=0,int p=0):weight(w),Lson(l),Rson(r),parent(p) {}
};
struct CodeString {
    char str[MaxLen_str];
    int weight;
};

/**< ����δ���������,���ַ�������,stdin���� */
int Read_UnencodeDate_muilt( int n,CodeString *Input_Date,CodeString *EncodeDate);
/**< ���봦�������,�ַ���+Ȩֵ, stdin���� */
void Read_UnencodeDate_uniqu( int n,CodeString *EncodeDate);
/**< ��huffman��������������С����*/
void _Search_min( Node *tree,int s,int e, int *l,int *r );
/**< ����huffmn �� */
Node* Creat_HuffmanTree( int n,CodeString *EncodeDate  );
/**< ����huffman ���� */
char** Creat_HuffmanCode( int n,Node* HuffTree );

void _Print_EncodeDate( int n,CodeString *EncodeDate );
void _Print_HuffmanCode( int n, CodeString *EncodeDate,char **HuffmanCode);
/**< �ļ���������� */
int  _Read_HuffmanCode( CodeString *EncodeDate,char ***HuffmanCode);
void _Save_HuffmanCode( int n, CodeString *EncodeDate,char **HuffmanCode);
/**< qsort���� ���� */
int _cmpCodeString_byAscii(const void *a,const void *b);
int _cmpCodeString_byWeight(const void *a,const void *b);
/**< �ݹ��ӡhuffman ��,������ʽ */
void _Print_HuffmanTree(Node* HuffTree,Node* p,char str[]);
/**< ��ʾ�˵� */
void Showmenu() {
    printf("******************************\n");
    printf("|       Please choose        |\n");
    printf("|      I.Initialization      |\n");
    printf("|      E.Encoding            |\n");
    printf("|      D.Decoding            |\n");
    printf("|      P.Printing            |\n");
    printf("|      T.TreePrint           |\n");
    printf("|      Q.Quit                |\n");
    printf("******************************\n");
    printf("Please Input Your Option:\n");
}

/**< ��ͼ����,���÷�װ�� huffman api ���� */
int Initialization( CodeString *EncodeDate,char ***HuffmanCode );
void Encoding( int n, CodeString *EncodeDate,char **HuffmanCode);
void Decoding( int n, CodeString *EncodeDate,char ** HuffmanCode);
void Print();
void Treeprint(Node* HuffTree);


void solve ( ) {
    int n ;
//    CodeString Input_Date[MaxSum_str];
    CodeString EncodeDate[MaxSum_str];
    char **HuffmanCode  ;

    bool isInit = false;
//    freopen("input.txt","r",stdin);

    char cmd[2];
    while ( 1 ) {
        Showmenu();
        scanf("%s",cmd);
        switch ( *cmd ) {
        case 'I':
            n = Initialization(EncodeDate,&HuffmanCode);
            isInit = true;
            break;
        case 'E':
            if ( !isInit ) n = _Read_HuffmanCode( EncodeDate,&HuffmanCode);
            Encoding(n, EncodeDate, HuffmanCode);
            break;
        case 'D':
            if ( !isInit ) n = _Read_HuffmanCode( EncodeDate,&HuffmanCode);
            Decoding(n, EncodeDate, HuffmanCode);
            break;
        case 'P':
            Print();
            break;
        case 'T':{
            if ( !isInit ) n = _Read_HuffmanCode( EncodeDate,&HuffmanCode);
            Node* hufftree = Creat_HuffmanTree(  n, EncodeDate  );
            Treeprint(hufftree);
            break;
            }
        case 'Q':
            exit(0);
            break;
        default:
            break;
        }
    }
}

int main() {
    solve();
    return 0;
}
int Initialization( CodeString *EncodeDate,char ***HuffmanCode ) {
    int n;

    printf("���������ݼ�����n\n");
    scanf("%d",&n);
    printf("���������ݼ�, n��, ÿ��һ���ַ��� һ��Ȩֵ,�ո���� \n");
    Read_UnencodeDate_uniqu( n, EncodeDate);
    Node *hufftree = Creat_HuffmanTree(n,EncodeDate);
    *HuffmanCode = Creat_HuffmanCode(n,hufftree);

    _Print_HuffmanCode(n,EncodeDate,*HuffmanCode);
    _Save_HuffmanCode( n, EncodeDate,*HuffmanCode);
    return n;
}
void Encoding( int n, CodeString *EncodeDate,char **HuffmanCode) {

    char from[MaxLen_str];
    FILE *frp,*fwp;
    if(NULL==(frp=(fopen("ToBeTran.txt","r"))))
        printf("��ToBeTran.txtʧ��\n");
    if(NULL==(fwp=(fopen("CodeFile.txt","w"))))
        printf("��CodeFile.txtʧ��\n");

    while ( !feof(frp) ) {

        fgets(from,MaxLen_str,frp);
        from[strlen(from)-1] = '\0';
        for (int i = 0; i < n; ++i ) {
            if ( 0 == strcmp(EncodeDate[i].str,from) ) {
                fprintf(fwp,"%s\n",HuffmanCode[i]);
                break;
            }
        }
    }
    fclose(frp);
    fclose(fwp);
}
void Decoding( int n, CodeString *EncodeDate,char ** HuffmanCode) {

    char from[MaxLen_code];
    FILE *frp,*fwp;
    if(NULL==(frp=(fopen("CodeFile.txt","r"))))
        printf("��CodeFile.txtʧ��\n");
    if(NULL==(fwp=(fopen("Text.txt","w+"))))
        printf("��Text.txtʧ��\n");

    while ( !feof(frp)) {
        fgets(from,MaxLen_code,frp);
        from[strlen(from)-1] = '\0';
        for (int i = 0; i < n; ++i ) {
            if ( 0 == strcmp(HuffmanCode[i],from) ) {
                fprintf(fwp,"%s\n",EncodeDate[i].str);
                break;
            }
        }
    }
    fclose(frp);
    fclose(fwp);
}

void Print() {
    FILE *frp;
    char from[MaxLen_code];
    if(NULL==(frp=(fopen("CodeFile.txt","r"))))
        printf("��CodeFile.txtʧ��\n");

    while ( fgets(from,MaxLen_code,frp) ) {
        printf("%s\n",from);
    }
    fclose(frp);
}
void Treeprint(Node* HuffTree){
    int head = 0;
    while ( HuffTree[head].parent != -1 )
        head = HuffTree[head].parent;
    char str[10000] = "";
    _Print_HuffmanTree(HuffTree,HuffTree+head,str);
}


void Read_UnencodeDate_uniqu( int n,CodeString *EncodeDate) {
    for ( int i = 0; i < n; ++i ) {
        scanf("%s%d",EncodeDate[i].str,&EncodeDate[i].weight);
    }
}
int Read_UnencodeDate_muilt( int n,CodeString *Input_Date,CodeString *EncodeDate) {

    for ( int i = 0; i < n; ++i )scanf("%s",Input_Date[i].str);
    qsort(Input_Date,n,sizeof(Input_Date[0]),_cmpCodeString_byAscii);
    int cnt_date = 0;
    for (int i = 0; i < n; ) {
        int j = i+1;
        strcpy(EncodeDate[cnt_date].str,Input_Date[i].str);
        EncodeDate[cnt_date].weight = 1;
        while ( strcmp(Input_Date[i].str,Input_Date[j].str) == 0 && j < n )
            EncodeDate[cnt_date].weight++, j++;
        i = j, cnt_date ++;
    }
    return cnt_date;
}

Node* Creat_HuffmanTree( int n,CodeString *EncodeDate  ) {

    //һ����n��Ҷ�ӽڵ�ĺշ���������2n-1���ڵ�
    int total = 2*n-1;

    Node* HuffTree = (Node*)malloc(total*sizeof(Node));

    for ( int i = 0 ; i < total ; i++ )
        HuffTree[i] = (i < n ) ? Node( EncodeDate[i].weight,-1,-1,-1):
                      Node( 0,-1,-1,-1);

    for(int i = n; i<total; i++) {
        int l,r;
        _Search_min( HuffTree,0,i-1, &l,&r );

        HuffTree[l].parent = HuffTree[r].parent = i;

        HuffTree[i].Lson = l;
        HuffTree[i].Rson = r;
        HuffTree[i].weight = HuffTree[l].weight + HuffTree[r].weight;
    }
    return HuffTree;
}

char** Creat_HuffmanCode( int n,Node* HuffTree ) {

    char **HuffmanCode = (char** )malloc(n*sizeof(char *));

    //������n��Ҷ�ӽڵ�ĺշ���������Ҷ�ӽڵ�ı��볤���������n-1
    char* _tmpCode = (char *)malloc(n*sizeof(char));

    _tmpCode[n-1] = '\0';

    for (int i = 0; i < n ; i++ ) {

        int current = i;           //���嵱ǰ���ʵĽڵ�
        int father = HuffTree[i].parent; //��ǰ�ڵ�ĸ��ڵ�
        int start = n-1;           //ÿ�α����λ�ã���ʼΪ�����������λ��
        //��Ҷ�ӽڵ�����շ�����ֱ�����ڵ�
        while(father != -1) {
            if(HuffTree[father].Lson == current)   //��������ӣ������Ϊ0
                _tmpCode[--start] = '0';
            else                              //������Һ��ӣ������Ϊ1
                _tmpCode[--start] = '1';
            current = father;
            father = HuffTree[father].parent;
        }

        //Ϊ��i���ַ��ı��봮����洢�ռ�
        HuffmanCode[i] = (char *)malloc((n-start)*sizeof(char));

        //�����봮��code���Ƶ�HC
        strcpy(HuffmanCode[i],_tmpCode+start);
    }
    return HuffmanCode;
}


void _Search_min( Node *tree,int s,int e, int *l,int *r ) {
    int fri = INT_MAX;
    int sec = INT_MAX;
    *l = *r = 0;
    for (int i = s ; i <= e ; ++i ) {
        if ( tree[i].parent != -1 ) continue;
        if ( tree[i].weight < fri ) {
            *r = *l,*l = i;
            sec = fri,fri = tree[i].weight;
        } else if ( tree[i].weight < sec ) {
            *r = i;
            sec =  tree[i].weight;
        }
    }
}
int _cmpCodeString_byAscii(const void * a,const void *b) { //qsort��Ҫ�����const
    return strcmp((*(CodeString *)a).str,(*(CodeString *)b).str) ; //�ֵ����С����
    //return strcmp((char *)b,(char *)a) ; //�ֵ���Ӵ�С
}
int _cmpCodeString_byWeight(const void * a,const void *b) { //qsort��Ҫ�����const
    return (*(CodeString *)a).weight > (*(CodeString *)b).weight; //�ֵ����С����
    //return strcmp((char *)b,(char *)a) ; //�ֵ���Ӵ�С
}

void _Print_EncodeDate( int n,CodeString *EncodeDate ) {
    printf(" ======= the date needing encoding is following  ====== \n");
    for (int i = 0; i < n; i++ ) {
        printf("==>  %s  :   %d\n", EncodeDate[i].str,EncodeDate[i].weight);
    }
}
void _Print_HuffmanCode( int n, CodeString *EncodeDate,char **HuffmanCode) {
    printf(" ============ the huffuman code ===========\n");
    for (int i = 0 ; i < n ; i++ ) {
        printf("==> the ( id: %d,weight: %d,str: %s)   :  %s\n", i,EncodeDate[i].weight,EncodeDate[i].str,HuffmanCode[i]);
    }
}
void _Save_HuffmanCode( int n, CodeString *EncodeDate,char **HuffmanCode) {
    FILE *fp;
    fp=fopen("hfmTree.txt","w+");
    fprintf(fp,"%d\n",n);
    for ( int i = 0 ; i < n; ++i ) {
        fprintf(fp,"%s %d %s\n",EncodeDate[i].str,EncodeDate[i].weight,HuffmanCode[i]);
    }
    fclose(fp);
}
void _Print_HuffmanTree(Node* HuffTree,Node* p,char str[]){

    char str_copy[10000] = "";
    strcpy( str_copy , str);
    strcat(str_copy,"      ");
    if ( p->Lson != -1)
        _Print_HuffmanTree(HuffTree,p->Lson+HuffTree,str_copy);
    printf("%s(%d,%d)\n",str,p-HuffTree,p->weight);
    if ( p->Rson != -1)
        _Print_HuffmanTree(HuffTree,p->Rson+HuffTree,str_copy);
}
int  _Read_HuffmanCode( CodeString *EncodeDate,char ***HuffmanCode) {
    int n;
    FILE *fp;
    fp=fopen("hfmTree.txt","r");
    fscanf(fp,"%d\n",&n);
    *HuffmanCode = (char** )malloc(n*sizeof(char *));
    char tmp[MaxLen_code+MaxLen_str+10], tmp2[MaxLen_code];
    for ( int i = 0 ; i < n; ++i ) {
        fgets(tmp,MaxLen_code,fp);
        sscanf(tmp,"%s %d %s",EncodeDate[i].str,&EncodeDate[i].weight,tmp2);
        (*HuffmanCode)[i] = (char *)malloc((strlen(tmp2))*sizeof(char));
        strcpy((*HuffmanCode)[i],tmp2);
    }
    fclose(fp);
    return n;
}
