#include "../inc/fdf.h"

int	create_rgb(int r, int g, int b);
int	get_r(int rgb);
int	get_g(int rgb);
int	get_b(int rgb);
int add_shade(int rgb, double shade_factor);
int get_opposite(int rgb);
int interpolate_color(int c_start, int c_end, double t);

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	get_r(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	get_g(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	get_b(int rgb)
{
	return (rgb & 0xFF);
}

int add_shade(int rgb, double shade_factor)
{
    int r;
    int g;
    int b;

    r = ft_max((int)(get_r(rgb) * shade_factor), 0);
    g = ft_max((int)(get_g(rgb) * shade_factor), 0);
    b = ft_max((int)(get_b(rgb) * shade_factor), 0);
    r = ft_min(r, 255);
    g = ft_min(g, 255);
    b = ft_min(b, 255);
    return (r << 16 | g << 8 | b);
}

int get_opposite(int rgb)
{
    int r;
    int g;
    int b;

    r = 255 - get_r(rgb);
    g = 255 - get_g(rgb);
    b = 255 - get_b(rgb);
    return (r << 16 | g << 8 | b);
}

int interpolate_color(int c_start, int c_end, double t)
{
    int r_interp;
    int g_interp;
    int b_interp;

    r_interp = round((1.0 - t) * get_r(c_start) + t * get_r(c_end));
    g_interp = round((1.0 - t) * get_g(c_start) + t * get_g(c_end));
    b_interp = round((1.0 - t) * get_b(c_start) + t * get_b(c_end));
    r_interp = ft_max(r_interp, 0);
    g_interp = ft_max(g_interp, 0);
    b_interp = ft_max(b_interp, 0);
    r_interp = ft_min(r_interp, 255);
    g_interp = ft_min(g_interp, 255);
    b_interp = ft_min(b_interp, 255);
    return ((r_interp << 16) | (g_interp << 8) | (b_interp));
}
