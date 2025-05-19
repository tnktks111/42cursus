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

int return_min_dist(int idx, int total)
{
    if (idx <= (total / 2))
        return (idx);
    else
        return -(total - idx);
}
