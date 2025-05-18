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
        "rrr\n"
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

    command_list.total = 0;
    if (argv_parser(argc, argv, &info_a) == EXIT_FAILURE)
        return (ft_puterr());
    if (info_a.size > 1)
    {
        if (lis(&info_a) == EXIT_FAILURE)
        {
            free_all_node(info_a.head);
            return (ft_puterr());
        }
        separator(&info_a, &info_b, &command_list);
        insertor(&info_a, &info_b, &command_list);
        final_rotator(&info_a, &command_list);
    }
    command_printer(command_list);
    return (0);
}