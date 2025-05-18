#include "push_swap.h"
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
            push(info_b, info_a);
            command_list->array[command_list->total++] = pb;
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
