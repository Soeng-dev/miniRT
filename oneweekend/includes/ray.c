/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/05 18:13:27 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ray_tracing.h"

void	initray(t_ray *ray, t_vec orig, t_vec dir)
{
	ray->orig = orig;
	ray->dir = dir;
}

t_ray	cast(t_ray ray, double t)
{
	ray.orig.x += (ray.dir.x * t);
	ray.orig.y += (ray.dir.y * t);
	ray.orig.z += (ray.dir.z * t);
	return (ray);
}

double	hitsp(const t_sp *sp, const t_ray *ray)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = dot(ray->dir, ray->dir);
	b = 2.0 * dot(ray->dir, minus(ray->orig, sp->ctr));
	c = dot(minus(ray->orig, sp->ctr), minus(ray->orig, sp->ctr)) - pow(sp->r, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	else
		return ((-b - sqrt(discriminant)) / (2.0 * a));
}

int		ray_color(const t_ray *ray, const t_sp *sp)
{
	double	ratio;
	int		r;
	int		g;
	int		b;
	double	t;

	t = hitsp(sp, ray);
	if (t > 0.0)
	{
		t_vec color = normalize(minus(cast(*ray, t).orig, getvec(0, 0, -1)));
		color = multi(add(color, getvec(1.0, 1.0, 1.0)), 0.5 * 255.0);
		printf("%d %d %d\n", (int)color.x, (int)color.y, (int)color.z);
		return (get_color(color.x, color.y, color.z));
	}
	ratio = 0.5 * (ray->dir.y + 1.0);
	r = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.5);
	g = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.7);
	b = 255;
	return (get_color(r, g, b));
}
