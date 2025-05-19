#include "../push_swap.h"
long ft_min(long a, long b)
{
    if (a > b)
        return (b);
    else
        return (a);
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
        printf("%ld\n", dp[i]);
    i = -1;
    while (++i < size)
        if (dp[i] == INF)
            break;
    return (i);
}

#include <stdio.h>
int main()
{
    long array[3] = {5, 7, 9};
    printf("%d", solve_lis_length(array, 3));
}