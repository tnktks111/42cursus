#include "fdf.h"

t_quaternion normalize_quaternion(t_quaternion q);
t_quaternion gen_rot_quaternion(t_quaternion axis, double angle);
void update_rot_quaternion(t_quaternion rot, t_env *env);
void rot_based_on_quaternion(t_quaternion p, t_quaternion *p_prime, t_env *env);

t_quaternion normalize_quaternion(t_quaternion q)
{
    double norm;
    t_quaternion normalized_q;

    norm = norm_of_quaternion(q);
    if (norm > 0.000001)
    {
        normalized_q.w = q.w / norm;
        normalized_q.x = q.x / norm;
        normalized_q.y = q.y / norm;
        normalized_q.z = q.z / norm;
    }
    else
    {
        normalized_q.w = 1;
        normalized_q.x = 0;
        normalized_q.y = 0;
        normalized_q.z = 0;
    }
    return (normalized_q);
}

t_quaternion gen_rot_quaternion(t_quaternion axis, double angle)
{
    t_quaternion rot;
    t_quaternion normalized_rot;
    t_quaternion normarized_axis;
    double alpha;
    double sin_alpha;

    alpha = angle / 2;
    sin_alpha = sin(alpha);
    normarized_axis = normalize_quaternion(axis);
    rot.w = cos(alpha);
    rot.x = normarized_axis.x * sin_alpha;
    rot.y = normarized_axis.y * sin_alpha;
    rot.z = normarized_axis.z * sin_alpha;
    normalized_rot = normalize_quaternion(rot);
    return (normalized_rot);
}

void update_rot_quaternion(t_quaternion rot, t_env *env)
{
    t_quaternion prev_rot;

    prev_rot = env->rot;
    env->rot = normalize_quaternion(quaternion_product(rot, prev_rot));
}

void rot_based_on_quaternion(t_quaternion p, t_quaternion *p_prime, t_env *env)
{
    t_quaternion q_total_rotation_conj;
    t_quaternion tmp_prod;

    q_total_rotation_conj = quaternion_conjugate(env->rot);
    tmp_prod = quaternion_product(env->rot, p);
    *p_prime = quaternion_product(tmp_prod, q_total_rotation_conj);
}
