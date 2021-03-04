/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/04 21:29:55 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ray_tracing.h"

void	initray(t_ray *ray, t_vec orig, t_vec dir)
{
	ray->orig = orig;
	ray->curr = orig;
	ray->dir = dir;
}

void	cast(t_ray *ray, double t)
{
	ray->curr.x += (ray->dir.x * t);
	ray->curr.y += (ray->dir.y * t);
	ray->curr.z += (ray->dir.z * t);
}

int		hitsp(const t_sp *sp, const t_ray *ray)
{
	double	a;
	double	b;
	double	c;

	a = dot(ray->dir, ray->dir);
	b = dot(multi(ray->dir, 2.0), minus(ray->orig, sp->ctr));
	c = dot(minus(ray->orig, sp->ctr), minus(ray->orig, sp->ctr));

	return ((b * b - 4 * a * c) >= 0);
}

int		ray_color(const t_ray *ray, const t_sp *sp)
{
	double	ratio;
	int		r, g, b;

	if (hitsp(sp, ray))
		return (get_color(1,0,0));
	ratio = 0.5 * (ray->dir.y + 1.0);
	//printf("%g\n", ray->dir.y);
	r = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.5);
	g = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.7);
	b = 255;
	//printf("%d %d %d\n", r, g,b);
	return (get_color(r, g, b));
}