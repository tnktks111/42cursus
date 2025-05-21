#include "push_swap.h"

void final_rotator(t_list_info *info)
{
    int i;

    i = find_min_index_in_sorted_list(info);
    while (i > 0)
    {
        rotate(info, False, ra);
        i--;
    }
    while (i < 0)
    {
        rotate(info, True, rra);
        i++;
    }
}
