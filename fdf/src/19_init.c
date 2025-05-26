#include "fdf.h"
void init_environment(t_env *env);

void init_environment(t_env *env)
{
    env->mode = Iso;
    env->mlx_ptr = NULL;
    env->win_ptr = NULL;
    env->img = NULL;
    env->addr = NULL;
    env->menu_xpm = NULL;
}
