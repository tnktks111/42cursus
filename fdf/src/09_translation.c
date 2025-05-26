#include "fdf.h"

int translate_view(int key, t_env *env);

int translate_view(int key, t_env *env)
{
    if (key == K_W)
        env->user_offset_y += 10;
    if (key == K_S)
        env->user_offset_y -= 10;
    if (key == K_A)
        env->user_offset_x += 10;
    if (key == K_D)
        env->user_offset_x -= 10;
    redraw_line_after_translation(env);
    return (0);
}
