/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myvector.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:20:47 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:56:58 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void			init_vector(t_vector *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vector		get_vector(double x, double y, double z)
{
	t_vector vec;

	init_vector(&vec, x, y, z);
	return (vec);
}

t_vector		multi(t_vector v, double n)
{
	t_vector result;
	result.x = v.x * n;
	result.y = v.y * n;
	result.z = v.z * n;
	return (result);
}

t_vector		divide(t_vector v, double n)
{
	v.x /= (n);
	v.y /= (n);
	v.z /= (n);
	return (v);
}

t_vector		normalize(t_vector v)
{
	double	norm;

	norm = sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	v.x /= norm;
	v.y /= norm;
	v.z /= norm;
	return (v);
}

t_vector		add(t_vector v1, t_vector v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

t_vector		minus(t_vector v1, t_vector v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

t_vector		power(t_vector v, double n)
{
	v.x = (double)powl((long double)v.x, (long double)n);
	v.y = (double)powl((long double)v.y, (long double)n);
	v.z = (double)powl((long double)v.z, (long double)n);
	return (v);
}

t_vector		vec_clamp(t_vector v, double min, double max)
{
	v.x = clamp(v.x, min, max);
	v.y = clamp(v.y, min, max);
	v.z = clamp(v.z, min, max);
	return (v);
}

t_vector	multi_corresponds(t_vector v1, t_vector v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}

double		sum_of_elements(t_vector v1)
{
	return (v1.x + v1.y + v1.z);
}

int				vector_is_same(t_vector v1, t_vector v2)
{
	if (v1.x == v2.x && \
		v1.y == v2.y && \
		v1.z == v2.z)
		return (TRUE);
	else
		return (FALSE);
}

double	dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	cross(t_vector v1, t_vector v2)
{
	t_vector	cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = -(v1.x * v2.z) + v1.z * v2.x;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}

int				is_valid_vector(t_vector v, double min, double max)
{
	return (min <= v.x && v.x <= max &&\
			min <= v.y && v.y <= max &&\
			min <= v.z && v.z <= max);
}

double		distance(t_vector v1, t_vector v2)
{
	v1 = minus(v1, v2);
	return (sqrt(dot(v1, v1)));
}

t_vector	rotate_vector(t_vector target, t_vector axis, double angle)
{
	t_vector	rotated;
	t_vector	temp;
	t_vector	coef;

	axis = normalize(axis);
	coef = multi(axis, 1 - cos(angle));
	temp.x = axis.x * coef.x + cos(angle);
	temp.y = axis.y * coef.x - axis.z * sin(angle);
	temp.z = axis.z * coef.x + axis.y * sin(angle);
	rotated.x = sum_of_elements(multi_corresponds(temp, target));
	temp.x = axis.x * coef.y + axis.z * sin(angle);
	temp.y = axis.y * coef.y + cos(angle);
	temp.z = axis.z * coef.y - axis.x * sin(angle);
	rotated.y = sum_of_elements(multi_corresponds(temp, target));
	temp.x = axis.x * coef.z - axis.y * sin(angle);
	temp.y = axis.y * coef.z + axis.x * sin(angle);
	temp.z = axis.z * coef.z - cos(angle);
	rotated.z = sum_of_elements(multi_corresponds(temp, target));
	return (rotated);
}
