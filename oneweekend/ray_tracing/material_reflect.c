
#include "../miniRT.h"

void		init_material(t_material *material, t_vector color,\
												int (*scatter)(const t_ray*, void *, t_ray *))
{
	material->albedo = color;
	material->scatter = scatter;
}

t_material	get_material(t_vector albedo, int (*scatter)(const t_ray*, void *, t_ray *))
{
	t_material	material;

	material.albedo = albedo;
	material.scatter = scatter;
	return (material);
}

int			lambertian(const t_ray *r_in, void *hitted_record, t_ray *scattered)
{
	t_hit_record	*hitted;

	hitted = (t_hit_record *)hitted_record;
	*scattered = get_ray(hitted->pos, get_scattered_dir(&(hitted->normal)));
	return (TRUE);
}

t_vector	get_reflected(const t_vector *v, const t_vector *n)
{
	return (minus(*v, multi(*n, 2 * dot(*v, *n))));
}

int			metal(const t_ray *r_in, void *hitted_record, t_ray *scattered)
{
	t_hit_record	*hitted;

	hitted = (t_hit_record *)hitted_record;
	*scattered = get_ray(hitted->pos,\
									get_reflected(&r_in->dir, &hitted->normal));
	return (dot(scattered->dir, hitted->normal) > 0);
}
