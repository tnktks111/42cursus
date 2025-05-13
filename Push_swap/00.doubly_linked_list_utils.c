/*
ft_lstnew ... receive a content and return node
del_node ... delete a linked list node
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

void    del_node(t_circ_doubly_list *node)
{
    (node->prv)->nxt = node->nxt;
    (node->nxt)->prv = node->prv;
}

void    insert_node(t_circ_doubly_list *new_node, t_circ_doubly_list *nxt_node)
{
    (new_node)->prv = nxt_node->prv;
    (new_node)->nxt = nxt_node;
    (nxt_node->prv)->nxt = new_node;
    nxt_node->prv = new_node;
}

void    push(t_list_info *dst, t_list_info *src)
{
    t_list_info *new_src_head;
    del_node(src->head);
    new_src_head = (src->head)->nxt;
    insert_node(src->head, dst->head);
    dst->head = src->head;
    src->head = new_src_head;
    dst->size += 1;
    src->size -= 1;
}

void swap(t_list_info *info)
{
    int content_tmp;
    int in_lis_tmp;
    content_tmp = (info->head)->content;
    (info->head)->content = (info->head->nxt)->content;
    (info->head->nxt)->content = content_tmp;
    in_lis_tmp = (info->head)->in_lis;
    (info->head)->in_lis = (info->head->nxt)->in_lis;
    (info->head->nxt)->in_lis = in_lis_tmp;
}

void    rotate(t_list_info *info, int reverse)
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
    curr = head->nxt;
    while (curr && curr != head)
    {
        tmp = curr;
        curr = curr->nxt;
        free(tmp);
    }
    free(head);
}
