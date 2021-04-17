/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void	init_plane(t_plane *plane, t_vector p, \
					t_vector normal, t_material *material)
{
	plane->p = p;
	plane->normal = normalize(normal);
	plane->material = *material;
	return ;
}

void	make_plane(t_vector p, t_vector normal, t_material *material)
{
	t_list	*plane_node;

	plane_node = (t_list *)malloc(sizeof(t_list));
	if (!plane_node)
		return ;
	plane_node->content = malloc(sizeof(t_plane));
	if (!plane_node->content)
		return ;
	init_plane((t_plane *)(plane_node->content), p, normal, material);
	plane_node->pos = &((t_plane *)plane_node->content)->p;
	ft_lstadd_front(&g_figures[PLANE], plane_node);
	return ;
}

int		check_plane_hitpos(const t_plane *pl, const t_ray *ray, \
							t_hit_record *hitted)
{
	double	time;

	time = dot(minus(pl->p, ray->pos), pl->normal)\
			/ dot(ray->dir, pl->normal);
	if (time_is_valid(time))
	{
		hitted->time = time;
		hitted->pos = raypos_at_t(*ray, time);
		return (TRUE);
	}
	else
		return (FALSE);
}

void	record_hittedpl_normal_mat(const t_plane *pl, const t_ray *ray, \
									t_hit_record *hitted)
{
	if (dot(ray->dir, pl->normal) < 0)
		hitted->normal = pl->normal;
	else
		hitted->normal = multi(pl->normal, -1.0);
	hitted->is_front_face = TRUE;
	hitted->material = (t_material *)&pl->material;
	return ;
}

void	hit_plane(void *plane, const t_ray *ray, t_hit_record *hitted)
{
	if (check_plane_hitpos((const t_plane *)plane, ray, hitted))
		record_hittedpl_normal_mat(plane, ray, hitted);
	else
		hitted->time = NOT_HIT;
	return ;
}
