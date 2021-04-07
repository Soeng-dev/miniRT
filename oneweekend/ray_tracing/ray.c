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
	record_hitted(g_figures[PLANE], hit_plane, ray, hitted);
	record_hitted(g_figures[TRIANGLE], hit_triangle, ray, hitted);
	record_hitted(g_figures[SPHERE], hit_sphere, ray, hitted);
	record_hitted(g_figures[SQUARE], hit_square, ray, hitted);
	return ;
}

t_vector	ray_color(const t_ray *ray, int depth)
{
	t_hit_record	hitted;
	t_vector		color;
	t_ray			scattered;

	if (depth <= 0)
		return (get_vector(0.5, 0.5, 0.5));
	init_hit_record(&hitted);
	raycast(ray, &hitted);
	if (hitted.time == NOT_HIT)
		color = g_light_data.ambient;
	else if (hitted.material->scatter(ray, (void*)&hitted, &scattered))
	{
		color = ray_color(&scattered, depth - 1);
		color = multi_corresponds(hitted.material->albedo, color);
		light_hitted(&hitted, &color);
		color = vec_clamp(color, 0.0001, 1);
	}
	else
		color = get_vector(1, 1, 1);
	return (color);
}


