/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myvector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:20:47 by soekim            #+#    #+#             */
/*   Updated: 2021/03/04 21:31:35 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

void			initvec(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vec		multi(t_vec v, double n)
{
	t_vec result;
	result.x = v.x * n;
	result.y = v.y * n;
	result.z = v.z * n;
	return (result);
}

t_vec		div(t_vec v, double n)
{
	t_vec result;
	result.x = v.x / n;
	result.y = v.y / n;
	result.z = v.z / n;
	return (result);
}

t_vec		normalize(t_vec v)
{
	t_vec	result;
	double	norm;

	norm = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	result.x /= norm;
	result.y /= norm;
	result.z /= norm;
	return (result);
}

t_vec		add(t_vec v1, t_vec v2)
{
	t_vec result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vec		minus(t_vec v1, t_vec v2)
{
	t_vec result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

double	dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}