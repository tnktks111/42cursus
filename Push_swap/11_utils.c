#include "push_swap.h"

int ft_puterr(void)
{
    write(2, "Error\n", 6);
    return (1);
}

long ft_min(long a, long b)
{
    if (a > b)
        return (b);
    else
        return (a);
}

long ft_max(long a, long b)
{
    if (a > b)
        return (a);
    else
        return (b);
}

long ft_abs(long num)
{
    if (num < 0)
        num *= -1;
    return (num);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int* list_to_array(t_circ_doubly_list *head, int size)
{
    int *array;
    int i;

    array = (int *)malloc(sizeof(int) * size);
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

int return_min_dist(int idx, int total)
{
    if (idx <= (total / 2))
        return (idx);
    else
        return -(total - idx);
}
//にぶたん
int find_insert_point(int *array, int size, int target)
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