/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:17:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/15 19:55:33 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

void			init_sphere(t_sphere *sp, t_vector center, double r, \
							t_material *material)
{
	sp->ctr = center;
	sp->r = r;
	sp->material = *material;
	return ;
}

void			make_sphere(t_vector center, double radius, \
							t_material *material)
{
	t_list	*sphere_node;

	sphere_node = (t_list *)malloc(sizeof(t_list));
	if (!sphere_node)
		return ;
	sphere_node->content = malloc(sizeof(t_sphere));
	if (!(sphere_node->content))
		return ;
	init_sphere((t_sphere *)(sphere_node->content), center, radius, material);
	sphere_node->pos = &((t_sphere *)sphere_node->content)->ctr;
	ft_lstadd_front(&g_figures[SPHERE], sphere_node);
	return ;
}

static void		set_sphere_hitrec(t_hit_record *hitted, \
									const t_sphere *sp, const t_ray *ray)
{
	t_vector	outward_normal;

	if (hitted->time == NOT_HIT)
		return ;
	hitted->pos = raypos_at_t(*ray, hitted->time);
	hitted->material = (t_material *)&sp->material;
	outward_normal = divide(minus(hitted->pos, sp->ctr), sp->r);
	hitted->is_front_face = check_front_face(ray, &outward_normal);
	if (hitted->is_front_face)
		hitted->normal = outward_normal;
	else
		hitted->normal = multi(outward_normal, -1);
}

void			hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted)
{
	double			eqcoef[3];
	const t_sphere	*sp;

	sp = (const t_sphere *)sphere;
	eqcoef[0] = dot(ray->dir, ray->dir);
	eqcoef[1] = 2 * dot(ray->dir, minus(ray->pos, sp->ctr));
	eqcoef[2] = dot(minus(ray->pos, sp->ctr), minus(ray->pos, sp->ctr)) \
				- pow(sp->r, 2);
	hitted->time = get_valid_2nd_eqsol(eqcoef, NOT_HIT, time_is_valid);
	set_sphere_hitrec(hitted, sp, ray);
	return ;
}
