#include "push_swap.h"
//0 1 2 3 4 5 6
//0 1 2 3 -3 -2 -1

//にぶたん
int find_insert_point(long *array, int size, int target)
{
    int left;
    int right;
    int mid;

    left = 0;
    right = size - 1;
    if (array[left] < array[right] && (target < array[left] || target > array[right]))
        return (0);
    if (array[right] < target && target < array[left])
        return (0);
    while (right - left > 1)
    {
        mid = (right - left) / 2 + left;
        if (array[mid] < array[right])
        {
            if (target > array[mid] && target < array[right])
                left = mid;
            else
                right = mid;
        }
        else
        {
            if (target > array[left] && target < array[mid])
                right = mid;
            else
                left = mid;
        }
    }
    return (right);
}

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

void rotate_ab_stack(t_score_info *target_info, t_list_info *info_a, t_list_info *info_b, t_command_list *command_list)
{
    if (target_info->rotate_ab_cnt > 0)
    {
        while (target_info->rotate_ab_cnt-- > 0)
            rotate_two_stack(info_a, info_b, command_list, rr);
    }
    else
    {
        while (target_info->rotate_ab_cnt++ < 0)
            rotate_two_stack(info_a, info_b, command_list, rrr);
    }
    if (target_info->rotate_a_cnt > 0)
    {
        while (target_info->rotate_a_cnt-- > 0)
            rotate(info_a, False, command_list, ra);
    }
    else
    {
        while (target_info->rotate_a_cnt++ < 0)
            rotate(info_a, True, command_list, rra);
    }
    if (target_info->rotate_b_cnt > 0)
    {
        while (target_info->rotate_b_cnt-- > 0)
            rotate(info_b, False, command_list, rb);
    }
    else
    {
        while (target_info->rotate_b_cnt++ < 0)
            rotate(info_b, True, command_list, rrb);
    }
}

int insertor(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list)
{
    t_score_info *score_info;
    t_score_info *target_info;
    int min_score_idx;
    while (info_b->head)
    {
        score_info = (t_score_info *)malloc(sizeof(t_score_info) * info_b->size);
        if (!score_info)
            return(EXIT_FAILURE);
        gen_score_info(info_a, info_b, score_info);
        min_score_idx = calc_min_score_idx(score_info, info_b->size);
        target_info = &score_info[min_score_idx];
        decide_rotate_cnt(target_info);
        rotate_ab_stack(target_info, info_a, info_b, command_list);
        push(info_a, info_b, command_list, pa);
        free(score_info);
    }
    return (EXIT_SUCCESS);
}
