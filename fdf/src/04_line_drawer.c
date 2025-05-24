#include "fdf.h"

void plot(t_env *env, int x, int y, int z, int rgb, double brightness);
void xiaolin_wu(t_env *env, t_mappoint p0, t_mappoint p1);
void line_drawer(t_env *env);
void vertical_line_drawer(t_env *env);
void horizontal_line_drawer(t_env *env);

void plot(t_env *env, int x, int y, int z, int rgb, double brightness)
{
    char *dst;
    int idx;

    if (x < 0 || x >= W_WIDTH || y < 0 || y >= W_HEIGHT)
        return;
    idx = y * W_WIDTH + x;
    if (z > env->elevation_map[idx])
    {
        dst = env->addr + (y * env->line_length + x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = add_shade(rgb, brightness);
        env->elevation_map[idx] = z;
    }
}

void xiaolin_wu(t_env *env, t_mappoint p0, t_mappoint p1)
{
    t_bool steep;
    double dx;
    double dy;
    double grad;
    int x_end;
    int y_end;
    double x_gap;
    int x_pxl1;
    int y_pxl1;
    int x_pxl2;
    int y_pxl2;
    double intery;
    int x;
    int intery_color;
    double t;
    int z;

    z = (int)ft_db_min(p0.va.z, p1.va.z);
    steep = (ft_db_abs(p1.va.y - p0.va.y) > ft_db_abs(p1.va.x - p0.va.x));
    if (steep)
    {
        ft_db_swap(&p0.va.x, &p0.va.y);
        ft_db_swap(&p1.va.x, &p1.va.y);
    }
    if (p0.va.x > p1.va.x)
    {
        ft_db_swap(&p0.va.x, &p1.va.x);
        ft_db_swap(&p0.va.y, &p1.va.y);
        ft_db_swap(&p0.va.z, &p1.va.z);
        ft_uint_swap(&p0.color, &p1.color);
    }
    dx = p1.va.x - p0.va.x;
    dy = p1.va.y - p0.va.y;
    if (dx == 0)
        grad = 1;
    else
        grad = dy / dx;
    x_end = round(p0.va.x);
    y_end = p0.va.y + grad * (x_end - p0.va.x);
    x_gap = rfpart(p0.va.x + 0.5);
    x_pxl1 = x_end;
    y_pxl1 = ipart(y_end);
    if (steep)
    {
        plot(env, y_pxl1, x_pxl1, z, p0.color, rfpart(y_end) * x_gap);
        plot(env, y_pxl1 + 1, x_pxl1, z, p0.color, fpart(y_end) * x_gap);
    }
    else
    {
        plot(env, x_pxl1, y_pxl1, z, p0.color, rfpart(y_end) * x_gap);
        plot(env, x_pxl1, y_pxl1 + 1, z, p0.color, fpart(y_end) * x_gap);
    }
    intery = y_end + grad;
    x_end = round(p1.va.x);
    y_end = p1.va.y + grad * (x_end - p1.va.x);
    x_gap = fpart(p1.va.x + 0.5);
    x_pxl2 = x_end;
    y_pxl2 = ipart(y_end);
    if (steep)
    {
        plot(env, y_pxl2, x_pxl2, z, p1.color, rfpart(y_end) * x_gap);
        plot(env, y_pxl2 + 1, x_pxl2, z, p1.color, fpart(y_end) * x_gap);
    }
    else
    {
        plot(env, x_pxl2, y_pxl2, z, p1.color, rfpart(y_end) * x_gap);
        plot(env, x_pxl2, y_pxl2 + 1, z, p1.color, fpart(y_end) * x_gap);
    }
    x = x_pxl1;
    t = 0.5;
    while (++x < x_pxl2)
    {
        if (dx != 0)
            t = (x - p0.va.x) / dx;
        intery_color = interpolate_color(p0.color, p1.color, t);
        if (steep)
        {
            plot(env, ipart(intery), x, z, intery_color, rfpart(intery));
            plot(env, ipart(intery)+1, x, z, intery_color, fpart(intery));
        }
        else
        {
            plot(env, x, ipart(intery), z, intery_color, rfpart(intery));
            plot(env, x, ipart(intery)+1, z, intery_color, fpart(intery));
        }
        intery = intery + grad;
    }
}

void line_drawer(t_env *env)
{
    ft_bzero(env->addr, W_HEIGHT * env->line_length);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
}

void vertical_line_drawer(t_env *env)
{
    int r;
    int c;
    t_mappoint p0_screen;
    t_mappoint p1_screen;

    c = -1;
    while (++c < env->m_width)
    {
        r = -1;
        while (++r < env->m_height - 1)
        {
            p0_screen = env->map[r][c];
            p1_screen = env->map[r + 1][c];
            p0_screen.va.x = (env->map[r][c].va.x - env->min_x) * env->scaling + env->offset_x + env->user_offset_x;
            p0_screen.va.y = (env->map[r][c].va.y - env->min_y) * env->scaling + env->offset_y + env->user_offset_y;
            p1_screen.va.x = (env->map[r + 1][c].va.x - env->min_x) * env->scaling + env->offset_x + env->user_offset_x;
            p1_screen.va.y = (env->map[r + 1][c].va.y - env->min_y) * env->scaling + env->offset_y + env->user_offset_y;
            xiaolin_wu(env, p0_screen, p1_screen);
        }
    }
}

void horizontal_line_drawer(t_env *env)
{
    int r;
    int c;
    t_mappoint p0_screen;
    t_mappoint p1_screen;

    r = -1;
    while (++r < env->m_height)
    {
        c = -1;
        while (++c < env->m_width - 1)
        {
            p0_screen = env->map[r][c];
            p1_screen = env->map[r][c + 1];
            p0_screen.va.x = (env->map[r][c].va.x - env->min_x) * env->scaling + env->offset_x + env->user_offset_x;
            p0_screen.va.y = (env->map[r][c].va.y - env->min_y) * env->scaling + env->offset_y + env->user_offset_y;
            p1_screen.va.x = (env->map[r][c + 1].va.x - env->min_x) * env->scaling + env->offset_x + env->user_offset_x;
            p1_screen.va.y = (env->map[r][c + 1].va.y - env->min_y) * env->scaling + env->offset_y + env->user_offset_y;
            xiaolin_wu(env, p0_screen, p1_screen);
        }
    }
}
