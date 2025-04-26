static int ft_isspace(int c)
{
    if (c == ' ' || (9 <= c && c <= 13))
        return (1);
    else
        return (0);
}

int ft_atoi(const char *str)
{
    int i = 0;
    long num = 0;
    int sign = 1;
    while (str[i] && ft_isspace(str[i]))
        i++;
    if (str[i] && (str[i] == '+' || str[i] == '-'))
    {
        if (str[i] == '-')
            sign *= -1;
        i++;
    }
    while (str[i] && ('0' <= str[i] && str[i] <= '9'))
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return (sign * num);
}

// #include <stdio.h>
// int main()
// {
//     char *s = "1";
//     printf("%d", ft_atoi(s));
// }