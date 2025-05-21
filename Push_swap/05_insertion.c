#include "push_swap.h"

void rotate_ab_stack(t_score_info *target_info, t_list_info *info_a, t_list_info *info_b)
{
    if (target_info->rotate_ab_cnt > 0)
    {
        while (target_info->rotate_ab_cnt-- > 0)
            rotate_two_stack(info_a, info_b, rr);
    }
    else
    {
        while (target_info->rotate_ab_cnt++ < 0)
            rotate_two_stack(info_a, info_b, rrr);
    }
    if (target_info->rotate_a_cnt > 0)
    {
        while (target_info->rotate_a_cnt-- > 0)
            rotate(info_a, False, ra);
    }
    else
    {
        while (target_info->rotate_a_cnt++ < 0)
            rotate(info_a, True, rra);
    }
    if (target_info->rotate_b_cnt > 0)
    {
        while (target_info->rotate_b_cnt-- > 0)
            rotate(info_b, False, rb);
    }
    else
    {
        while (target_info->rotate_b_cnt++ < 0)
            rotate(info_b, True, rrb);
    }
}

int insertor(t_list_info *info_a, t_list_info *info_b)
{
    t_score_info *score_info;
    t_score_info *target_info;
    int min_score_idx;
    while (info_b->head)
    {
        score_info = (t_score_info *)malloc(sizeof(t_score_info) * info_b->size);
        if (!score_info)
        {
            free_all_node(info_a->head);
            free_all_node(info_b->head);
            return(EXIT_FAILURE);
        }
        gen_score_info(info_a, info_b, score_info);
        min_score_idx = calc_min_score_idx(score_info, info_b->size);
        target_info = &score_info[min_score_idx];
        decide_rotate_cnt(target_info);
        rotate_ab_stack(target_info, info_a, info_b);
        push(info_a, info_b, pa);
        free(score_info);
    }
    return (EXIT_SUCCESS);
}
