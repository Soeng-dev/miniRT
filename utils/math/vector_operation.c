/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:20:47 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:56:58 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myvector.h"

double			dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector		cross(t_vector v1, t_vector v2)
{
	t_vector	cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = -(v1.x * v2.z) + v1.z * v2.x;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}

t_vector		normalize(t_vector v)
{
	double	norm;

	norm = sqrt(powl((long double)v.x, 2)	\
			+ powl((long double)v.y, 2) + powl((long double)v.z, 2));
	v.x /= norm;
	v.y /= norm;
	v.z /= norm;
	return (v);
}

t_vector		rotate_vector(t_vector target, t_vector axis, double angle)
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
	temp.z = axis.z * coef.z + cos(angle);
	rotated.z = sum_of_elements(multi_corresponds(temp, target));
	return (rotated);
}
