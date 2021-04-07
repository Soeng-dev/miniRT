 
#include "../../miniRT.h"

void			init_cylinder(t_cylinder *cyl, t_vector ctr, t_vector normal, t_material *material)
{
	cyl->ctr = ctr;
	cyl->normal = normal;
	cyl->material = *material;
	return ;
}

void			make_cylinder(t_vector ctr, t_vector normal, t_material *material)
{
	t_list	*cyl_node;

	cyl_node = (t_list *)malloc(sizeof(t_list));
	if (!cyl_node)
		return ;
	cyl_node->content = malloc(sizeof(t_cylinder));
	if (!cyl_node->content)
		return ;
	init_cylinder((t_cylinder *)(cyl_node->content), ctr, normal, material);
	ft_lstadd_front(&g_figures[CYLINDER], cyl_node);
}

static double	get_cyl_hitted_time(double a, double b, double sqrt_dis)
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

static void		set_cyl_hitrec(t_hit_record *hitted, const t_cylinder *cyl, const t_ray *ray)
{
	t_vector	outward_normal;
	double		h;

	if (hitted->time == NOT_HIT)
		return ;
	hitted->pos = raypos_at_t(*ray, hitted->time);
	hitted->material = (t_material *)&cyl->material;
	h = dot(cyl->normal, minus(ray->pos, cyl->ctr)) / dot(cyl->normal, cyl->normal);
	outward_normal = minus(ray->pos, add(cyl->ctr, multi(cyl->normal, h)));
	hitted->is_front_face = check_front_face(ray, &outward_normal);
	if (hitted->is_front_face)
		hitted->normal = outward_normal;
	else
		hitted->normal = multi(outward_normal, -1);
	return ;
}

void			hit_cylinder(void *cylinder, const t_ray *ray, t_hit_record *hitted)
{
	double				a;
	double				b;
	double				c;
	double				discriminant;
	t_vector			delp;
	const t_cylinder	*cyl;

	cyl = (const t_cylinder *)cylinder;
	delp = minus(ray->pos, cyl->ctr);
	a = dot(minus(ray->dir, multi(cyl->normal, dot(ray->dir, cyl->normal))), \
			minus(ray->dir, multi(cyl->normal, dot(ray->dir, cyl->normal))));
	b = dot(minus(ray->dir, multi(cyl->normal, dot(cyl->normal, ray->dir))), \
			minus(delp, multi(cyl->normal, dot(delp, cyl->normal))));
	c = dot(minus(delp, multi(cyl->normal, dot(delp, cyl->normal))), \
			minus(delp, multi(cyl->normal, dot(delp, cyl->normal)))) \
		 - cyl->r * cyl->r;
	discriminant = b * b - a * c;
	if (discriminant > 0)
		hitted->time = get_cyl_hitted_time(a, b, sqrt(discriminant));
	set_cyl_hitrec(hitted, cyl, ray);
}
