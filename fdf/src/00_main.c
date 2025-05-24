#include "../inc/fdf.h"

void mlx_handler(t_env *env);

int main(int argc, char *argv[])
{
    t_env env;

    if (parser(argc, argv[1], &env) == EXIT_FAILURE)
        return (1);
    mlx_handler(&env);
    return (0);
}

void mlx_handler(t_env *env)
{
    env->mlx_ptr = mlx_init();
    if (!env->mlx_ptr)
    {
        printf("Error: mlx_init() failed!\n");
        return;
    }
    env->win_ptr = mlx_new_window(env->mlx_ptr, W_WIDTH, W_HEIGHT, "fdf");
    if (!env->win_ptr)
    {
        printf("Error: mlx_new_window() failed!\n");
        return;
    }
    env->img = mlx_new_image(env->mlx_ptr, W_WIDTH, W_HEIGHT);
    if (!env->img)
    {
        printf("Error: mlx_new_image() failed!\n");
        return;
    }
    env->addr = mlx_get_data_addr(env->img, &env->bits_per_pixel, &env->line_length, &env->endian);
    env->elevation_map = (int *)malloc(sizeof(int) * W_WIDTH * W_HEIGHT);
    if (!env->elevation_map)
        return ;
    hook_handler(env);
    line_drawer(env);
    mlx_loop(env->mlx_ptr);
};
