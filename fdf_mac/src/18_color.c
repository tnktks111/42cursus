#include "../inc/fdf.h"

int	create_rgb(int r, int g, int b);
int	get_r(int rgb);
int	get_g(int rgb);
int	get_b(int rgb);


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
