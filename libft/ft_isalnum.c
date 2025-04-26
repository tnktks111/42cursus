#include "libft.h"

int ft_isalnum(int c)
{
    if (ft_isalpha(c) || ft_isdigit(c))
        return (1);
    else
        return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int main()
// {
//     char c = 's';
//     printf("%d\n", isalnum(c));
//     printf("%d\n", ft_isalnum(c));
// }