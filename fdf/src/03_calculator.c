#include "fdf.h"

void calc_mapsize(t_env *env);
void recalc_mapsize(t_env *env);

void calc_mapsize(t_env *env)
{
    int r;
    int c;
    double width_max_min[2];
    double height_max_min[2];
    
    width_max_min[0] = env->map[0][0].va.x;
    width_max_min[1] = env->map[0][0].va.x;
    height_max_min[0] = env->map[0][0].va.y;
    height_max_min[1] = env->map[0][0].va.y;
    r = -1;
    while (++r < env->m_height)
    {
        c = -1;
        while (++c < env->m_width)
        {
            width_max_min[0] = ft_db_max(env->map[r][c].va.x, width_max_min[0]);
            width_max_min[1] = ft_db_min(env->map[r][c].va.x, width_max_min[1]);
            height_max_min[0] = ft_db_max(env->map[r][c].va.y, height_max_min[0]);
            height_max_min[1] = ft_db_min(env->map[r][c].va.y, height_max_min[1]);
        }
    }
    env->user_offset_x = 0;
    env->user_offset_y = 0;
    env->w_width = ceil(width_max_min[0] - width_max_min[1]);
    env->w_height = ceil(height_max_min[0] - height_max_min[1]);
    env->scaling = ft_db_min((double)W_WIDTH / env->w_width, (double)W_HEIGHT / env->w_height) * 0.75;
    env->virtual_square = ft_min(W_WIDTH, W_HEIGHT) / 2;
    env->offset_x = (W_WIDTH - (env->w_width * env->scaling)) / 2;
    env->offset_y = (W_HEIGHT - (env->w_height * env->scaling)) / 2;
    env->min_x = width_max_min[1];
    env->min_y = height_max_min[1];
}

void recalc_mapsize(t_env *env)
{
    int r;
    int c;
    double width_max_min[2];
    double height_max_min[2];
    
    width_max_min[0] = env->map[0][0].va.x;
    width_max_min[1] = env->map[0][0].va.x;
    height_max_min[0] = env->map[0][0].va.y;
    height_max_min[1] = env->map[0][0].va.y;
    r = -1;
    while (++r < env->m_height)
    {
        c = -1;
        while (++c < env->m_width)
        {
            width_max_min[0] = ft_db_max(env->map[r][c].va.x, width_max_min[0]);
            width_max_min[1] = ft_db_min(env->map[r][c].va.x, width_max_min[1]);
            height_max_min[0] = ft_db_max(env->map[r][c].va.y, height_max_min[0]);
            height_max_min[1] = ft_db_min(env->map[r][c].va.y, height_max_min[1]);
        }
    }
    env->w_width = ceil(width_max_min[0] - width_max_min[1]);
    env->w_height = ceil(height_max_min[0] - height_max_min[1]);
    env->offset_x = (W_WIDTH - (env->w_width * env->scaling)) / 2;
    env->offset_y = (W_HEIGHT - (env->w_height * env->scaling)) / 2;
    env->min_x = width_max_min[1];
    env->min_y = height_max_min[1];
}
