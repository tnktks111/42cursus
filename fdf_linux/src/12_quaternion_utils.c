/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_quaternion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttanaka <ttanaka@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 17:27:40 by ttanaka           #+#    #+#             */
/*   Updated: 2025/05/28 18:44:26 by ttanaka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

t_quaternion	set_quaternion(double w, double x, double y, double z);
double			norm_of_quaternion(t_quaternion q);
t_quaternion	quaternion_conjugate(t_quaternion q);
t_quaternion	quaternion_product(t_quaternion q, t_quaternion p);
void			quaternion_product_in_place(t_quaternion *p, t_quaternion rot);

t_quaternion	set_quaternion(double w, double x, double y, double z)
{
	t_quaternion	res;

	res.w = w;
	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

double	norm_of_quaternion(t_quaternion q)
{
	return (sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}

t_quaternion	quaternion_conjugate(t_quaternion q)
{
	t_quaternion	conj;

	conj.w = q.w;
	conj.x = -q.x;
	conj.y = -q.y;
	conj.z = -q.z;
	return (conj);
}

t_quaternion	quaternion_product(t_quaternion q, t_quaternion p)
{
	t_quaternion	result;

	result.w = q.w * p.w - q.x * p.x - q.y * p.y - q.z * p.z;
	result.x = q.w * p.x + q.x * p.w + q.y * p.z - q.z * p.y;
	result.y = q.w * p.y - q.x * p.z + q.y * p.w + q.z * p.x;
	result.z = q.w * p.z + q.x * p.y - q.y * p.x + q.z * p.w;
	return (result);
}

void	quaternion_product_in_place(t_quaternion *p, t_quaternion rot)
{
	t_quaternion	rot_conj;
	t_quaternion	tmp;

	rot_conj = quaternion_conjugate(rot);
	tmp = quaternion_product(rot, *p);
	*p = quaternion_product(tmp, rot_conj);
}
