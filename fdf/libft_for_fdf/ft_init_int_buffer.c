#include "../inc/libft_for_fdf.h"

void ft_init_int_buffer(int *buffer, int size)
{
    int i;

    i = -1;
    while (++i < size)
        buffer[i] = INT_MIN;
    return;
}