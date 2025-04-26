#include "libft.h"

void ft_putnbr_fd(int n, int fd)
{
    char c;
    if (n == -2147483648)
        ft_putstr_fd("-2147483648", fd);
    else
    {
        if (n < 0)
        {
            ft_putchar_fd('-', fd);
            n *= -1;
        }
        if (n >= 10)
            ft_putnbr_fd(n / 10, fd);
        c = '0' + n % 10;
        ft_putchar_fd(c, fd);
    }
}

// int main()
// {
//     int n = -12345;
//     ft_putnbr_fd(n, 0);
// }