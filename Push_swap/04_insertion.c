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

int calc_min_score(t_score_info *score_info)
{
    int res;
    res = ft_max(score_info->a_score, score_info->b_score);
    res = ft_min(res, -ft_min(score_info->a_rev_score, score_info->b_rev_score));
    res = ft_min(res, score_info->a_score - score_info->b_rev_score);
    res = ft_min(res, score_info->b_score - score_info->a_rev_score);
    return (res);
}

int calc_min_score_idx(t_score_info score_info[], int size)
{
    int res;
    int min_score;
    int i;

    i = 0;
    res = 0;
    score_info[i].min_score = calc_min_score(&score_info[i]);
    min_score = calc_min_score(&score_info[i]);
    while (++i < size)
    {
        score_info[i].min_score = calc_min_score(&score_info[i]);
        if (score_info[i].min_score < min_score)
        {
            min_score = score_info[i].min_score;
            res = i;
        }
    }
    return (res);
}

// insert_min_score_node(int min_score_idx, t_score_info score_info, t_command_list *command_list)
// {
//     if (ft_max(score_info.a_score, score_info.b_score) == score_info.min_score)
//     {
        
//     }
//     else if (-ft_min(score_info.a_rev_score, score_info.b_rev_score) == score_info.min_score)
//     {

//     }
//     else if (score_info.a_score - score_info.b_rev_score == score_info.min_score)
//     {

//     }
//     else (score_info.b_score - score_info.a_rev_score == score_info.min_score)
//     {

//     }
// }

void calcularor(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list)
{
    t_score_info *score_info;
    t_score_info *target_info;
    int i;
    int min_score_idx;

    score_info = (t_score_info *)malloc(sizeof(t_score_info) * info_b->size);
    if (!score_info)
        return;
    gen_score_info(info_a, info_b, score_info);
    min_score_idx = calc_min_score_idx(score_info, info_b->size);
    // insert_min_score_node(min_score_idx, score_info[min_score_idx], command_list);
    target_info = &score_info[min_score_idx];
    if (ft_max(target_info->a_score, target_info->b_score) == target_info->min_score)
    {
        i = ft_min(target_info->a_score, target_info->b_score);
        while (i--)
        {
            rotate(info_a, False);
            rotate(info_b, False);
            command_list->array[command_list->total++] = rr;
        }
        i = ft_abs(target_info->a_score - target_info->b_score);
        if (target_info->a_score > target_info->b_score)
        {
            while (i--)
            {
                rotate(info_a, False);
                command_list->array[command_list->total++] = ra;
            }
        }
        else
        {
            while (i--)
            {
                rotate(info_b, False);
                command_list->array[command_list->total++] = rb;
            }
        }
    }
    else if (-ft_min(target_info->a_rev_score, target_info->b_rev_score) == target_info->min_score)
    {
        i = -ft_max(target_info->a_rev_score, target_info->b_rev_score);
        while (i--)
        {
            rotate(info_a, True);
            rotate(info_b, True);
            command_list->array[command_list->total++] = rrr;
        }
        i = ft_abs(target_info->a_rev_score - target_info->b_rev_score);
        if (target_info->a_rev_score > target_info->b_rev_score)
        {
            while (i--)
            {
                rotate(info_b, True);
                command_list->array[command_list->total++] = rrb;
            }
        }
        else
        {
            while (i--)
            {
                rotate(info_a, True);
                command_list->array[command_list->total++] = rra;
            }
        }
    }
    else if (target_info->a_score - target_info->b_rev_score == target_info->min_score)
    {
        i = target_info->a_score;
        while (i--)
        {
            rotate(info_a, False);
            command_list->array[command_list->total++] = ra;
        }
        i = -target_info->b_rev_score;
        while (i--)
        {
            rotate(info_b, True);
            command_list->array[command_list->total++] = rrb;
        } 
    }
    else
    {
        i = -target_info->a_rev_score;
        while (i--)
        {
            rotate(info_a, True);
            command_list->array[command_list->total++] = rra;
        }
        i = target_info->b_score;
        while (i--)
        {
            rotate(info_b, False);
            command_list->array[command_list->total++] = rb;
        }
    }
    push(info_a, info_b);
    command_list->array[command_list->total++] = pa;
    free(score_info);
}

void insertor(t_list_info *info_a, t_list_info *info_b, t_command_list *command_list)
{
    while (info_b->head)
        calcularor(info_a, info_b, command_list);
}
