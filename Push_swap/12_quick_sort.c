#include "push_swap.h"

static void    swap(int *a, int *b)
{
    int tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

static int    partition (int array[], int left, int right) {
    int i;
    int j;
    int pivot;

    i = left;
    j = right + 1;
    pivot = left;
    while (i < j)
    {
        while (array[++i] < array[pivot] && i != right);
        while (array[pivot] < array[--j] && j != left);
        if (i >= j)
            break;
        swap(&array[i], &array[j]);
    }
    swap(&array[pivot], &array[j]);
    return j;
}

void   quick_sort(int array[], int left, int right)
{
    int q;

    if (left < right)
    {
        q = partition(array, left, right);
        quick_sort(array, left, q - 1);
        quick_sort(array, q + 1, right);
    }
}
