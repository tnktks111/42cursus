#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#define EXIT_SORTED -1
// #define INT_MAX 2147483647
// #define INT_MIN -2147483648
#define INF 2147483648L

typedef enum e_bool
{
    False, True
} t_bool;

typedef enum e_commands
{
    sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr
} t_commands;

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

typedef struct s_score_info
{
    int a_score;
    int a_rev_score;
    int b_score;
    int b_rev_score;
    int min_score;
} t_score_info;

//doubly_linked_list_utils.c
t_circ_doubly_list *ft_lstnew(long content);
void               sep_node(t_circ_doubly_list *node);
void               insert_node(t_circ_doubly_list *new_node, t_circ_doubly_list *nxt_node);
void               push(t_list_info *dst, t_list_info *src);
void               swap(t_list_info *info);
void               rotate(t_list_info *info, t_bool reverse);
void               free_all_node(t_circ_doubly_list *head);

int argv_parser(int argc, char *argv[], t_list_info *info);

//lis.c
int                lis(t_list_info *info);

void separator(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list);

void insertor(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list);


//11_utils.c

int ft_puterr(void);
long ft_abs(long num);
long ft_min(long a, long b);
long ft_min_four(long a, long b, long c, long d);
long ft_max(long a, long b);
size_t	ft_strlen(const char *s);
long* list_to_array(t_circ_doubly_list *head, int size);
int return_min_dist(int idx, int total);

void final_rotator(t_list_info *info, t_command_list *command_list);

void   quick_sort(long array[], int left, int right);


void    insert_node_tail(t_circ_doubly_list *new_node, t_circ_doubly_list *tail_node);
