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

#include "../../minirt.h"

void		init_cylinder(t_cylinder *cyl, const t_plane *bottom, \
							double r, double height)
{
	cyl->r = r;
	cyl->height = height;
	cyl->bottom = *bottom;
	cyl->bottom.normal = multi(bottom->normal, -1);
	cyl->top = *bottom;
	cyl->top.p = add(bottom->p, multi(bottom->normal, height));
	cyl->normal = bottom->normal;
	cyl->material = bottom->material;
	return ;
}

void		make_cylinder(const t_plane *bottom, \
						const double r, const double height)
{
	t_list	*cyl_node;

	cyl_node = (t_list *)malloc(sizeof(t_list));
	if (!cyl_node)
		return ;
	cyl_node->content = malloc(sizeof(t_cylinder));
	if (!cyl_node->content)
		return ;
	init_cylinder((t_cylinder *)(cyl_node->content), bottom, r, height);
	cyl_node->pos = &((t_cylinder *)cyl_node->content)->bottom.p;
	ft_lstadd_front(&g_figures[CYLINDER], cyl_node);
}

void		hit_circle(const t_plane *pl, double r, \
						const t_ray *ray, t_hit_record *hitted)
{
	init_hit_record(hitted);
	if (check_plane_hitpos(pl, ray, hitted))
	{
		if (distance(hitted->pos, pl->p) < r)
			record_hittedpl_normal_mat(pl, ray, hitted);
		else
		{
			hitted->time = NOT_HIT;
			init_vector(&hitted->pos, 0, 0, 0);
		}
	}
}

void		set_cyl_hitrec(t_hit_record *hitted, const t_cylinder *cyl, \
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

void		hit_cylinder(void *cylinder, const t_ray *ray, t_hit_record *hitted)
{
	double				time;
	double				eqcoef[3];
	t_vector			delp;
	const t_cylinder	*cyl;
	t_hit_record	check_top;
	t_hit_record	check_bottom;

	cyl = (const t_cylinder *)cylinder;
	delp = minus(ray->pos, cyl->bottom.p);
	eqcoef[0] = dot(minus(ray->dir, multi(cyl->normal, \
											dot(ray->dir, cyl->normal))), \
					minus(ray->dir, multi(cyl->normal, \
											dot(ray->dir, cyl->normal))));
	eqcoef[1] = 2 * dot(minus(ray->dir, multi(cyl->normal, \
												dot(cyl->normal, ray->dir))), \
						minus(delp, multi(cyl->normal, \
											dot(delp, cyl->normal))));
	eqcoef[2] = dot(minus(delp, multi(cyl->normal, \
										dot(delp, cyl->normal))), \
					minus(delp, multi(cyl->normal, \
										dot(delp, cyl->normal)))) \
				- cyl->r * cyl->r;
	time = get_valid_2nd_eqsol(eqcoef, NOT_HIT, time_is_valid);
	hit_circle(&cyl->top, cyl->r, ray, &check_top);
	hit_circle(&cyl->bottom, cyl->r, ray, &check_bottom);
	if (check_top.time < check_bottom.time)
		*hitted = check_top;
	else
		*hitted = check_bottom;
	if (hitted->time <= time)
		return;
	else if (time < hitted->time)
		set_cyl_hitrec(hitted, cyl, ray, time);
	else if (time == NOT_HIT)
		return ;
	return ;
}
