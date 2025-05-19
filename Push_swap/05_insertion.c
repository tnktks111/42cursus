#include "push_swap.h"

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
