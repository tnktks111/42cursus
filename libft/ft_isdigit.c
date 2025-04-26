#include "libft.h"

int ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

// #include <ctype.h>
// #include <stdio.h>
// int main()
// {
//     char c = '5';
//     printf("%d\n", isdigit(c));
//     printf("%d\n", ft_isdigit(c));
// }