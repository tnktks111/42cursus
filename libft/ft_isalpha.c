#include "libft.h"

static int ft_islower(int c)
{
    if (c >= 97 && c <= 122)
        return (1);
    else
        return (0);
}

static int ft_isupper(int c)
{
    if (c >= 65 && c <= 90)
        return (1);
    else
        return (0);
}

int ft_isalpha(int c)
{
    if (ft_islower(c) || ft_isupper(c))
        return (1);
    else
        return (0);
}

// #include <ctype.h>
// #include <stdio.h>
// int main()
// {
//     char c = 'f';
//     printf("%d\n", isalpha(c));
//     printf("%d\n", ft_isalpha(c));
// }