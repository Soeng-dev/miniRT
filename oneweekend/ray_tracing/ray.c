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

#include "../miniRT.h"

double		min(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

double		max(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
//figure
void			init_sphere(t_sphere *sp, t_vector center, double r)
{
	sp->ctr = center;
	sp->r = r;
}

//ray
void	init_ray(t_ray *ray, t_vector orig, t_vector dir)
{
	ray->pos = orig;
	ray->dir = dir;
}

t_vector	raypos_at_t(t_ray ray, double t)
{
	ray.pos = add(ray.pos, multi(ray.dir, t));
	return (ray.pos);
}

int	check_front_face(const t_ray *ray, const t_vector *outward_normal)
{
	return (dot(ray->pos, *outward_normal) < 0);
}

void	hit_sphere(void *sphere, const t_ray *ray, t_hit_record *hitted)
{
	double		a;
	double		b;
	double		c;
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
		hitted->time = min(hitted->time, (-b -sqrt(discriminant)) / a);
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

void	make_sphere(t_vector center, double radius)
{
	t_list	*sphere_node;

	sphere_node = (t_list *)malloc(sizeof(t_list));
	sphere_node->content = malloc(sizeof(t_sphere *));
	init_sphere((t_sphere *)(sphere_node->content), center, radius);
	ft_lstadd_front(&g_figures[SHPERE], sphere_node);
	return ;
}

int		ray_color(const t_ray *ray)
{
	double	ratio;
	int		r;
	int		g;
	int		b;
	t_hit_record	hitted;
	t_vector	color;

	init_hit_record(&hitted);
	raycast(ray, &hitted);
	if (hitted.time == NOT_HIT)
	{
		ratio = 0.5 * (ray->dir.y + 1.0);
		r = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.5);
		g = (int)((1.0 - ratio) * 255.0 + ratio * 255.0 * 0.7);
		b = 255;
		return (get_color(r, g, b));
	}
	color = normalize(minus(raypos_at_t(*ray, hitted.time), get_vector(0, 0, -1)));
	color = multi(add(color, get_vector(1.0, 1.0, 1.0)), 0.5 * 255.0);
	return (get_color(color.x, color.y, color.z));
}
