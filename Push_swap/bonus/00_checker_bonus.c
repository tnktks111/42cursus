#include "get_next_line/get_next_line.h"
#include "push_swap.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i]
		&& i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_commands command_checker(char *s)
{
    if (ft_strncmp(s, "sa", 2) == 0)
        return (sa);
    if (ft_strncmp(s, "sb", 2) == 0)
        return (sb);
    if (ft_strncmp(s, "ss", 2) == 0)
        return (ss);
    if (ft_strncmp(s, "pa", 2) == 0)
        return (pa);
    if (ft_strncmp(s, "pb", 2) == 0)
        return (pb);
    if (ft_strncmp(s, "ra", 2) == 0)
        return (ra);
    if (ft_strncmp(s, "rb", 2) == 0)
        return (rb);
    if (ft_strncmp(s, "rr", 2) == 0)
        return (rr);
    if (ft_strncmp(s, "rra", 2) == 0)
        return (rra);
    if (ft_strncmp(s, "rrb", 2) == 0)
        return (rrb);
    if (ft_strncmp(s, "rrr", 2) == 0)
        return (rrr);
    else
        return (Error);
}

void operator(t_commands cmd, t_list_info *info_a, t_list_info *info_b)
{
    if (cmd == sa)
        swap(info_a, pass);
    else if (cmd == sb)
        swap(info_b, pass);
    else if (cmd == ss)
    {
        swap(info_a, pass);
        swap(info_b, pass);
    }
    else if (cmd == pa)
        push(info_a, info_b, pass);
    else if (cmd == pb)
        push(info_a, info_b, pass);
    else if (cmd == ra || cmd == rra)
        rotate(info_a, (t_bool)(cmd == rra), pass);
    else if (cmd == rb || cmd == rrb)
        rotate(info_b, (t_bool)(cmd == rrb), pass);
    else if (cmd == rr || cmd == rrr)
    {
        rotate(info_b, (t_bool)(cmd == rrr), pass);
        rotate(info_b, (t_bool)(cmd == rrr), pass);
    }
}

int is_sorted(t_list_info *info_a)
{
    int i;
    t_circ_doubly_list *curr;

    curr = info_a->head;
    i = info_a->size - 1;
    while (i-- > 0)
    {
        if (!curr->nxt || curr->content >= curr->nxt->content)
            return (0);
        curr = curr->nxt;
    }
    return (1);
}

int main(int argc, char *argv[])
{
    t_list_info info_a;
    t_list_info info_b;
    t_commands cmd;
    int signal;
    char *s;
    
    if (argc == 1)
        return (0);
    if (argv_parser(argc, argv, &info_a) == EXIT_FAILURE)
        return (ft_puterr(), 1);
    info_b.head = NULL;
    info_b.size = 0;
    s = get_next_line(0);
    while (s)
    {
        cmd = command_checker(s);
        if (cmd == Error)
            return(ft_puterr(), 1);
        operator(cmd, &info_a, &info_b);
    }
    if (!is_sorted(&info_a) || info_b.size != 0)
        write(1, "KO\n", 3);
    else
        write(1, "OK\n", 3);
    return (0);
}
