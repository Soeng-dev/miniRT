
#include "../miniRT.h"

int		time_is_valid(long double time)
{
	return (T_MIN < time && time < T_MAX);
}

void	record_hitted(t_list *same_kind_figures, void (*hit)(void *figure, const t_ray *, t_hit_record *), const t_ray *ray, t_hit_record *hitted)
{
	t_hit_record	new_hitted;
	t_light			*lights;
	t_vector		light_dir;
	int				i;

	init_hit_record(&new_hitted);
	while (same_kind_figures)
	{
		hit((t_sphere*)same_kind_figures->content, ray, &new_hitted);
		if (new_hitted.time < hitted->time)
			*hitted = new_hitted;
		same_kind_figures = same_kind_figures->next;
	}
	lights = g_light_data.lights;
	if (!lights)
		return ;
	i = -1;
	while (++i < g_lights_data.count)
	{
		light_dir = normalize(minus(lights->pos, hitted->pos));
		hitted->spot_bright = light->bright * dot(light_dir, hitted->normal);
		++lights;
	}
	return ;
}

void		init_hit_record(t_hit_record *hitted)
{
	ft_memset(hitted, 0, sizeof(t_hit_record));
	hitted->time = NOT_HIT;
}

int		check_front_face(const t_ray *ray, const t_vector *outward_normal)
{
	return (dot(ray->dir, *outward_normal) < 0);
}
