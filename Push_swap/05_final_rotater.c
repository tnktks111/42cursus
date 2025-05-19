#include "push_swap.h"
static int find_min_index(t_list_info *info)
{
    t_circ_doubly_list *curr;
    int i;

    curr = info->head;
    i = 0;
    while (curr->content < curr->nxt->content)
    {
        curr = curr->nxt;
        i++;
    }
    i++;
    return (return_min_dist(i, info->size));
}
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
