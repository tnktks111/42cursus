#include "../inc/libft_for_fdf.h"

double ft_db_max(double x, double y);
double ft_db_min(double x, double y);
double ft_db_abs(double x);
void   ft_db_swap(double *x, double *y);
int ipart(double x);
double fpart(double x);
double rfpart(double x);

double ft_db_max(double x, double y)
{
    if (x > y)
        return (x);
    else
        return (y);
}

double ft_db_min(double x, double y)
{
    if (x < y)
        return (x);
    else
        return (y);
}

double ft_db_abs(double x)
{
    if (x < 0)
        x *= -1;
    return (x);
}

void ft_db_swap(double *x, double *y)
{
    double tmp;

    tmp = *x;
    *x = *y;
    *y = tmp;
}

int ipart(double x)
{
    return floor(x);
}

double fpart(double x)
{
    return (x - ipart(x));
}

double rfpart(double x)
{
    return (1 - fpart(x));
}