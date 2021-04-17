/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:29:17 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:48:22 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
		ft_memcpy(light, g_light_data.light_arr, \
					g_light_data.count * sizeof(t_light));
		free(g_light_data.light_arr);
	}
	g_light_data.light_arr = light;
	init_light(light + g_light_data.count, pos, color, bright);
	g_light_data.count++;
}

void	delete_light(void)
{
	free(g_light_data.light_arr);
	g_light_data.light_arr = NULL;
	g_light_data.count = 0;
}

void	color_by_light(t_vector *color, const t_hit_record *hitted, \
						t_light *light)
{
	t_hit_record	blocked;
	t_vector		light_dir;
	t_ray			hitted_to_light;
	double			spot_bright;

	init_hit_record(&blocked);
	light_dir = minus(light->pos, hitted->pos);
	init_ray(&hitted_to_light, hitted->pos, light_dir);
	raycast(&hitted_to_light, &blocked);
	if (blocked.time == NOT_HIT)
	{
		spot_bright = 1 + light->bright * \
							absol(dot(normalize(light_dir), hitted->normal));
		*color = add(light->color, get_vector(1, 1, 1));
		*color = multi(*color, spot_bright);
	}
	else
	{
		spot_bright = 1.0 - light->bright;
		*color = minus(get_vector(1, 1, 1), light->color);
		*color = multi(*color, spot_bright);
	}
	return ;
}

void	light_hitted(const t_hit_record *hitted, t_vector *color)
{
	t_light			*light;
	t_vector		spot_color;
	t_vector		lighted_color;
	int				i;

	if (!g_light_data.light_arr)
		return ;
	init_vector(&spot_color, 0, 0, 0);
	light = g_light_data.light_arr;
	i = -1;
	while (++i < g_light_data.count)
	{
		color_by_light(&lighted_color, hitted, light);
		spot_color = add(lighted_color, spot_color);
		++light;
	}
	spot_color = divide(spot_color, g_light_data.count);
	*color = multi_corresponds(spot_color, *color);
	return ;
}
