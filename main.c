#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "sort.h"

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

    long long maxEdges = (long long)N * (N - 1) / 2;
    if (M < 0 || M > maxEdges)
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

    EDGE *mstEdges = (EDGE *)malloc((N - 1) * sizeof(EDGE));
    if (mstEdges == NULL)
    {
        free(edges);
        free(parent);
        return 0;
    }

    int mstSize = 0;
    for (int i = 0; i < M && mstSize < N - 1; i++)
    {
        int start = edges[i].start;
        int end = edges[i].end;
        if (find(parent, start) != find(parent, end))
        {
            unionSets(parent, start, end);
            mstEdges[mstSize++] = edges[i];
        }
    }

    if (mstSize != N - 1 && N != 0)
        printf("no spanning tree\n");
    else
        for (int i = 0; i < mstSize; i++)
            printf("%d %d\n", mstEdges[i].start + 1, mstEdges[i].end + 1);

    free(edges);
    free(parent);
    free(mstEdges);

    return 0;
}