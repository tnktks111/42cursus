#include "push_swap.h"

void final_rotator(t_list_info *info, t_command_list *command_list)
{
    int i;

    i = find_min_index_in_sorted_list(info);
    while (i > 0)
    {
        rotate(info, False, command_list, ra);
        i--;
    }
    while (i < 0)
    {
        rotate(info, True, command_list, rra);
        i++;
    }
}
