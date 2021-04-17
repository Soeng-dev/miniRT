/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:20:47 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:56:58 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myvector.h"

double			sum_of_elements(t_vector v1)
{
	return (v1.x + v1.y + v1.z);
}

double			distance(t_vector v1, t_vector v2)
{
	v1 = minus(v1, v2);
	return (sqrt(dot(v1, v1)));
}

t_vector		multi_corresponds(t_vector v1, t_vector v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}

t_vector		vec_clamp(t_vector v, double min, double max)
{
	v.x = clamp(v.x, min, max);
	v.y = clamp(v.y, min, max);
	v.z = clamp(v.z, min, max);
	return (v);
}

void			prt_vector(char *pre, t_vector target, char *post)
{
	char	blank;

	blank = 0;
	if (!pre)
		pre = &blank;
	if (!post)
		post = &blank;
	return ;
}
