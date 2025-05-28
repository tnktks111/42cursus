#include "fdf.h"
void switch_view(t_env *env)
{
    env->mode = (env->mode + 1) % 4;
    reset_view(env);
}
