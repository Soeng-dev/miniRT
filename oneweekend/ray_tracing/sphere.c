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

#include "../miniRT.h"

void	init_sphere(t_sphere *sp, t_vector center, double r, t_material *material)
{
	sp->ctr = center;
	sp->r = r;
	sp->material = material;
}

void	make_sphere(t_vector center, double radius, t_material *material)
{
	t_list	*sphere_node;

	sphere_node = (t_list *)malloc(sizeof(t_list));
	if (!sphere_node)
		return ;
	sphere_node->content = malloc(sizeof(t_sphere));
	if (!(sphere_node->content))
		return ;
	init_sphere((t_sphere *)(sphere_node->content), center, radius, material);
	ft_lstadd_front(&g_figures[SPHERE], sphere_node);
	return ;
}

double	get_sphere_hitted_time(double a, double b, double sqrt_dis)
{
	double time;

	time = (-b - sqrt_dis) / a;
	if (time_is_valid(time))
		return (time);
	time = (-b + sqrt_dis) / a;
	if (time_is_valid(time))
		return (time);
	else
		return (NOT_HIT);
}

void	hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted)
{
	double		a;
	double		b;
	double		c;
	double		time;
	double		discriminant;
	t_sphere	*sp;
	t_vector	outward_normal;

	sp = (t_sphere *)sphere;
	a = dot(ray->dir, ray->dir);
	b = dot(ray->dir, minus(ray->pos, sp->ctr));
	c = dot(minus(ray->pos, sp->ctr), minus(ray->pos, sp->ctr)) - pow(sp->r, 2);
	discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		hitted->time = get_sphere_hitted_time(a, b, sqrt(discriminant));
		if (hitted->time == NOT_HIT)
			return ;
		hitted->pos = raypos_at_t(*ray, hitted->time);
		hitted->material = sp->material;
		outward_normal = divide(minus(hitted->pos, sp->ctr), sp->r);
		hitted->is_front_face = check_front_face(ray, &outward_normal);
		if (hitted->is_front_face)
			hitted->normal = outward_normal;
		else
			hitted->normal = multi(outward_normal, -1);
	}
	return ;
}
