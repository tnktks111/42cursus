#include "fdf.h"
void free_map_partial(t_env *env, int allocated);
void free_map(t_env *env);
void close_window(t_env *env);

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

void close_window(t_env *env)
{
    mlx_destroy_window(env->mlx_ptr, env->win_ptr);
    mlx_destroy_image(env->mlx_ptr, env->img);
    free_map(env);
    free(env->win_ptr);
    exit(0);
}