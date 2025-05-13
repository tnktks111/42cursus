#include "push_swap.h"

static int	ft_isdigit(int c)
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
        if (sign > 0 && num > INT_MAX || sign < 0 && num > -(long)INT_MIN)
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
    i = 0;
	while (++i < argc)
	{
		new_content = ft_atoi_for_pushswap(argv[i]);
        new_node = ft_lstnew(new_content);
        if (new_content == LONG_MAX || !new_node)
            return(free_all_node(head), NULL);
        if (!head)
        {
            head = new_node;
            curr = head;
        }
        else
        {
            curr->nxt = new_node;
            (curr->nxt)->prv = curr;
            curr = curr->nxt;
        }
	}
    curr->nxt = head;
    head->prv = curr;
	return (head);
}

int argv_parser(int argc, char *argv[], t_list_info *info)
{
    info->head = ft_lstmap(argc, argv);
    if (!info->head)
        return (EXIT_FAILURE);
    info->size = argc - 1;
    return (EXIT_SUCCESS);
}
