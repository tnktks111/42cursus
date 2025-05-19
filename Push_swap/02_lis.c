/*
双方向循環連結リストを受取、dpでLISを捜索、lisの構成要素にフラグを立てる
*/

#include "push_swap.h"

static int free_dp_table(long **table, int allocate)
{
    int i;

    i = 0;
    while (i < allocate)
        free(table[i++]);
    free(table);
    return (EXIT_FAILURE);
}

static int solve_lis_length(long *l, int size)
{
    long *dp;
    int i;
    int j;

    dp = (long *)malloc(sizeof(long) * size);
    if (!dp)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < size)
        dp[i] = INF;
    i = -1;
    while (++i < size)
    {
        j = -1;
        while (++j <= i)
        {
            if (j == 0 || l[i] > dp[j - 1])
                dp[j] = ft_min(l[i], dp[j]);
        }
    }
    i = -1;
    while (++i < size)
        if (dp[i] == INF)
            break;
    return (i);
}

//i...idx, j ... length(- 1)
int lis(t_list_info *info)
{
    t_circ_doubly_list *curr;
    long **dp;
    long *l;
    int i;
    int j;
    int max;
    int tmp;

    max = 0;
    curr = info->head;
    i = -1;
    while (++i < info->size)
    {
        l = list_to_array(curr, info->size);
        tmp = solve_lis_length(l, info->size);
        if (i == 0 && tmp == info->size)
            return (EXIT_SORTED);
        if (tmp < max)
        {
            tmp = max;
            j = i;
        }
        free(l);
        curr = curr->nxt;
    }
    curr = info->head;
    while (j-- > 0)
        curr = curr->nxt;
    l = list_to_array(curr, info->size);
    dp = (long **)malloc(sizeof(long *) * (info->size));
    if (!dp)
        return (EXIT_FAILURE);
    i = -1;
    while (++i < info->size)
    {
        dp[i] = (long *)malloc(sizeof(long) * (info->size));
        if (!dp[i])
            return (free_dp_table(dp, i));
        j = 0;
        while (j < info->size)
            dp[i][j++] = INF;
    }
    i = -1;
    while (++i < info->size)
    {
        j = -1;
        while (++j <= i)
            if (i == 0)
                dp[i][j] = l[0];
            else if (j == 0 || l[i] > dp[i - 1][j - 1])
                dp[i][j] = ft_min(dp[i - 1][j], l[i]);
            else
                dp[i][j] = dp[i - 1][j];
    }
    j = 0;
    while (j < (info->size) && dp[(info->size) - 1][j] != INF)
        j++;
    i = 0;
    while (i < info->size)
        l[i++] = 0;
    i--;
    j--;
    while (i >= 0 && j >= 0)
    {
        if (i == 0 || dp[i - 1][j] != dp[i][j])
        {
            l[i] = 1;
            j--;
        }
        i--;
    }
    i = 0;
    while (i < info -> size)
    {
        curr->in_lis = 0;
        if (l[i++] == 1)
            curr->in_lis = 1;
        curr = curr->nxt;
    }
    free(l);
    free_dp_table(dp, i);
    return (EXIT_SUCCESS);
}
