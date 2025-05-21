#include "push_swap.h"

void command_printer(t_commands cmd)
{
    static const char *command_strings[] = {
        "sa\n",
        "sb\n",
        "ss\n",
        "pa\n",
        "pb\n",
        "ra\n",
        "rb\n",
        "rr\n",
        "rra\n",
        "rrb\n",
        "rrr\n"
    };

    write(1, command_strings[cmd], ft_strlen(command_strings[cmd]));
}

int main(int argc, char *argv[])
{
    t_list_info info_a;
    t_list_info info_b;
    int signal;

    signal = argv_parser(argc, argv, &info_a);
    if (signal == EXIT_FAILURE)
        return (ft_puterr(), 1);
    if (signal == EXIT_SORTED || info_a.size < 2)
        return (0);
    signal = lis(&info_a);
    if (signal == EXIT_FAILURE)
        return (ft_puterr(), 1);
    info_b.head = NULL;
    info_b.size = 0;
    separator(&info_a, &info_b);
    if (insertor(&info_a, &info_b) == EXIT_FAILURE)
        return (ft_puterr(), 1);
    final_rotator(&info_a);
    free_all_node(info_a.head);
    free_all_node(info_b.head);
    return (0);
}
