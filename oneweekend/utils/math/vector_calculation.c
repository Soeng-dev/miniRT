/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_calculation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:20:47 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:56:58 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myvector.h"

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

t_vector		multi(t_vector v, double n)
{
	v.x *= n;
	v.y *= n;
	v.z *= n;
	return (v);
}

t_vector		divide(t_vector v, double n)
{
	v.x /= (n);
	v.y /= (n);
	v.z /= (n);
	return (v);
}
