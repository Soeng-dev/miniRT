/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_view.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 16:07:37 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 12:55:42 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "manage_command.h"

void	set_mlx_resolution(char *s, t_info *info)
{
	int		max_width;
	int		max_height;

	if (info->setup.scr.width || info->setup.scr.height)
	{
		printf("Multi declaration of Resolution\n");
		info->err_exit = TRUE;
	}
	mlx_get_screen_size(info->setup.mlx_vars.mlx, &max_width, &max_height);
	info->setup.scr.width = dbl_min(read_dbl(&s), (double)max_width);
	info->setup.scr.height = dbl_min(read_dbl(&s), (double)max_height);
	info->setup.scr.ratio = info->setup.scr.width / info->setup.scr.height;
	if (info->setup.scr.width <= 0 || info->setup.scr.height <= 0)
	{
		printf("Invalid Resolution\n");
		info->err_exit = TRUE;
	}
	return ;
}

void	set_ambient(char *s, int *is_error)
{
	double		bright;
	t_vector	ambient;

	if (!vector_is_same(g_light_data.ambient, \
						get_vector(0, 0, 0)))
		return ;
	bright = read_dbl(&s);
	if (bright < 0)
		return (set_errflag(is_error));
	ambient = divide(read_vector(&s), 255.0);
	if (ambient.x < 0 || ambient.y < 0 || ambient.z < 0)
		return (set_errflag(is_error));
	ambient = multi(ambient, bright);
	g_light_data.ambient = ambient;
	return ;
}

void	set_camera(char *s, t_info *info, int *is_error)
{
	t_campos	campos;
	t_camview	camview;

	campos.upward = get_vector(0, 1, 0);
	campos.origin = read_vector(&s);
	campos.dir = normalize(read_vector(&s));
	camview.angle = M_PI * (read_dbl(&s) / 180.0);
	if (camview.angle >= M_PI || camview.angle <= 0)
		return (set_errflag(is_error));
	camview.focallen = 1.0;
	camview.ratio = info->setup.scr.ratio;
	make_camera(&info->caminfo, &campos, &camview);
}

void	set_light(char *s, int *is_error)
{
	t_vector	pos;
	t_vector	color;
	double		bright;

	pos = read_vector(&s);
	bright = read_dbl(&s);
	color = divide(read_vector(&s), 255.0);
	if (bright < 0 || color.x < 0 || color.y < 0 || color.z < 0)
		return (set_errflag(is_error));
	make_light(pos, color, bright);
}
