#include "fdf.h"

int translate_view(int key, t_env *env);

int translate_view(int key, t_env *env)
{
    if (key == UP_ARROW)
        env->user_offset_y += 10;
    if (key == DOWN_ARROW)
        env->user_offset_y -= 10;
    if (key == LEFT_ARROW)
        env->user_offset_x += 10;
    if (key == RIGHT_ARROW)
        env->user_offset_x -= 10;
    redraw_line_after_translation(env);
    return (0);
}