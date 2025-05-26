#include "fdf.h"

void plot(t_env *env, t_point p, double brightness, t_bool reversed);
t_point gen_point(int x, int y, int z, int color);
void plot_edge(t_env *env, t_draw_var *info, t_mappoint p, t_bool is_start);
void plot_loop(t_env *env, t_draw_var *info);
void xiaolin_wu(t_env *env, t_mappoint p0, t_mappoint p1, t_bool reversed);
void line_drawer(t_env *env);
void vertical_line_drawer(t_env *env);
void horizontal_line_drawer(t_env *env);

void plot(t_env *env, t_point p, double brightness, t_bool reversed)
{
    char *dst;
    int idx;

    if (reversed)
        ft_swap(&p.x, &p.y);
    if (p.x < 0 || p.x >= W_WIDTH || p.y < 0 || p.y >= W_HEIGHT)
        return;
    idx = p.y * W_WIDTH + p.x;
    if (p.z > env->elevation_map[idx])
    {
        dst = env->addr + (p.y * env->line_length + p.x * (env->bits_per_pixel / 8));
        *(unsigned int*)dst = add_shade(p.color, brightness);
        env->elevation_map[idx] = p.z;
    }
}

t_point gen_point(int x, int y, int z, int color)
{
    t_point res;

    res.x = x;
    res.y = y;
    res.z = z;
    res.color = color;
    return (res);
}

void plot_edge(t_env *env, t_draw_var *info, t_mappoint p, t_bool is_start)
{
    int x_end;
    double y_end;
    double x_gap;

    x_end = round(p.va.x);
    y_end = p.va.y + info->grad * (x_end - p.va.x);
    if (is_start)
    {
        x_gap = rfpart(p.va.x + 0.5);
        info->x_pxl1 = x_end;
        info->y_pxl1 = ipart(y_end);
        plot(env, gen_point(info->x_pxl1, info->y_pxl1, p.va.z, p.color), rfpart(y_end) * x_gap, info->reversed);
        plot(env, gen_point(info->x_pxl1, info->y_pxl1 + 1, p.va.z, p.color), fpart(y_end) * x_gap, info->reversed);
        info->intery = y_end + info->grad;
    }
    else
    {
        x_gap = fpart(p.va.x + 0.5);
        info->x_pxl2 = x_end;
        info->y_pxl2 = ipart(y_end);
        plot(env, gen_point(info->x_pxl2, info->y_pxl2, p.va.z, p.color) ,rfpart(y_end) * x_gap, info->reversed);
        plot(env, gen_point(info->x_pxl2, info->y_pxl2 + 1, p.va.z, p.color), fpart(y_end) * x_gap, info->reversed);
    }
}

void plot_loop(t_env *env, t_draw_var *info)
{
    int x;
    double t;
    int intery_height;
    int intery_color;

    x = info->x_pxl1;
    t = 0.5;
    while (++x < info->x_pxl2)
    {
        if (info->dx != 0)
            t = (x - info->start.va.x) / info->dx;
        intery_color = interpolate_color(info->start.color, info->end.color, t);
        intery_height = round((1 - t) * info->start.va.z + t * info->end.va.z);
        plot(env, gen_point(x, ipart(info->intery), intery_height, intery_color), rfpart(info->intery), info->reversed);
        plot(env, gen_point(x, ipart(info->intery) + 1, intery_height, intery_color), fpart(info->intery), info->reversed);
        info->intery = info->intery + info->grad;
    }
}

void xiaolin_wu(t_env *env, t_mappoint p0, t_mappoint p1, t_bool reversed)
{
    t_draw_var info;

    info.reversed = reversed;
    info.start = p0;
    info.end = p1;
    if (ft_db_abs(p1.va.y - p0.va.y) > ft_db_abs(p1.va.x - p0.va.x))
    {
        ft_db_swap(&p0.va.x, &p0.va.y);
        ft_db_swap(&p1.va.x, &p1.va.y);
        return (xiaolin_wu(env, p0, p1, True));
    }
    if (p0.va.x > p1.va.x)
        return (xiaolin_wu(env, p1, p0, reversed));
    info.dx = p1.va.x - p0.va.x;
    info.dy = p1.va.y - p0.va.y;
    if (info.dx == 0)
        info.grad = 1;
    else
        info.grad = info.dy / info.dx;
    plot_edge(env, &info, p0, True);
    plot_edge(env, &info, p1, False);
    plot_loop(env, &info);
}

void line_drawer(t_env *env)
{
    ft_bzero(env->addr, W_HEIGHT * env->line_length);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    env->menu_xpm = mlx_xpm_file_to_image(env->mlx_ptr, XPM_FILE_PATH, &env->menu_img_width, &env->menu_img_height);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    env->display_menu = True;
    if (env->display_menu == True)
        mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->menu_xpm, 0, 0);
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
            p0_screen.va.x = env->map[r][c].va.x * env->scaling + env->offset_x + env->user_offset_x;
            p0_screen.va.y = env->map[r][c].va.y * env->scaling + env->offset_y + env->user_offset_y;
            p1_screen.va.x = env->map[r + 1][c].va.x * env->scaling + env->offset_x + env->user_offset_x;
            p1_screen.va.y = env->map[r + 1][c].va.y * env->scaling + env->offset_y + env->user_offset_y;
            xiaolin_wu(env, p0_screen, p1_screen, False);
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
            p0_screen.va.x = env->map[r][c].va.x * env->scaling + env->offset_x + env->user_offset_x;
            p0_screen.va.y = env->map[r][c].va.y * env->scaling + env->offset_y + env->user_offset_y;
            p1_screen.va.x = env->map[r][c + 1].va.x * env->scaling + env->offset_x + env->user_offset_x;
            p1_screen.va.y = env->map[r][c + 1].va.y * env->scaling + env->offset_y + env->user_offset_y;
            xiaolin_wu(env, p0_screen, p1_screen, False);
        }
    }
}
