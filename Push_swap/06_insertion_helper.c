#include "push_swap.h"

void gen_score_info(t_list_info *info_a, t_list_info *info_b, t_score_info score_info[])
{
    int i;
    long *l_a;
    t_circ_doubly_list *curr;

    l_a = list_to_array(info_a->head, info_a->size);
    if (!l_a)
        return; 
    i = -1;
    curr = info_b->head;
    while (++i < info_b->size)
    {
        score_info[i].a_score = find_insert_point(l_a, info_a->size, curr->content);
        score_info[i].a_rev_score = -((info_a->size - score_info[i].a_score) % info_a->size);
        score_info[i].b_score = i;
        score_info[i].b_rev_score = -((info_b->size - i) % info_b->size);
        curr = curr->nxt;
    }
    free(l_a);
}

void calc_min_score(t_score_info *score_info)
{
    int res;
    res = ft_max(score_info->a_score, score_info->b_score);
    res = ft_min(res, -ft_min(score_info->a_rev_score, score_info->b_rev_score));
    res = ft_min(res, score_info->a_score - score_info->b_rev_score);
    res = ft_min(res, score_info->b_score - score_info->a_rev_score);
    score_info->min_score = res;
}

int calc_min_score_idx(t_score_info score_info[], int size)
{
    int res;
    int min_score;
    int i;

    i = 0;
    res = 0;
    calc_min_score(&score_info[0]);
    min_score = score_info[0].min_score;
    while (++i < size)
    {
        calc_min_score(&score_info[i]);
        if (score_info[i].min_score < min_score)
        {
            min_score = score_info[i].min_score;
            res = i;
        }
    }
    return (res);
}

void set_rotate_cnt(t_score_info *score_info, int a, int b, int ab)
{
    score_info->rotate_a_cnt = a;
    score_info->rotate_b_cnt = b;
    score_info->rotate_ab_cnt = ab;
}

void decide_rotate_cnt(t_score_info *s_info)
{
    if ((s_info->min_score) == ft_max(s_info->a_score, s_info->b_score))
    {
        if (s_info->a_score > s_info->b_score)
            set_rotate_cnt(s_info, s_info->a_score - s_info->b_score, 0, s_info->b_score);
        else
            set_rotate_cnt(s_info, 0, s_info->b_score - s_info->a_score, s_info->a_score);
    }
    else if (s_info->min_score == -ft_min(s_info->a_rev_score, s_info->b_rev_score))
    {
        if (s_info->a_rev_score < s_info->b_rev_score)
            set_rotate_cnt(s_info, s_info->a_rev_score - s_info->b_rev_score, 0, s_info->b_rev_score);
        else
            set_rotate_cnt(s_info, 0, s_info->b_rev_score - s_info->a_rev_score, s_info->a_rev_score);
    }
    else if (s_info->min_score == s_info->a_score - s_info->b_rev_score)
        set_rotate_cnt(s_info, s_info->a_score, s_info->b_rev_score, 0);
    else
        set_rotate_cnt(s_info, s_info->a_rev_score, s_info->b_score, 0);
}