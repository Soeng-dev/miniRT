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
	double			coef;

	light_dir = normalize(minus(light->pos, hitted->pos));
	init_ray(&hitted_to_light, hitted->pos, light_dir);
	raycast(&hitted_to_light, &blocked);
	if (blocked.time == NOT_HIT || \
		distance(light->pos, hitted->pos) \
		<= distance(blocked.pos, hitted->pos))
		coef = sqrt(light->bright * \
					pow(absol(dot(light_dir, hitted->normal)), 10));
	else if (blocked.object == hitted->object)
		coef = -1.0 * absol(dot(blocked.normal, light_dir));
	else
		coef = -1.0;
	spot_bright = 1.0 + light->bright * coef;
	*color = add(get_vector(1, 1, 1), multi(light->color, coef));
	*color = multi(*color, spot_bright);
	*color = minus(*color, get_vector(0.1, 0.1, 0.1));
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
	*color = add(get_vector(0.05, 0.05, 0.05), *color);
	*color = multi_corresponds(spot_color, *color);
	*color = minus(*color, get_vector(0.05, 0.05, 0.05));
	return ;
}
