#include "push_swap.h"

void free_dp_table(long **table, int allocate)
{
    int i;

    i = 0;
    while (i < allocate)
        free(table[i++]);
    free(table);
}

long **init_dp_table(int size)
{
    long **dp;
    int i;
    int j;

    dp = (long **)malloc(sizeof(long *) * size);
    if (!dp)
        return (NULL);
    i = -1;
    while (++i < size)
    {
        dp[i] = (long *)malloc(sizeof(long) * size);
        if (!dp[i])
            return (free_dp_table(dp, i), NULL);
        j = 0;
        while (j < size)
            dp[i][j++] = INF;
    }
    return (dp);
}

long **create_dp_table(long **dp, long *l, int size)
{
    int i;
    int j;

    i = -1;
    while (++i < size)
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
    return (dp);
}

void lis_restorator(long **dp, long *l, int size)
{
    int i;
    int j;
    j = 0;
    while (j < (size) && dp[size - 1][j] != INF)
        j++;
    i = 0;
    while (i < size)
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
}