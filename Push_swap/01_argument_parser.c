#include "push_swap.h"

static int	ft_isdigit(long c)
{
	return (c >= '0' && c <= '9');
}

static long	ft_atoi_for_pushswap(const char *str)
{
	long	num;
	long	sign;

	if (!str)
		return (LONG_MAX);
	num = 0;
	sign = 1;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str++ == '-')
			sign *= -1;
	}
    if (!ft_isdigit(*str))
        return (LONG_MAX);
	while (*str && ('0' <= *str && *str <= '9'))
	{
		num = num * 10 + (*str++ - '0');
        if ((sign > 0 && num > INT_MAX) || (sign < 0 && num > -(long)INT_MIN))
            return (LONG_MAX);
	}
    if (*str)
        return (LONG_MAX);
	return (sign * num);
}

t_circ_doubly_list	*ft_lstmap(int argc, char *argv[])
{
	t_circ_doubly_list	*head;
    t_circ_doubly_list  *curr;
	t_circ_doubly_list  *new_node;
	long new_content;
    int i;

	head = NULL;
    i = 1;
	while (i < argc)
	{
		new_content = ft_atoi_for_pushswap(argv[i++]);
        new_node = ft_lstnew(new_content);
        if (!head)
        {
            head = new_node;
            curr = head;
        }
        else
            insert_node_tail(new_node, curr);
        curr = curr->nxt;
        if (new_content == LONG_MAX || !new_node)
            return(free_all_node(head), NULL);
	}
	return (head);
}

static t_bool contains_duplicate(t_list_info *list_a)
{   
    long *l_a;
    int i;

    l_a = list_to_array(list_a->head, list_a->size);
    quick_sort(l_a, 0, list_a->size - 1);
    i = -1;
    while (++i < list_a->size - 1)
    {
        if (l_a[i] == l_a[i + 1])
            return (True);
    }
    free(l_a);
    return (False);
}

int argv_parser(int argc, char *argv[], t_list_info *info)
{
    info->head = ft_lstmap(argc, argv);
    if (!info->head && argc == 1)
        return (EXIT_SORTED);
    if (!info->head)
        return (EXIT_FAILURE);
    info->size = argc - 1;
    if (contains_duplicate(info) == True)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
