#include "fdf.h"

void redraw_line_after_rotation(t_quaternion rot, t_env *env);
void redraw_line_after_translation(t_env *env);
void redraw_line_after_zoom(t_env *env);
void reset_view(t_env *env);

void redraw_line_after_rotation(t_quaternion rot, t_env *env)
{
    int i;
    int j;

    i = -1;

    update_rot_quaternion(rot, env);
    while (++i < env->m_height)
    {
        j = -1;
        while (++j < env->m_width)
            rot_based_on_quaternion(env->map[i][j].a, &env->map[i][j].va, env);
    }
    recalc_mapsize(env);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    ft_bzero(env->addr, W_HEIGHT * env->line_length);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    mlx_do_sync(env->mlx_ptr);
}

void redraw_line_after_translation(t_env *env)
{
    ft_bzero(env->addr, W_HEIGHT * env->line_length);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    mlx_do_sync(env->mlx_ptr);
}

void redraw_line_after_zoom(t_env *env)
{
    recalc_mapsize(env);
    ft_bzero(env->addr, W_HEIGHT * env->line_length);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    mlx_do_sync(env->mlx_ptr);
}

void reset_view(t_env *env)
{
    int i;
    int j;

    i = -1;
    while (++i < env->m_height)
    {
        j = -1;
        while (++j < env->m_width)
            env->map[i][j].va = rot_isometric(env->map[i][j].a, env);
    }
    ft_bzero(env->addr, W_HEIGHT * env->line_length);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    calc_mapsize(env);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    mlx_do_sync(env->mlx_ptr);
}