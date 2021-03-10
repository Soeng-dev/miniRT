/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:17:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/10 17:16:41 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void			init_sphere(t_sphere *sp, t_vector center, double r)
{
	sp->ctr = center;
	sp->r = r;
}

void	make_sphere(t_vector center, double radius)
{
	t_list	*sphere_node;

	sphere_node = (t_list *)malloc(sizeof(t_list));
	if (!sphere_node)
		return ;
	sphere_node->content = malloc(sizeof(t_sphere));
	if (!(sphere_node->content))
		return ;
	init_sphere((t_sphere *)(sphere_node->content), center, radius);
	ft_lstadd_front(&g_figures[SPHERE], sphere_node);
	return ;
}

double	get_sphere_hitted_time(double a, double b, double sqrt_dis)
{
	double time;

	time = (-b - sqrt_dis) / a;
	if (T_MIN < time && time < T_MAX)
		return (time);
	time = (-b + sqrt_dis) / a;
	if (T_MIN < time && time < T_MAX)
		return (time);
	else
		return (NOT_HIT);
}
