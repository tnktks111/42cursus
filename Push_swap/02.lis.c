/*
双方向循環連結リストを受取、dpでLISを捜索、lisの構成要素にフラグを立てる
*/

#include "push_swap.h"

long ft_min(long a, long b)
{
    if (a < b)
        return (a);
    else
        return (b);
}

int free_dp_table(long **table, int allocate)
{
    int i;

    i = 0;
    while (i < allocate)
        free(table[i++]);
    free(table);
    return (EXIT_FAILURE);
}

int lis(t_list_info *info)
{
    t_circ_doubly_list *curr;
    long **dp;
    long *l;
    int i;
    int j;

    l = (long *)malloc(sizeof(long) * (info->size));
    if (!l)
        return (EXIT_FAILURE);
    i = -1;
    curr = info->head;
    while (++i < info->size)
    {
        l[i] = curr->content;
        curr = curr->nxt;
    }
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
    curr = info->head;
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
