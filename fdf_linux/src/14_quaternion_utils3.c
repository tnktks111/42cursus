/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_quaternion_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:57:06 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 17:58:06 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_quaternion	rot_isometric(t_quaternion p, t_env *env);
t_quaternion	rot_yz(t_quaternion p, t_env *env);
t_quaternion	rot_zx(t_quaternion p, t_env *env);
t_quaternion	rot_based_on_view_mode(t_quaternion p, t_env *env);

/*
sin(45°/2) = 0.382683
cos(45°/2) = 0.923879
arctan(1/√2) = 0.615479
cos(arctan(1/√2)/2) = 0.95302061382
sin(arctan(1/√2)/2) = 0.30290544668
*/
t_quaternion	rot_isometric(t_quaternion p, t_env *env)
{
	static t_quaternion	q_rot_z_45 = {0.923879, 0, 0, 0.382683};
	static t_quaternion	q_rot_x_35 = {0.953020, 0.302905, 0, 0};
	t_quaternion		q_total_rotation_conj;
	t_quaternion		tmp_prod;

	env->rot = quaternion_product(q_rot_x_35, q_rot_z_45);
	q_total_rotation_conj = quaternion_conjugate(env->rot);
	tmp_prod = quaternion_product(env->rot, p);
	return (quaternion_product(tmp_prod, q_total_rotation_conj));
}

/*
sin 45° = cos 45° = 0.70710678118
*/

t_quaternion	rot_yz(t_quaternion p, t_env *env)
{
	static t_quaternion	q_rot_y_90 = {0.707106, 0, 0.707106, 0};
	static t_quaternion	q_rot_z_90 = {0.707106, 0, 0, -0.707106};
	t_quaternion		q_total_rotation_conj;
	t_quaternion		tmp_prod;

	env->rot = quaternion_product(q_rot_z_90, q_rot_y_90);
	q_total_rotation_conj = quaternion_conjugate(env->rot);
	tmp_prod = quaternion_product(env->rot, p);
	return (quaternion_product(tmp_prod, q_total_rotation_conj));
}

t_quaternion	rot_zx(t_quaternion p, t_env *env)
{
	static t_quaternion	q_rot_x_90 = {0.707106, 0.707106, 0, 0};
	static t_quaternion	q_rot_x_90_conj = {0.707106, -0.707106, 0, 0};
	t_quaternion		tmp_prod;

	env->rot = q_rot_x_90;
	tmp_prod = quaternion_product(env->rot, p);
	return (quaternion_product(tmp_prod, q_rot_x_90_conj));
}

t_quaternion	rot_based_on_view_mode(t_quaternion p, t_env *env)
{
	if (env->mode == Iso)
		return (rot_isometric(p, env));
	if (env->mode == YZ)
		return (rot_yz(p, env));
	if (env->mode == ZX)
		return (rot_zx(p, env));
	else
	{
		env->rot = set_quaternion(0, 0, 0, 0);
		return (p);
	}
}
