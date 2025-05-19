#include "push_swap.h"

void final_rotator(t_list_info *info, t_command_list *command_list)
{
    int i;

    i = find_min_index(info);
    if (i > 0)
    {
        while (i--)
            rotate(info, False, command_list, ra);
    }
    else
    {
        i *= -1;
        while (i--)
            rotate(info, True, command_list, rra);
    }
}
