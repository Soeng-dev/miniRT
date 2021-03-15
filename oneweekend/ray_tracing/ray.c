/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/10 17:17:47 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_ray(t_ray *ray, t_vector pos, t_vector dir)
{
	ray->pos = pos;
	ray->dir = dir;
}

t_vector	raypos_at_t(t_ray ray, double t)
{
	ray.pos = add(ray.pos, multi(ray.dir, t));
	return (ray.pos);
}

int		check_front_face(const t_ray *ray, const t_vector *outward_normal)
{
	return (dot(ray->pos, *outward_normal) < 0);
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
		time = get_sphere_hitted_time(a, b, sqrt(discriminant));
		if (time == NOT_HIT)
			return ;
		hitted->time = min(hitted->time, time);
		hitted->pos = raypos_at_t(*ray, hitted->time);
		outward_normal = divide(minus(hitted->pos, sp->ctr), sp->r);
		hitted->is_front_face = check_front_face(ray, &outward_normal);
	}
	return ;
}

void	record_hitted(t_list *same_kind_figures, void (*hit)(void *figure, const t_ray *, t_hit_record *), const t_ray *ray, t_hit_record *hitted)
{
	while (same_kind_figures)
	{
		hit((t_sphere*)same_kind_figures->content, ray, hitted);
		same_kind_figures = same_kind_figures->next;
	}
	return ;
}

void	raycast(const t_ray *ray, t_hit_record *hitted)
{
	hitted->time = NOT_HIT;
	record_hitted(g_figures[SPHERE], hit_sphere, ray, hitted);
	return ;
}

void		init_hit_record(t_hit_record *hitted)
{
	ft_memset(hitted, 0, sizeof(t_hit_record));
	hitted->time = NOT_HIT;
}

t_vector	ray_color(const t_ray *ray)
{
	double	ratio;
	t_hit_record	hitted;
	t_vector	color;

	init_hit_record(&hitted);
	raycast(ray, &hitted);
	if (hitted.time == NOT_HIT)
	{
		ratio = 0.5 * (ray->dir.y + 1.0);
		color.x = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.5);
		color.y = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.7);
		color.z = 255;
		return (color);
	}
	color = normalize(minus(raypos_at_t(*ray, hitted.time), get_vector(0, 0, -1)));
	color = multi(add(color, get_vector(1.0, 1.0, 1.0)), 0.5 * 255.0);
	return (color);
}

t_vector	get_diffused_ray(

t_vector	ray_color_of_diffuse(const t_ray *ray, int max_depth)
{
	double	ratio;
	t_hit_record	hitted;
	t_vector	color;

	init_hit_record(&hitted);
	raycast(ray, &hitted);
	if (hitted.time == NOT_HIT)
	{
		ratio = 0.5 * (ray->dir.y + 1.0);
		color.x = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.5);
		color.y = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.7);
		color.z = 255;
		return (color);
	}
	color = normalize(minus(raypos_at_t(*ray, hitted.time), get_vector(0, 0, -1)));
	color = multi(add(color, get_vector(1.0, 1.0, 1.0)), 0.5 * 255.0);
	return (color);
}
