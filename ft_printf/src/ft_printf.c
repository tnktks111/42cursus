#include "../inc/ft_printf.h"

int format_parser(va_list args, char format)
{
    int cnt;

    cnt = 0;
    if (format == '\0')
        return (-1);
    else if (format == 's' || format == 'p')
        cnt += f_ptr_parser(format, va_arg(args, void*));
    else if (format == 'c' || format == 'd' || format == 'i' || format == 'u' || format == 'x' || format == 'X')
        cnt += f_int_parser(format, va_arg(args, int));
    else if (format == '%')
    {
        if (ft_putchar('%') == -1)
            return (-1);
        cnt++;
    }
    else
        return (-1);
    if (cnt == -1)
        return (-1);
    return (cnt);
}

int ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int cnt;
    int add;

    cnt = 0;
    while(*format)
    {
        if (*format == '%')
        {
            add = format_parser(args, *(++format));
            if (add == -1)
                return (-1);
            cnt += add;
            format++;
        }
        else
        {
            if (ft_putchar(*format++) == -1)
                return (-1);
            cnt++;
        }
    }
    va_end(args);
    return (cnt);
}

// //cw -I ./inc -I ./libft src/*.c libft/libft.a 
// #include <stdio.h>
// int main()
// {
//     int a = ft_printf(" %c ", '0');
//     int b = printf(" %c ", '0');
//     printf("%d\n%d", a, b);
// }