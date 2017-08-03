#include <cstdio>

#define MAX_N 30
#define MOD 9973

int n,m;
long long t;
int adj[MAX_N][MAX_N];
int tran[100][MAX_N*MAX_N][MAX_N*MAX_N];
int count[2][MAX_N*MAX_N];

void read_input()
{
    scanf("%d %d %lld",&n,&m,&t);
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            adj[i][j] = 0;

    for(int i=0; i<m; i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        u--;
        v--;
        adj[u][v] = adj[v][u] = 1;
    }
}

inline int pairnum(int u, int v)
{
    return u*n + v;
}

void init_first_matrix()
{
    for(int u1=0; u1<n; u1++)
        for(int v1=0; v1<n; v1++)
            for(int u2=0; u2<n; u2++)
                for(int v2=0; v2<n; v2++)
                {
                    int uu = pairnum(u1,v1);
                    int vv = pairnum(u2,v2);

                    if((u1!=u2) && (v1!=v2) &&
                            (adj[u1][u2]) && (adj[v1][v2]) &&
                            (u1!=v1) && (u2!=v2))
                    {
                        //printf("-- (%d,%d) - (%d,%d)\n",u1,v1,u2,v2);
                        tran[0][uu][vv] = 1;
                    }
                    else
                    {
                        tran[0][uu][vv] = 0;
                    }
                }
    for(int u=0; u<n; u++)
        for(int v=0; v<n; v++)
            count[0][pairnum(u,v)] = 0;
    count[0][pairnum(0,n-1)] = 1;
}

void build_trans()
{
    int n2 = n*n;

    for(int i=0; i<50; i++)
    {
        //printf("%d\n",i);
        for(int uu=0; uu<n2; uu++)
        {
            for(int vv=0; vv<n2; vv++)
            {
                tran[i+1][uu][vv] = 0;

                for(int ww=0; ww<n2; ww++)
                {
                    tran[i+1][uu][vv] += tran[i][uu][ww] * tran[i][ww][vv];
                    tran[i+1][uu][vv] %= MOD;
                }
                //printf("%d ",tran[i][uu][vv]);
            }
            //printf("\n");
        }
        //printf("------------------------\n");
    }
}

void process()
{
    init_first_matrix();
    build_trans();

    int cur = 0;
    int nx = 1;
    int n2 = n*n;
    long long tt = t - 1;

    int tidx = 0;
    while(tt != 0)
    {
        nx = (cur+1) % 2;
        if(tt % 2 !=0)
        {
            //printf("> %d\n",tidx);
            // printf("=== %d\n",count[0][3]);
            for(int vv=0; vv<n2; vv++)
            {
                count[nx][vv] = 0;
                // printf("=== %d,%d,%d\n",nx,vv,count[0][3]);
            }
            // printf("=== %d\n",count[0][3]);
            for(int uu=0; uu<n2; uu++)
            {
                for(int vv=0; vv<n2; vv++)
                {
                    count[nx][vv] += tran[tidx][uu][vv] * count[cur][uu];
                    count[nx][vv] %= MOD;
                }

                /*
                printf(">> %d:",uu);
                for(int vv=0; vv<n2; vv++) {
                  printf("%d ",count[nx][vv]);
                }
                printf("\n");
                */
            }
        }
        else
        {
            for(int vv=0; vv<n2; vv++)
            {
                count[nx][vv] = count[cur][vv];
            }
        }
        /*
        printf("================\n");
        for(int uu=0; uu<n2; uu++) {
          printf("%d ",count[nx][uu]);
        }
        printf("\n");
        */
        tidx++;
        tt /= 2;

        cur = (cur+1)%2;
    }

    int output = 0;
    for(int u=0; u<n; u++)
        for(int v=0; v<n; v++)
        {
            int endcount = 0;
            for(int x=0; x<n; x++)
            {
                if(adj[u][x] && adj[v][x])
                {
                    endcount++;
                }
            }
            output += endcount * count[cur][pairnum(u,v)];
            output %= MOD;
        }
    printf("%d\n",output);
}


main()
{
    int k;
    scanf("%d",&k);
    for(int i=0; i<k; i++)
    {
        read_input();
        process();
    }
}
