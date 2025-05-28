#include "fdf.h"

void calc_mapsize(t_env *env, double vessel[3][2]);
void adjust_offset(t_env *env);
void readjust_offset(t_env *env);

//calculate {{width_min, width_max}, {height_min, height_max}, {x_sum, y_sum}}
void calc_mapsize(t_env *env, double vessel[3][2])
{
    int r;
    int c;

    vessel[0][0] = env->map[0][0].va.x;
    vessel[0][1] = env->map[0][0].va.x;
    vessel[1][0] = env->map[0][0].va.y;
    vessel[1][1] = env->map[0][0].va.y;
    vessel[2][0] = 0;
    vessel[2][1] = 0;
    r = -1;
    while (++r < env->m_height)
    {
        c = -1;
        while (++c < env->m_width)
        {
            vessel[0][0] = ft_db_min(env->map[r][c].va.x, vessel[0][0]);
            vessel[0][1] = ft_db_max(env->map[r][c].va.x, vessel[0][1]);
            vessel[1][0] = ft_db_min(env->map[r][c].va.y, vessel[1][0]);
            vessel[1][1] = ft_db_max(env->map[r][c].va.y, vessel[1][1]);
            vessel[2][0] += env->map[r][c].va.x;
            vessel[2][1] += env->map[r][c].va.y;
        }
    }
}

void adjust_offset(t_env *env)
{
    double map_data[3][2];

    calc_mapsize(env, map_data);
    env->user_offset_x = 0;
    env->user_offset_y = 0;
    env->w_width = ceil(map_data[0][1] - map_data[0][0]);
    env->w_height = ceil(map_data[1][1] - map_data[1][0]);
    env->scaling = ft_db_min((double)W_WIDTH / env->w_width, (double)W_HEIGHT / env->w_height) * 0.4;
    env->virtual_square = ft_min(W_WIDTH, W_HEIGHT) / 2;
    env->offset_x = W_WIDTH / 2 - (map_data[2][0] * env->scaling / (env->m_height * env->m_width) );
    env->offset_y = W_HEIGHT / 2 - (map_data[2][1] * env->scaling / (env->m_height * env->m_width) );
}


void readjust_offset(t_env *env)
{
    double map_data[3][2];

    calc_mapsize(env, map_data);
    env->w_width = ceil(map_data[0][1] - map_data[0][0]);
    env->w_height = ceil(map_data[1][1] - map_data[1][0]);
    env->offset_x = W_WIDTH / 2 - (map_data[2][0] * env->scaling / (env->m_height * env->m_width) );
    env->offset_y = W_HEIGHT / 2 - (map_data[2][1] * env->scaling / (env->m_height * env->m_width) );
}
