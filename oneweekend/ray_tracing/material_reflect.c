
#include "../miniRT.h"

void		init_material(t_material *material, t_vector color, double fuzz, \
												int (*scatter)(const t_ray*, void *, t_ray *))
{
	material->albedo = color;
	material->scatter = scatter;
	if (fuzz > 1)
		material->fuzz = 1;
	else
		material->fuzz = fuzz;
}

t_material	*get_material(t_vector color, double fuzz, \
							int (*scatter)(const t_ray*, void *, t_ray *))
{
	t_material	*material;

	material = (t_material *)malloc(sizeof(t_material));
	if (!material)
		return NULL;
	material->albedo = color;
	material->scatter = scatter;
	if (fuzz > 1)
		material->fuzz = 1;
	else
		material->fuzz = fuzz;
	return (material);
}

t_vector	get_rand_in_unitsphere(void)
{
	t_vector	ret;

	ret.x = 2 * (((double)(rand() % 10000)) / 10000) - 1;
	ret.y = 2 * (((double)(rand() % 10000)) / 10000) - 1;
	ret.z = 2 * (((double)(rand() % 10000)) / 10000) - 1;

	return (ret);
}

t_vector	get_scattered_dir(const t_vector *normal)
{
	t_vector	dir;

	dir = get_rand_in_unitsphere();
	if (dot(dir, *normal) > 0)
		return (dir);
	else
		return (multi(dir, -1));
}

int			lambertian(const t_ray *r_in, void *hitted_record, t_ray *scattered)
{
	const t_hit_record	*hitted;
	t_vector			scattered_dir;

	hitted = (const t_hit_record *)hitted_record;
	scattered_dir = get_scattered_dir(&hitted->normal);
	*scattered = get_ray(hitted->pos, scattered_dir);
	return (TRUE);
}

t_vector	get_reflected(const t_vector *v, const t_vector *n)
{
	return (minus(*v, multi(*n, 2 * dot(*v, *n))));
}

int			metal(const t_ray *r_in, void *hitted_record, t_ray *scattered)
{
	const t_hit_record	*hitted;
	t_vector			dir;

	hitted = (const t_hit_record *)hitted_record;
	dir = get_rand_in_unitsphere();
	dir = multi(dir, hitted->material->fuzz);
	dir = add(get_reflected(&r_in->dir, &hitted->normal), dir);
	*scattered = get_ray(hitted->pos, dir);
	return (dot(scattered->dir, hitted->normal) > 0);
}
