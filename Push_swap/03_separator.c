#include "push_swap.h"

int find_median(t_list_info *info)
{
    long *l;
    long res;

    l = list_to_array(info->head, info->size);
    quick_sort(l, 0, info->size - 1);
    res = (l[(info->size - 1) / 2 ] + l[info->size / 2]) / 2;
    free(l);
    return res;
}

void separator(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list)
{
    int i;

    info_b->head = NULL;
    info_b->size = 0;
    i = info_a->size; 
    while (i--)
    {
        if (!(info_a->head)->in_lis)
        {
            if ((info_b)->head && find_median(info_b) < (info_a->head)->content)
            {
                push(info_b, info_a);
                rotate(info_b, False);
                command_list->array[command_list->total++] = pb;
                command_list->array[command_list->total++] = rb;
            }
            else
            {
                push(info_b, info_a);
                command_list->array[command_list->total++] = pb;
            }
        }
        else
        {
            while (info_a->head && info_b->head && (info_a->head)->content > (info_b->head)->content && (info_a->head)->prv->content < (info_b->head)->content)
            {
                push(info_a, info_b);
                rotate(info_a, False);
                command_list->array[command_list->total++] = pa;
                command_list->array[command_list->total++] = ra;
            }
            rotate(info_a, False);
            command_list->array[command_list->total++] = ra;
        }
    }
}
