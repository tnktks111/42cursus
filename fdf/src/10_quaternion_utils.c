#include "fdf.h"

t_quaternion set_quaternion(double w, double x, double y, double z);
double norm_of_quaternion(t_quaternion q);
t_quaternion quaternion_conjugate(t_quaternion q);
t_quaternion quaternion_product(t_quaternion q, t_quaternion p);
void quaternion_product_in_place(t_quaternion *p, t_quaternion rot);
t_quaternion rot_isometric(t_quaternion p, t_env *env);

t_quaternion set_quaternion(double w, double x, double y, double z)
{
    t_quaternion res;

    res.w = w;
    res.x = x;
    res.y = y;
    res.z = z;
    return (res);
}
// t_quaternion gen_rot_quaternion(double angle)

double norm_of_quaternion(t_quaternion q)
{
    return (sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}



t_quaternion quaternion_conjugate(t_quaternion q)
{
    t_quaternion conj;
    conj.w = q.w;
    conj.x = -q.x;
    conj.y = -q.y;
    conj.z = -q.z;
    return conj;
}

t_quaternion quaternion_product(t_quaternion q, t_quaternion p)
{
    t_quaternion result;
    result.w = q.w*p.w - q.x*p.x - q.y*p.y - q.z*p.z;
    result.x = q.w*p.x + q.x*p.w + q.y*p.z - q.z*p.y;
    result.y = q.w*p.y - q.x*p.z + q.y*p.w + q.z*p.x;
    result.z = q.w*p.z + q.x*p.y - q.y*p.x + q.z*p.w;
    return (result);
}

void quaternion_product_in_place(t_quaternion *p, t_quaternion rot)
{
    t_quaternion rot_conj;
    t_quaternion tmp;
    
    rot_conj = quaternion_conjugate(rot);
    tmp = quaternion_product(rot, *p);
    *p = quaternion_product(tmp, rot_conj);
}

/*
sin(45°/2) = 0.382683
cos(45°/2) = 0.923879
arctan(1/√2) = 0.615479
cos(arctan(1/√2)/2) = 0.95302061382
sin(arctan(1/√2)/2) = 0.30290544668
*/
t_quaternion rot_isometric(t_quaternion p, t_env *env)
{
    static t_quaternion q_rot_z_45 = {0.923879, 0, 0, 0.382683};
    static t_quaternion q_rot_x_35 = {0.953020, 0.302905, 0, 0};

    t_quaternion q_total_rotation_conj;
    t_quaternion tmp_prod;

    env->rot = quaternion_product(q_rot_x_35, q_rot_z_45);
    q_total_rotation_conj = quaternion_conjugate(env->rot);
    tmp_prod = quaternion_product(env->rot, p);
    return (quaternion_product(tmp_prod, q_total_rotation_conj));
}
