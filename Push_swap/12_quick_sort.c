#include "push_swap.h"

static void    int_swap(long *a, long *b)
{
    long tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

static int    partition (long array[], int left, int right) {
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
        int_swap(&array[i], &array[j]);
    }
    int_swap(&array[pivot], &array[j]);
    return j;
}

void   quick_sort(long array[], int left, int right)
{
    int q;

    if (left < right)
    {
        q = partition(array, left, right);
        quick_sort(array, left, q - 1);
        quick_sort(array, q + 1, right);
    }
}

long quick_select(long array[], int left, int right, int k)
{
    int pivot_index;

    if (left == right)
        return array[left];
    pivot_index = partition(array, left, right);
    if (k == pivot_index)
    {
        return array[k];
    }
    else if (k < pivot_index)
        return quick_select(array, left, pivot_index - 1, k);
    else
        return quick_select(array, pivot_index + 1, right, k);
}