#include "libft.h"

int ft_isascii(int c)
{
    if (c >= 0 && c <= 127)
        return (1);
    else
        return (0);
}

// #include <ctype.h>
// #include <stdio.h>

// int main()
// {
//     char c = '\t';
//     printf("%d\n", isascii(c));
//     printf("%d\n", ft_isascii(c));
// }