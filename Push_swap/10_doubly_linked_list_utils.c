/*
ft_lstnew ... receive a content and return node
sep_node ... separate a linked list node
insert_node ... insert "new_node" before "nxt_node"
push ... push "src" head to "dst"
swap ... receive a "t_list_info" and apply "swap" to it
rotate ... rotate cicular linked list
*/

#include "push_swap.h"

t_circ_doubly_list *ft_lstnew(long content)
{
	t_circ_doubly_list *newnode;

	newnode = malloc(sizeof(t_circ_doubly_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->nxt = newnode;
    newnode->prv = newnode;
	return (newnode);
}

void    sep_node(t_circ_doubly_list *node)
{
    if (!node)
        return;
    (node->prv)->nxt = node->nxt;
    (node->nxt)->prv = node->prv;
}

void    insert_node(t_circ_doubly_list *new_node, t_circ_doubly_list *nxt_node)
{
    if (!new_node || !nxt_node)
        return;
    (new_node)->prv = nxt_node->prv;
    (new_node)->nxt = nxt_node;
    (nxt_node->prv)->nxt = new_node;
    nxt_node->prv = new_node;
}

void    push(t_list_info *dst, t_list_info *src)
{
    t_circ_doubly_list *node_to_move;

    if (src->size == 0)
        return;
    node_to_move = src->head;
    if (src->size == 1)
        src->head = NULL;
    else
    {
        src->head = (src->head)->nxt;
        sep_node(node_to_move);
    }
    (src->size)--;
    if (dst->size == 0)
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
    (dst->size)++;
}

void swap(t_list_info *info)
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
}

void    rotate(t_list_info *info, t_bool reverse)
{
    if (reverse)
        info->head = (info->head)->prv;
    else
        info->head = (info->head)->nxt;
}

void    free_all_node(t_circ_doubly_list *head)
{
    t_circ_doubly_list *curr;
    t_circ_doubly_list *tmp;

    if (!head)
        return;
    curr = head->nxt;
    while (curr && curr != head)
    {
        tmp = curr;
        curr = curr->nxt;
        free(tmp);
    }
    free(head);
}

void    insert_node_tail(t_circ_doubly_list *new_node, t_circ_doubly_list *tail_node)
{
    if (!new_node || !tail_node)
        return;
    (new_node)->nxt = (tail_node)->nxt;
    ((tail_node)->nxt)->prv = new_node;
    (tail_node)->nxt = new_node;
    (new_node)->prv = tail_node;
}
