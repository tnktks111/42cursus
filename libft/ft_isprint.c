#include "libft.h"

int ft_isprint(int c)
{
    if (c >= 32 && c <= 126)
        return (1);
    else
        return (0);
}

// #include <ctype.h>
// #include <stdio.h>
// int main()
// {
//     char c = '@';
//     printf("%d\n", isprint(c));
//     printf("%d\n", ft_isprint(c));
// }