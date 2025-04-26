#include "libft.h"

// count digits of positive num
static int count_digit(long n)
{
    if (0 <= n && n <= 9)
        return (1);
    return (1 + count_digit(n / 10));
}

char  *ft_itoa(int n)
{
    int i;
    int len;
    char *numstr;
    unsigned int un;
    if (n >= 0)
    {
        len = count_digit(n);
        numstr = malloc(len + 1);
        if (!numstr)
            return (NULL);
        numstr[len] = '\0';
        i = len - 1;
        while (i >= 0)
        {
            numstr[i--] = '0' + n % 10;
            n /= 10;
        }
    }
    else
    {
        un = (unsigned int)(-((long)n));
        len = count_digit(un) + 1;
        numstr = malloc(len + 1);
        if (!numstr)
            return (NULL);
        numstr[len] = '\0';
        numstr[0] = '-';
        i = len - 1;
        while (i >= 1)
        {
            numstr[i--] = '0' + un % 10;
            un /= 10;
        }
    }
    return (numstr);
}