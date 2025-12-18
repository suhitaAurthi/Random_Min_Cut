#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v;
};

struct graph
{
    int v, e;
    Edge *edge;
};

struct subset
{
    int parent, rank;
};

int find(struct subset subsets[], int i)
{
    if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void unioon(struct subset subsets[], int x, int y)
{
    int xroot = find(subsets, x), yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int mincut(struct graph *g)
{
    int v = g->v, e = g->e;
    Edge *edge = g->edge;

    struct subset *subsets = new subset[v];

    for (int i = 0; i < v; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int ver = v;
    while (ver > 2)
    {
        int i = rand() % e;

        int subset1 = find(subsets, edge[i].u);
        int subset2 = find(subsets, edge[i].v);

        if (subset1 == subset2)
            continue;
        else
        {
            ver--;
            unioon(subsets, subset1, subset2);
        }

        int cut = 0;
        for (int i = 0; i < e; i++)
        {
            int subset1 = find(subsets, edge[i].u);
            int subset2 = find(subsets, edge[i].v);
            if (subset1 != subset2)
                cut++;
        }

        return cut;
    }
}

struct graph *crete(int v, int e)
{
    graph *g = new graph;
    g->v = v;
    g->e = e;
    g->edge = new Edge[e];
    return g;
};

int main()
{
    int v, e;
    cin >> v >> e;
    // vector<vector<

    struct graph *g = crete(v, e);

    int i = 0;
    while (e--)
    {
        int u1, v1;
        cin >> u1 >> v1;
        g->edge[i].u = u1;
        g->edge[i].v = v1;
        i++;
    }

    srand(time(NULL));

    cout << mincut(g) << endl;
}