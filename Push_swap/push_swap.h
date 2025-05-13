#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define True 1
#define False 0
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define INF 2147483648

typedef struct s_circ_doubly_list
{
    long content;
    int in_lis;
    struct s_circ_doubly_list *nxt;
    struct s_circ_doubly_list *prv;
} t_circ_doubly_list;

typedef struct s_list_info
{
    t_circ_doubly_list *head;
    int size;
} t_list_info;

//doubly_linked_list_utils.c
t_circ_doubly_list *ft_lstnew(int content);
void               del_node(t_circ_doubly_list *node);
void               insert_node(t_circ_doubly_list *new_node, t_circ_doubly_list *nxt_node);
void               push(t_list_info *dst, t_list_info *src);
void               swap(t_list_info *info);
void               rotate(t_list_info *info, int reverse);

int     lis(t_list_info *info);