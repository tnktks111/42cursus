#include "fdf.h"

t_quaternion map_mouse_to_sphere(int x, int y, t_env *env);
t_quaternion vector_cross_product(t_quaternion p, t_quaternion q);
double vector_inner_product(t_quaternion p, t_quaternion q);

t_quaternion map_mouse_to_sphere(int x, int y, t_env *env)
{
    t_quaternion res;
    double r_xy_sq;

    res.w = 0;
    res.x = (x - W_WIDTH / 2) / env->virtual_square;
    res.y = (y - W_HEIGHT / 2) / env->virtual_square;
    r_xy_sq = res.x * res.x + res.y * res.y;
    if (r_xy_sq <= 1)
        res.z = -sqrt(1 - (res.x * res.x + res.y * res.y));
    else
        res.z = 0;
    return (normalize_quaternion(res));
}

t_quaternion vector_cross_product(t_quaternion p, t_quaternion q)
{
    t_quaternion r;

    r.w = 0;
    r.x = p.y * q.z - q.y * p.z;
    r.y = p.z * q.x - q.z * p.x;
    r.z = p.x * q.y - q.x * p.y;
    return (r);
}

double vector_inner_product(t_quaternion p, t_quaternion q)
{
    double inner_product;

    inner_product = p.x * q.x + p.y * q.y + p.z * q.z;
    if (inner_product > 1)
        return (1);
    if (inner_product < -1)
        return (-1);
    return (inner_product);
}
