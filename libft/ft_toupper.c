#include "libft.h"

static int ft_islower(int c)
{
    if (c >= 97 && c <= 122)
        return (1);
    else
        return (0);
}

int ft_toupper(int c)
{
    if (ft_islower(c))
        c -= 32;
    return (c);
}