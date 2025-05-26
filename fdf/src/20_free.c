#include "fdf.h"
void free_map_partial(t_env *env, int allocated);
void free_map(t_env *env);
int close_window(t_env *env);

void free_map_partial(t_env *env, int allocated)
{
    int i;

    i = -1;
    while (++i < allocated)
        free(env->map[i]);
    free(env->map);
}

void free_map(t_env *env)
{
    int i;

    i = -1;
    while (++i < env->m_height)
        free(env->map[i]);
    free(env->map);
}

int close_window(t_env *env)
{
    if (env->mlx_ptr && env->img)
    {
        mlx_destroy_image(env->mlx_ptr, env->img);
        env->img = NULL;
    }
    if (env->mlx_ptr && env->menu_xpm)
    {
        mlx_destroy_image(env->mlx_ptr, env->menu_xpm);
        env->menu_xpm = NULL;
    }
    // if (env->mlx_ptr && env->win_ptr)
    // {
    //     mlx_destroy_window(env->mlx_ptr, env->win_ptr);
    //     env->win_ptr = NULL;
    // }
    free_map(env);
    if (env->mlx_ptr)
        free(env->mlx_ptr);
    exit(0);
}
