#include "push_swap.h"

typedef struct s_list
{
    int content;
    struct s_list *next;
} t_list;

typedef struct s_list_info
{
    t_list *head;
    t_list *tail;
} t_list_info;

t_list	*ft_lstnew(int content)
{
	t_list	*newnode;

	newnode = malloc(sizeof(t_list));
	if (!newnode)
		return (NULL);
	newnode->content = content;
	newnode->next = NULL;
	return (newnode);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tail;

	if (!lst)
		return (NULL);
	tail = lst;
	while (tail->next)
		tail = tail->next;
	return (tail);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_last;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	cur_last = *lst;
	while (cur_last && cur_last->next)
		cur_last = cur_last->next;
	cur_last->next = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*cur;
	t_list	*tmp;

	if (!lst || !(*lst))
		return ;
	cur = *lst;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
	*lst = NULL;
}



int main(int argc, char *argv[])
{
    int i = 0;
    t_list_info lst_info;
    t_list *cur;

    lst_info.head = NULL;
    lst_info.tail = NULL;
    while (argv[i])
    {
        if (!ft_isdigit(argv[i]))
        {
            ft_lstclear(&lst_info.head);
            ft_putstr_fd("Error\n", 2);
            return (1);
        }
        cur = ft_lstnew(ft_atoi(argv[i]));
        if (!cur)
        {
            ft_lstclear(&lst_info.head);
            ft_putstr_fd("Error\n", 2);
            return (1);
        }
        if (i == 0)
        {
            lst_info.head = cur;
            lst_info.tail = cur;
        }
        else
        {
            ft_lstadd_back(&lst_info.tail, cur);
            lst_info.tail = cur;
        }
    }

}
