#include "libft.h"

size_t ft_strlen(const char *s)
{
    if (!s)
        return (0);
    size_t i = 0;
    while (s[i])
        i++;
    return (i);
}


// #include <stdio.h>
// int main()
// {
//     char *s = "aiueoasdfg";
//     printf("%zu\n", strlen(s));
//     printf("%zu\n", ft_strlen(s));
// }