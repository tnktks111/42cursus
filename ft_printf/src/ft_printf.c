#include "ft_printf.h"
#include "libft.h"

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
            if (!((format++)))
                return (-1);
            else if (*format == 's' || *format == 'p' || *format == 'c' || *format == 'd' || *format == 'i' || *format == 'u' || *format == 'x' || *format == 'X')
            {
                if (*format == 's' || *format == 'p')
                    add = f_ptr_parser(*format, va_arg(args, void*));
                else
                    add = f_int_parser(*format, va_arg(args, int));
                if (add == -1)
                    return (-1);
                cnt += add;
            }
            else if (*format == '%')
            {
                if (ft_putchar('%') == -1)
                    return (-1);
                cnt++;
            }
            else
                return (-1);
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
//     int a = ft_printf("%p\n", "");
//     int b = printf("%p\n", "");
//     printf("%d\n%d", a, b);
// }