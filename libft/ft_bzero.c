#include <strings.h>
void ft_bzero(void *s, size_t n)
{
    char *c = (char *)s;
    while (n)
    {
        *c++ = '\0';
        n--;
    }
}