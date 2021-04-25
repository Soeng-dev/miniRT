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

void	set_mlx_resolution(char *s, t_info *info, int *is_error)
{
	int		max_width;
	int		max_height;

	if (info->setup.scr.width || info->setup.scr.height)
	{
		printf("Multi declaration of Resolution\n");
		info->err_exit = TRUE;
	}
	mlx_get_screen_size(info->setup.mlx_vars.mlx, &max_width, &max_height);
	info->setup.scr.width = dbl_min(read_dbl(&s, is_error), (double)max_width);
	info->setup.scr.height = dbl_min(read_dbl(&s, is_error), \
									(double)max_height);
	info->setup.scr.ratio = info->setup.scr.width / info->setup.scr.height;
	pass_charset(&s, " \t\f");
	if (*s != '\0')
		*is_error = TRUE;
	if (info->setup.scr.width <= 0 || info->setup.scr.height <= 0)
	{
		printf("Invalid Resolution\n");
		info->err_exit = TRUE;
	}
	init_vector(&g_light_data.filter, 1.0, 1.0, 1.0);
	return ;
}

void	set_ambient(char *s, t_info *info, int *is_error)
{
	double		bright;
	t_vector	ambient;

	if (!vector_is_same(g_light_data.ambient, \
						get_vector(0, 0, 0)))
	{
		printf("Multi declaration of Ambient\n");
		info->err_exit = TRUE;
		return ;
	}
	bright = read_dbl(&s, is_error);
	if (bright <= 0 || bright > 1.0)
		return (set_errflag(is_error));
	ambient = divide(read_vector(&s, is_error), 255.0);
	pass_charset(&s, " \t\f");
	if (vector_is_same(ambient, get_vector(0, 0, 0)) \
		|| ambient.x < 0 || ambient.x > 1.0 \
		|| ambient.y < 0 || ambient.y > 1.0 \
		|| ambient.z < 0 || ambient.z > 1.0 \
		|| *s != '\0')
		return (set_errflag(is_error));
	ambient = multi(ambient, bright);
	g_light_data.ambient = ambient;
	return ;
}

void	set_camera(char *s, t_info *info, int *is_error)
{
	t_campos	campos;
	t_camview	camview;

	campos.origin = read_vector(&s, is_error);
	campos.dir = normalize(read_vector(&s, is_error));
	if (absol(dot(campos.dir, get_vector(0, 1, 0))) > 0.9)
		campos.upward = get_vector(0, 1, 1);
	else
		campos.upward = get_vector(0, 1, 0);
	camview.angle = M_PI * (read_dbl(&s, is_error) / 180.0);
	pass_charset(&s, " \t\f");
	if (camview.angle >= M_PI || camview.angle <= 0 || *s != '\0')
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

	pos = read_vector(&s, is_error);
	bright = read_dbl(&s, is_error);
	color = divide(read_vector(&s, is_error), 255.0);
	pass_charset(&s, " \t\f");
	if (bright <= 0 || *s != '\0' \
		|| vector_is_same(color, get_vector(0, 0, 0)) \
		|| color.x < 0 || color.x > 1.0 \
		|| color.y < 0 || color.y > 1.0 \
		|| color.z < 0 || color.z > 1.0)
		return (set_errflag(is_error));
	make_light(pos, color, bright);
}
