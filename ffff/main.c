#include <stdio.h>
#include <stdlib.h>
#define max 1001
#define wq 65535
struct GNode
{
    int Nv;
    int Ne;
    int G[max][max];
};
struct ENode
{
    int v1;
    int v2;
    int weight;
};
struct GNode * create(int Nv)
{
    struct GNode * Graph;
    Graph=(struct GNode *)malloc(sizeof(struct GNode));
    Graph->Nv=Nv;
    Graph->Ne=0;
    for(int i=0;i<Graph->Nv;i++)
    {
        for(int j=0;j<Graph->Nv;j++)
        {
            Graph->G[i][j]=wq;
        }
    }
    return Graph;
}
void insert(struct GNode * Graph,struct ENode *E)
{
    Graph->G[E->v1-1][E->v2-1]=E->weight;
    Graph->G[E->v2-1][E->v1-1]=E->weight;
}
int find(struct GNode * Graph,int *dist)
{
    int min=wq,minv;
    for(int i=0;i<Graph->Nv;i++)
    {
        if(dist[i]!=0&&dist[i]<min)
        {
            min=dist[i];
            minv=i;
        }
    }
    if(min<wq)
    {
        return minv;
    }
    else
    {
        return -1;
    }
}
int prim(struct GNode * Graph)
{
    int dist[Graph->Nv];
    int parent[Graph->Nv];
    int cnt=0;
    int totalweight=0;
    for(int v=0;v<Graph->Nv;v++)
    {
        dist[v]=Graph->G[v][0];
        parent[v]=0;
    }
    dist[0]=0;
    parent[0]=-1;
    cnt++;
    int v;
    while(1)
    {
        v=find(Graph,dist);
        if(v==-1)
        {
            break;
        }
        totalweight+=dist[v];
        dist[v]=0;
        cnt++;
        for(int w=0;w<Graph->Nv;w++)
        {
            if(Graph->G[v][w]<wq&&dist[w]!=0)
            {
                if(Graph->G[v][w]<dist[w])
                {
                    dist[w]=Graph->G[v][w];
                    parent[w]=v;
                }
            }
        }
    }
    if(cnt==Graph->Nv)
    {
        return totalweight;
    }
    else
    {
        return -1;
    }
}
int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    struct GNode * Graph;
    Graph=create(n);
    struct ENode * E;
    E=(struct ENode *)malloc(sizeof(struct ENode));
    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d",&E->v1,&E->v2,&E->weight);
        insert(Graph,E);
    }
    int sum=prim(Graph);
    if(sum!=-1)
    {
        printf("%d\n",sum);
    }
    else
    {
        printf("Impossible");
    }
    return 0;
} 
