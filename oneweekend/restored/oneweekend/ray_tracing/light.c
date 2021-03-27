
#include "../miniRT.h"

void	init_light(t_light *light, t_vector pos, t_vector color, double bright)
{
	light->color = color;
	light->bright = bright;
	light->pos = pos;
	return ;
}

void	make_light(t_vector pos, t_vector color, double bright)
{
	t_light		*light;

	light = (t_light *)malloc((g_light_data.count + 2) * sizeof(t_light));
	if (!light)
		return ;
	if (g_light_data.light_arr)
	{
		ft_memcpy(light, g_light_data.light_arr, g_light_data.count);
		free(g_light_data.light_arr);
	}
	g_light_data.light_arr = light;
	light = g_light_data.light_arr + g_light_data.count;
	init_light(light, pos, color, bright);
	g_light_data.count++;
}

void	delete_light(void)
{
	free(g_light_data.light_arr);
	g_light_data.light_arr = NULL;
	g_light_data.count = 0;
}

void	light_hitted(const t_hit_record *hitted, t_vector *color)
{
	t_light			*light;
	t_vector		light_dir;
	t_ray			hitted_to_light;
	t_hit_record	blocked;
	int				i;
	t_vector		spot_color = get_vector(0,0,0);
	t_vector		color_by_light;
	double			spot_bright = 0;

	light = g_light_data.light_arr;
	if (!light)
		return ;
	i = -1;
	while (++i < g_light_data.count)
	{
		light_dir = normalize(minus(light->pos, hitted->pos));
		hitted_to_light = get_ray(hitted->pos, light_dir);
		raycast(&hitted_to_light, &blocked);
		if (blocked.time == NOT_HIT)
		{
			spot_bright = 1 + light->bright * \
							dot(light_dir, hitted->normal);
			color_by_light = multi(light->color, spot_bright);
		}
		else
		{
			spot_bright = 1.0 - light->bright;
			color_by_light = minus(get_vector(1, 1, 1), light->color);
			color_by_light = multi(color_by_light, spot_bright);
		}
		spot_color = add(spot_color, color_by_light);
		++light;
	}
	*color = multi_corresponds(spot_color, *color);
	return ;
}
