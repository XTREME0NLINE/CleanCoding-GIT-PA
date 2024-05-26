#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node *next;
} NODE;

typedef struct g
{
    int v;
    int *vis;
    NODE **alst;
} GPH;

typedef struct s{
    int t;
    int scap;
    int *arr;
} STK;

NODE *create_node(int v){
    NODE *nn=malloc(sizeof(NODE));
    nn->data=v;
    nn->next=NULL;
    return nn;
}

void add_edge(GPH *g,int src,int dest)
{
    NODE *nn=create_node(dest);
    nn->next=g->alst[src];
    g->alst[src]=nn;
    nn=create_node(src);
    nn->next=g->alst[dest];
    g->alst[dest]=nn;
}

GPH *create_g(int v)
{
    GPH *g=malloc(sizeof(GPH));
    g->v=v;
    g->alst=malloc(v * sizeof(NODE *));
    g->vis=malloc(v * sizeof(int));

    for (int i=0;i<v;i++)
    {
        g->alst[i]=NULL;
        g->vis[i]=0;
    }

    return g;
}

STK *create_s(int scap)
{
    STK *s=malloc(sizeof(STK));
    s->arr=malloc(scap*sizeof(int));
    s->t = -1;
    s->scap=scap;

    return s;
}

void push(int pshd,STK *s)
{
    s->t=s->t+1;
    s->arr[s->t]=pshd;
}

void DFS(GPH *g,STK *s,int v_nr)
{
    NODE *adj_list=g->alst[v_nr];
    NODE *aux=adj_list;
    g->vis[v_nr]=1;
    printf("%d ",v_nr);
    push(v_nr,s);
    while (aux != NULL){
        int con_ver=aux->data;
        if (g->vis[con_ver]==0)
            DFS(g,s,con_ver);
        aux=aux->next;
    }
}

void insert_edges(GPH *g,int edg_nr)
{
    int src,dest;
    printf("adauga %d munchii\n",edg_nr);
    for (int i=0;i<edg_nr;i++)
    {
        scanf("%d%d",&src,&dest);
        add_edge(g,src,dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i=0;i<nrv;i++)
    {
        g->vis[i] = 0;
    }
}  

void canbe(GPH *g, int nrv, STK *s1, STK *s2)
{
    int ans = 0;
    for (int i = 0; i < nrv; i++)
    {
        DFS(g, s1, i);
        wipe(g, nrv);
        DFS(g, s2, i);
        for (int j = 0; j < nrv && !ans; j++)
            if ((s1->arr[j] == i) && (s2->arr[j] == i))
                ans = 1;
    }
    printf("%d\n", ans);
}

int main()
{
    int nrv;
    int edg_nr;

    printf("cate noduri are girafa?");
    scanf("%d", &nrv);

    printf("cate muchii are giraful?");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr);

    canbe(g, nrv, s1, s2);

    return 0;
}