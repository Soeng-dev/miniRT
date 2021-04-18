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

#include "myvector.h"

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

int				vector_is_same(t_vector v1, t_vector v2)
{
	if (v1.x == v2.x && \
		v1.y == v2.y && \
		v1.z == v2.z)
		return (TRUE);
	else
		return (FALSE);
}

int				is_valid_vector(t_vector v, double min, double max)
{
	return (min <= v.x && v.x <= max &&\
			min <= v.y && v.y <= max &&\
			min <= v.z && v.z <= max);
}
