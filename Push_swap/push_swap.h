#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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
    sa, sb, ss, pa, pb, ra, rb, rr, rra, rrb, rrr, sample, pass
} t_commands;

typedef struct s_command_list
{
    t_commands array[10000];
    int total;
    int argc;
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
    int rotate_a_cnt;
    int rotate_b_cnt;
    int rotate_ab_cnt;
} t_score_info;

int argv_parser(int argc, char *argv[], t_list_info *info);
int lis(t_list_info *info);
void separator(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list);
int insertor(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list);
void final_rotator(t_list_info *info, t_command_list *command_list);

void    push(t_list_info *dst, t_list_info *src, t_command_list *command_list, t_commands cmd);
void    swap(t_list_info *info, t_command_list *command_list, t_commands cmd);
void    rotate(t_list_info *info, t_bool reverse, t_command_list *command_list, t_commands cmd);
void    rotate_two_stack(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list, t_commands cmd);

void free_dp_table(long **table, int allocate);
long **init_dp_table(int size);
long **create_dp_table(long **dp, long *l, int size);
void lis_restorator(long **dp, long *l, int size);

void gen_score_info(t_list_info *info_a, t_list_info *info_b, t_score_info score_info[]);
void calc_min_score(t_score_info *score_info);
int calc_min_score_idx(t_score_info score_info[], int size);
void set_rotate_cnt(t_score_info *score_info, int a, int b, int ab);
void decide_rotate_cnt(t_score_info *s_info);

t_circ_doubly_list *ft_lstnew(long content);
void    sep_node(t_circ_doubly_list *node);
void    insert_node(t_circ_doubly_list *new_node, t_circ_doubly_list *nxt_node);
void    insert_node_tail(t_circ_doubly_list *new_node, t_circ_doubly_list *tail_node);
void    free_all_node(t_circ_doubly_list *head);

int ft_puterr(void);
long ft_min(long a, long b);
long ft_max(long a, long b);
long ft_abs(long num);
size_t	ft_strlen(const char *s);

long*   list_to_array(t_circ_doubly_list *head, int size);
int     find_insert_point(long *array, int size, int target);
int     find_median(t_circ_doubly_list *head, int size);
int     find_min_index_in_sorted_list(t_list_info *info);
int     return_min_dist(int idx, int total);

void    quick_sort(long array[], int left, int right);
long    quick_select(long array[], int left, int right, int k);
#endif