#ifndef sort_h
#define sort_h
#include "edge.h"

void swap(EDGE *n1, EDGE *n2)
{
    EDGE temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}

int partition(EDGE *arr, int low, int high)
{
    int pivot = arr[high].length;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j].length <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSortEdges(EDGE *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSortEdges(arr, low, pi - 1);
        quickSortEdges(arr, pi + 1, high);
    }
}

#endif