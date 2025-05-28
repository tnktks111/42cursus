#include "fdf.h"
void switch_menu_frag(t_env *env);

void switch_menu_frag(t_env *env)
{
    env->display_menu = !(env->display_menu);
    redraw_line_after_tab(env);
}
