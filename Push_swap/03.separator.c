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
            rotate(info_a, False);
            command_list->array[command_list->total++] = ra;
        }
    }
}
