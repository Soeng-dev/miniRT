/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:17:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/15 19:55:33 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int		time_is_valid(long double time)
{
	return (T_MIN < time && time < T_MAX);
}

void	record_hitted(t_list *same_kind_figures, \
					void (*hit)(void *figure, const t_ray *, t_hit_record *), \
					const t_ray *ray, t_hit_record *hitted)
{
	t_hit_record	new_hitted;

	if (!hit || !hitted)
		return ;
	while (same_kind_figures)
	{
		init_hit_record(&new_hitted);
		hit(same_kind_figures->content, ray, &new_hitted);
		if (new_hitted.time < hitted->time)
		{
			*hitted = new_hitted;
			hitted->object = same_kind_figures->content;
		}
		same_kind_figures = same_kind_figures->next;
	}
	return ;
}

void	init_hit_record(t_hit_record *hitted)
{
	ft_memset(hitted, 0, sizeof(t_hit_record));
	hitted->time = NOT_HIT;
}

int		check_front_face(const t_ray *ray, const t_vector *outward_normal)
{
	return (dot(ray->dir, *outward_normal) < 0);
}

void	set_cyl_hitrec(t_hit_record *hitted, const t_cylinder *cyl, \
							const t_ray *ray, double time)
{
	double			h;
	t_vector		pos;
	t_vector		outward_normal;

	pos = raypos_at_t(*ray, time);
	h = dot(minus(pos, cyl->bottom.p), cyl->normal) \
		/ dot(cyl->normal, cyl->normal);
	if (0 < h && h < cyl->height)
	{
		hitted->pos = pos;
		outward_normal = normalize(\
								minus(pos, add(cyl->bottom.p, \
												multi(cyl->normal, h))));
		hitted->time = time;
		hitted->material = (t_material *)&cyl->material;
		hitted->is_front_face = check_front_face(ray, &outward_normal);
		if (hitted->is_front_face)
			hitted->normal = outward_normal;
		else
			hitted->normal = multi(outward_normal, -1.0);
	}
}
