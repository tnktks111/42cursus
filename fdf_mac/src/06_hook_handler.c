#include "fdf.h"

void hook_handler(t_env *env);
int key_button_press(int key, void *param_env);
int handle_button_press(int button, int x, int y, void *param_env);
int handle_mouse_motion(int x, int y, void *param_env);
int handle_button_release(int button, int x, int y, void *param_env);

void hook_handler(t_env *env)
{
    mlx_key_hook(env->win_ptr, key_button_press, env);
    mlx_hook(env->win_ptr, 4, 0, handle_button_press, env);
    mlx_hook(env->win_ptr, 5, 0, handle_button_release, env);
    mlx_hook(env->win_ptr, 6, 0, handle_mouse_motion, env);
    mlx_hook(env->win_ptr, 17, 0, close_window, env);
}

int key_button_press(int key, void *param_env)
{
    t_env *env;

    env = (t_env *)param_env;
    if (env->start == True && key == ENTER)
    {
        env->start = False;
        line_drawer(env);
    }
    if (key == ESCAPE)
        close_window(env);
    if (env->start == False)
    {
        if (key == K_W || key == K_A || key == K_S || key == K_D)
            translate_view(key, env);
        if (key == K_R)
            reset_view(env);
        if (key == TAB)
            switch_menu_frag(env);
        if (key == SPACE)
            switch_view(env);
    }
    return (0);
}

int handle_button_press(int button, int x, int y, void *param_env)
{
    t_env *env;
    int curr_mouse_x;
    int curr_mouse_y;

    env = (t_env *)param_env;
    if (env->start == True)
        return (0);
    if (button == MOUSE_CLICK_LEFT)
    {
        env->is_dragging = True;
        curr_mouse_x = x;
        curr_mouse_y = y;
        env->v_start = map_mouse_to_sphere(curr_mouse_x, curr_mouse_y, env);
    }
    if (button == MOUSE_SCROLL_DOWN)
    {
        env->scaling /= 1.1;
        redraw_line_after_zoom(env);
    }
    if (button == MOUSE_SCROLL_UP)
    {
        env->scaling *= 1.1;
        redraw_line_after_zoom(env);
    }
    return (0);
}

int handle_mouse_motion(int x, int y, void *param_env)
{
    t_env *env = (t_env *)param_env;
    int curr_mouse_x;
    int curr_mouse_y;
    t_quaternion rot;
    t_quaternion axis;
    double angle;

    if (env->start == True)
        return (0);
    if (env->is_dragging == True)
    {
        curr_mouse_x = x;
        curr_mouse_y = y;

        env->v_curr = map_mouse_to_sphere(curr_mouse_x, curr_mouse_y, env);
        axis = vector_cross_product(env->v_curr, env->v_start);
        angle = acos(vector_inner_product(env->v_start, env->v_curr));
        rot = gen_rot_quaternion(axis, angle);
        redraw_line_after_rotation(rot, env);
        env->v_start = env->v_curr;
    }
    return (0);
}

int handle_button_release(int button, int x, int y, void *param_env)
{
    t_env *env;

    (void)x;
    (void)y;
    env = (t_env *)param_env;
    if (env->start == True)
        return (0);
    if (button == MOUSE_CLICK_LEFT)
        env->is_dragging = 0;
    return (0);
}