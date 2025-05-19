#include "push_swap.h"

int find_median(t_circ_doubly_list *head, int size)
{
    long *l;
    long res;

    l = list_to_array(head, size);
    quick_sort(l, 0, size - 1);
    res = (l[(size - 1) / 2 ] + l[size / 2]) / 2;
    free(l);
    return res;
}

void separator(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list)
{
    int i;
    t_bool lis_started;

    lis_started = False;
    i = info_a->size;
    while (i--)
    {
        if (!(info_a->head)->in_lis)
        {
            push(info_b, info_a, command_list, pb);
            if (command_list->argc > 50 && find_median(info_b->head->nxt, info_b->size - 1) < (info_b->head)->content)
                rotate(info_b, False, command_list, rb);
        }
        else
        {
            while (lis_started == True && info_a->head && info_b->head && (info_a->head)->content > (info_b->head)->content && (info_a->head)->prv->content < (info_b->head)->content)
            {
                push(info_a, info_b, command_list, pa);
                rotate(info_a, False, command_list, ra);
            }
            rotate(info_a, False, command_list, ra);
            lis_started = True;
        }
    }
}
