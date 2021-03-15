/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/15 19:13:47 by soekim           ###   ########.fr       */
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

void	raycast(const t_ray *ray, t_hit_record *hitted)
{
	hitted->time = NOT_HIT;
	record_hitted(g_figures[SPHERE], hit_sphere, ray, hitted);
	return ;
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

