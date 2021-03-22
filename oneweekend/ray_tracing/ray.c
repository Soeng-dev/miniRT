/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:48:22 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	init_ray(t_ray *ray, t_vector pos, t_vector dir)
{
	ray->pos = pos;
	ray->dir = dir;
}

t_ray		get_ray(t_vector pos, t_vector dir)
{
	t_ray	ray;
	ray.pos = pos;
	ray.dir = dir;
	return (ray);
}

t_vector	raypos_at_t(t_ray ray, double t)
{
	ray.pos = add(ray.pos, multi(ray.dir, t));
	return (ray.pos);
}

void	raycast(const t_ray *ray, t_hit_record *hitted)
{
	hitted->time = NOT_HIT;
	record_hitted(g_figures[SPHERE], hit_sphere, ray, hitted);
	return ;
}

t_vector	get_background_color(const t_ray *ray)
{
	t_vector	background_color;
	double		ratio;

	ratio = 0.5 * (normalize(ray->dir).y + 1.0);
	background_color.x = (1.0 - ratio)+ ratio * 0.5;
	background_color.y = (1.0 - ratio)+ ratio * 0.7;
	background_color.z = 1.0;
	return (background_color);
}

t_vector	ray_color(const t_ray *ray, int depth)
{
	t_hit_record	hitted;
	t_vector		attenuation;
	t_ray			scattered;

	if (depth <= 0)
		return (get_vector(0, 0, 0));
	init_hit_record(&hitted);
	raycast(ray, &hitted);
	if (hitted.time == NOT_HIT)
		return (get_background_color(ray));
	if (hitted.material->scatter(ray, (void*)&hitted, &scattered))
	{
		attenuation = ray_color(&scattered, depth - 1);
		attenuation.x *= hitted.material->albedo.x;
		attenuation.y *= hitted.material->albedo.y;
		attenuation.z *= hitted.material->albedo.z;
		return (attenuation);
	}
	return (get_vector(0, 0, 0));
}


