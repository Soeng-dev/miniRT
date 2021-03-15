

#include "../miniRT.h"
t_vector	get_hemisphere_dir(const t_vector *normal)
{
	t_vector	dir;
	double		theta;
	double		alpha;
	double		beta;

	theta = acos(normal->x);
	srand(time(NULL));
	alpha = (M_PI / 2) * (((double)(rand() % 10000)) / 10000) - M_PI;
	srand(time(NULL));
	beta =  (M_PI / 2) * (((double)(rand() % 10000)) / 10000) - M_PI;
	dir.x = cos(theta + alpha);
	dir.y = sin(theta + alpha);
	dir.z = cos(acos(normal->z) + beta);
	return (dir);
}

t_vector	ray_color_of_diffuse(const t_ray *ray, int depth)
{
	double			ratio;
	t_hit_record	hitted;
	t_vector		color;
	t_ray			diffused_ray;

	if (depth <= 0)
		return (get_vector(0, 0, 0));
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
	diffused_ray.pos = hitted.pos;
	diffused_ray.dir = add(hitted.normal, get_hemisphere_dir(&(hitted.normal)));
	return (multi(ray_color_of_diffuse(&diffused_ray, depth - 1), 0.5));
}
