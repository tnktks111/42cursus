#include "push_swap.h"

void command_printer(t_command_list command_list)
{
    int i;
    const char *command_strings[] = {
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
        "rrr\n",
        "sample\n"
    };

    i = -1;
    while (++i < command_list.total)
        write(1, command_strings[command_list.array[i]], ft_strlen(command_strings[command_list.array[i]]));
}

int main(int argc, char *argv[])
{
    t_list_info info_a;
    t_list_info info_b;
    t_command_list command_list;
    int signal;

    command_list.argc = argc;
    command_list.total = 0;
    signal = argv_parser(argc, argv, &info_a);
    if (signal == EXIT_FAILURE)
        return (ft_puterr(), 1);
    if (signal == EXIT_SORTED || info_a.size < 2)
        return (0);
    signal = lis(&info_a);
    if (signal == EXIT_FAILURE)
        return (free_all_node(info_a.head), ft_puterr(), 1);
    if (signal == EXIT_SORTED)  
        return (0);
    info_b.head = NULL;
    info_b.size = 0;
    separator(&info_a, &info_b, &command_list);
    if (insertor(&info_a, &info_b, &command_list) == EXIT_FAILURE)
        return (ft_puterr(), 1);
    final_rotator(&info_a, &command_list);
    return (command_printer(command_list), 0);
}
