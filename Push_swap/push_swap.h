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
typedef enum e_commands{sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr} t_commands;

typedef struct s_command_list
{
    t_commands array[10000];
    int total;
} t_command_list;

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
t_circ_doubly_list *ft_lstnew(long content);
void               sep_node(t_circ_doubly_list *node);
void               insert_node(t_circ_doubly_list *new_node, t_circ_doubly_list *nxt_node);
void               push(t_list_info *dst, t_list_info *src);
void               swap(t_list_info *info);
void               rotate(t_list_info *info, int reverse);

//lis.c
int                lis(t_list_info *info);

//separator.c
void separator(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list);