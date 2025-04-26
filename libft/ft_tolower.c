#include "libft.h"

static int ft_isupper(int c)
{
    if (c >= 65 && c <= 90)
        return (1);
    else
        return (0);
}

int ft_tolower(int c)
{
    if (ft_isupper(c))
        c += 32;
    return (c);
}