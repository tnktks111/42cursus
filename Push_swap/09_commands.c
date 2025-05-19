#include "push_swap.h"
void    push(t_list_info *dst, t_list_info *src, t_command_list *command_list, t_commands cmd)
{
    t_circ_doubly_list *node_to_move;

    if (src->size == 0)
        return;
    node_to_move = src->head;
    if ((src->size)-- == 1)
        src->head = NULL;
    else
    {
        src->head = (src->head)->nxt;
        sep_node(node_to_move);
    }
    if ((dst->size)++ == 0)
    {
        dst->head = node_to_move;
        node_to_move->nxt = node_to_move;
        node_to_move->prv = node_to_move;
    }
    else
    {
        insert_node(node_to_move, dst->head);
        dst->head = node_to_move;
    }
    if (cmd != pass)
        command_list->array[command_list->total++] = cmd;
}

void swap(t_list_info *info, t_command_list *command_list, t_commands cmd)
{
    int content_tmp;
    int in_lis_tmp;

    if (!info || !info->head || info->size < 2)
        return ;
    content_tmp = (info->head)->content;
    (info->head)->content = (info->head->nxt)->content;
    (info->head->nxt)->content = content_tmp;
    in_lis_tmp = (info->head)->in_lis;
    (info->head)->in_lis = (info->head->nxt)->in_lis;
    (info->head->nxt)->in_lis = in_lis_tmp;
    if (cmd != pass)
        command_list->array[command_list->total++] = cmd;
}

void    rotate(t_list_info *info, t_bool reverse, t_command_list *command_list, t_commands cmd)
{
    if (reverse == True)
        info->head = (info->head)->prv;
    else
        info->head = (info->head)->nxt;
    if (cmd != pass)
        command_list->array[command_list->total++] = cmd;
}

void    rotate_two_stack(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list, t_commands cmd)
{
    if (cmd == rr)
    {
        rotate(info_a, False, command_list, pass);
        rotate(info_b, False, command_list, pass);
        command_list->array[command_list->total++] = rr;
    }
    else
    {
        rotate(info_a, True, command_list, pass);
        rotate(info_b, True, command_list, pass);
        command_list->array[command_list->total++] = rrr;
    }
}