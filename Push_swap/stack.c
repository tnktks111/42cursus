#include "push_swap.h"

typedef struct s_circ_doubly_list
{
    int content;
    t_circ_doubly_list *nxt;
    t_circ_doubly_list *prv;
} t_circ_doubly_list;

typedef struct s_list_info
{
    t_circ_doubly_list *head;
    int size;
} t_list_info;

t_circ_doubly_list *ft_lstnew(int content)
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

void    swap_node(t_circ_doubly_list *prv, t_circ_doubly_list *nxt)
{
    t_circ_doubly_list *tmp;
    tmp = prv;
    prv = nxt;
    nxt = prv;
}

void    del_node(t_circ_doubly_list *node)
{
    (node->prv)->nxt = (node->nxt)->prv;
    (node->nxt)->prv = (node->prv)->nxt;
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

void    rotate(t_list_info *info, int reverse)
{
    if (reverse)
        info->head = (info->head)->prv;
    else
        info->head = (info->head)->nxt;
}

void    merge_sort(t_list_info *dst, t_list_info *src, int len)
{
    t_circ_doubly_list *dst_last;
    t_circ_doubly_list *src_last;
    while (len)
    {
        dst_last = (dst->head)->prv;
        src_last = (src->head)->prv;
        if (dst_last->content < src_last->content)
            push(dst, src);
        else
            rotate(dst, False);
        len--;
    }
}

void    insertion_sort

int calc_min_run(int n)
{
    int r;
    while (n >= 64)
    {
        r |= n & 1;
        n >>= 1;
    }
    return (n + r);
}

void    timsort()