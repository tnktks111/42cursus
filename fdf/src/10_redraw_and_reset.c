#include "fdf.h"

void redraw_line_after_rotation(t_quaternion rot, t_env *env);
void redraw_line_after_translation(t_env *env);
void redraw_line_after_tab(t_env *env);
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
    readjust_offset(env);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    fill_background(env, BACKGROUND);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    if (env->display_menu == True)
        mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->menu_xpm, 10, 10);
    mlx_do_sync(env->mlx_ptr);
}

void redraw_line_after_translation(t_env *env)
{
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    fill_background(env, BACKGROUND);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    if (env->display_menu == True)
        mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->menu_xpm, 10, 10);
    mlx_do_sync(env->mlx_ptr);
}

void redraw_line_after_tab(t_env *env)
{
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    fill_background(env, BACKGROUND);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    if (env->display_menu == True)
        mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->menu_xpm, 10, 10);
    mlx_do_sync(env->mlx_ptr);
}

void redraw_line_after_zoom(t_env *env)
{
    readjust_offset(env);
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    fill_background(env, BACKGROUND);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    if (env->display_menu == True)
        mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->menu_xpm, 10, 10);
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
            env->map[i][j].va = rot_based_on_view_mode(env->map[i][j].a, env);
    }
    ft_init_int_buffer(env->elevation_map, W_WIDTH * W_HEIGHT);
    fill_background(env, BACKGROUND);
    adjust_offset(env);
    vertical_line_drawer(env);
    horizontal_line_drawer(env);
    mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->img, 0, 0);
    if (env->display_menu == True)
        mlx_put_image_to_window(env->mlx_ptr, env->win_ptr, env->menu_xpm, 10, 10);
    mlx_do_sync(env->mlx_ptr);
}
