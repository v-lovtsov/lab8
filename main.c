#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "sort.h"

#define slong long long

int find(int *parent, int u)
{
    while (parent[u] != u)
    {
        parent[u] = parent[parent[u]];
        u = parent[u];
    }
    return u;
}

void unionSets(int *parent, int u, int v)
{
    int rootU = find(parent, u);
    int rootV = find(parent, v);
    if (rootU != rootV)
        parent[rootV] = rootU;
}

int getEdgeLength(EDGE *edge)
{
    return edge->length;
}

void sortEdges(EDGE *edges, int size)
{
    quickSortEdges(edges, 0, size - 1);
}

int main()
{
    int N, M;
    if (scanf("%d", &N) != 1)
    {
        printf("bad number of lines\n");
        return 0;
    }
    if (scanf("%d", &M) != 1)
    {
        printf("bad number of lines\n");
        return 0;
    }

    if (N < 0 || N > 5000)
    {
        printf("bad number of vertices\n");
        return 0;
    }

    slong max_edges = (slong)N * (N - 1) / 2;
    if (M < 0 || M > max_edges)
    {
        printf("bad number of edges\n");
        return 0;
    }

    EDGE *edges = (EDGE *)malloc(M * sizeof(EDGE));
    if (edges == NULL)
        return 0;

    for (int i = 0; i < M; i++)
    {
        int start, end, length;
        if (scanf("%d %d %d", &start, &end, &length) != 3)
        {
            printf("bad number of lines\n");
            free(edges);
            return 0;
        }

        if (start < 1 || start > N || end < 1 || end > N)
        {
            printf("bad vertex\n");
            free(edges);
            return 0;
        }

        if (length < 0)
        {
            printf("bad length\n");
            free(edges);
            return 0;
        }

        edges[i].start = start - 1;
        edges[i].end = end - 1;
        edges[i].length = length;
    }

    sortEdges(edges, M);

    int *parent = (int *)malloc(N * sizeof(int));
    if (parent == NULL)
    {
        free(edges);
        return 0;
    }

    for (int i = 0; i < N; i++)
        parent[i] = i;

    EDGE *mst_edges = (EDGE *)malloc((N - 1) * sizeof(EDGE));
    if (mst_edges == NULL)
    {
        free(edges);
        free(parent);
        return 0;
    }

    int mst_size = 0;
    for (int i = 0; i < M && mst_size < N - 1; i++)
    {
        int start = edges[i].start;
        int end = edges[i].end;
        if (find(parent, start) != find(parent, end))
        {
            unionSets(parent, start, end);
            mst_edges[mst_size++] = edges[i];
        }
    }

    if (mst_size != N - 1 && N != 0)
        printf("no spanning tree\n");
    else
        for (int i = 0; i < mst_size; i++)
            printf("%d %d\n", mst_edges[i].start + 1, mst_edges[i].end + 1);

    free(edges);
    free(parent);
    free(mst_edges);

    return 0;
}
