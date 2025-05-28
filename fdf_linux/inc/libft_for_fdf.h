#ifndef LIBFT_FOR_FDF_H
# define LIBFT_FOR_FDF_H

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>

int ft_atoi_for_color(const char *str);
long	ft_atoi_for_fdf(const char *str);

void	ft_bzero(void *s, size_t n);
void ft_init_int_buffer(int *buffer, int size);

double ft_db_max(double x, double y);
double ft_db_min(double x, double y);
double ft_db_abs(double x);
void   ft_db_swap(double *x, double *y);
int ipart(double x);
double fpart(double x);
double rfpart(double x);

int ft_max(int x, int y);
int ft_min(int x, int y);
int ft_abs(int x);
void   ft_swap(int *x, int *y);
void ft_uint_swap(uint32_t *x, uint32_t *y);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);

char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *s);

#endif