#include "push_swap.h"

long* list_to_array(t_circ_doubly_list *head, int size)
{
    long *array;
    int i;

    array = (long *)malloc(sizeof(long) * size);
    if (!array)
        return (NULL);
    i = 0;
    while (i < size)
    {
        array[i++] = head->content;
        head = head->nxt;
    }
    return (array);
}

int find_insert_point(long *array, int size, int target)
{
    int left;
    int right;
    int mid;

    left = 0;
    right = size - 1;
    if (array[left] < array[right] && (target < array[left] || target > array[right]))
        return (0);
    if (array[right] < target && target < array[left])
        return (0);
    while (right - left > 1)
    {
        mid = (right - left) / 2 + left;
        if (array[mid] < array[right])
        {
            if (target > array[mid] && target < array[right])
                left = mid;
            else
                right = mid;
        }
        else
        {
            if (target > array[left] && target < array[mid])
                right = mid;
            else
                left = mid;
        }
    }
    return (right);
}

int find_median(t_circ_doubly_list *head, int size)
{
    long *l;
    long res;

    l = list_to_array(head, size);
    res = (quick_select(l, 0, size - 1, (size - 1) / 2) + quick_select(l, 0, size - 1, size / 2)) / 2;
    free(l);
    return res;
}

int find_min_index_in_sorted_list(t_list_info *info)
{
    t_circ_doubly_list *curr;
    int i;

    curr = info->head;
    i = 0;
    while (curr->content < curr->nxt->content)
    {
        curr = curr->nxt;
        i++;
    }
    i++;
    return (return_min_dist(i, info->size));
}

int return_min_dist(int idx, int total)
{
    if (idx <= (total / 2))
        return (idx);
    else
        return -(total - idx);
}
