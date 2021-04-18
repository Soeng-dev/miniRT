/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymlx_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 21:27:54 by soekim            #+#    #+#             */
/*   Updated: 2021/03/16 13:01:52 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#define SAMPLES_PER_PIXEL	1
#define RT_MAX_DEPTH		5

int		get_color(t_vector colorvec, double gamma)
{
	int		color;

	colorvec = power(colorvec, 1.0 / gamma);
	colorvec = multi(colorvec, 255);
	color = (((int)colorvec.x << 16) \
			| ((int)colorvec.y << 8) \
			| ((int)colorvec.z));
	return (color);
}

void	prt_img(t_info *info)
{
	if (!info)
		return ;
	render_img(&info->setup.img_data, &info->setup.scr, \
				info->caminfo.curr_camnode->cam);
	mlx_put_image_to_window(info->setup.mlx_vars.mlx, \
							info->setup.mlx_vars.win, \
							info->setup.img_data.img, \
							0, 0);
	mlx_loop(info->setup.mlx_vars.mlx);
	return ;
}

int		key_check(int key, t_info *info)
{
	char	*s;
	int		cmd_result;

	if (key == KEY_ESC)
		exit_program(info);
	if (key == KEY_ENT)
	{
		s = NULL;
		get_next_line(STDIN, &s);
		cmd_result = check_command(s, info);
		free(s);
		if (cmd_result == CMD_ERROR)
			printf("Error\n");
		if (cmd_result == CMD_QUIT || cmd_result == CMD_ERROR)
			return (0);
	}
	else if (key == KEY_LEFT && info->caminfo.curr_camnode->prev)
		info->caminfo.curr_camnode = info->caminfo.curr_camnode->prev;
	else if (key == KEY_RIGHT && info->caminfo.curr_camnode->next)
		info->caminfo.curr_camnode = info->caminfo.curr_camnode->next;
	else
		return (0);
	prt_img(info);
	return (0);
}

void	render_img(const t_img_data *img, const t_screen *scr, \
					const t_camera *cam)
{
	t_vector	curr;
	t_vector	color;
	char		*pixel;

	if (!img || !scr || !cam)
		return ;
	printf("render img start\n");
	pixel = img->addr;
	curr.y = scr->height - 1;
	while (--curr.y >= 0)
	{
		printf("left	%.2f%%\n", (100.0 * curr.y) / scr->height);
		curr.x = -1.0;
		while (++curr.x < scr->width)
		{
			ft_memset(&color, 0, sizeof(t_vector));
			anti_alias(&color, cam, scr, &curr);
			*(unsigned int *)pixel = get_color(color, 2);
			pixel += (img->bpp / 8);
		}
	}
	printf("render image done\n");
}

void	anti_alias(t_vector *color, const t_camera *cam, \
					const t_screen *scr, t_vector *curr)
{
	t_vector	offset;
	t_ray		ray;
	double		u;
	double		v;
	double		s;

	s = -1.0;
	while (++s < SAMPLES_PER_PIXEL)
	{
		u = (curr->x + (s / SAMPLES_PER_PIXEL)) / (scr->width - 1);
		v = (curr->y + (s / SAMPLES_PER_PIXEL)) / (scr->height - 1);
		offset = add(multi(cam->horizontal, u), multi(cam->vertical, v));
		init_ray(&ray, cam->origin, \
				minus(add(cam->lowerleft, offset), \
						cam->origin));
		*color = add(*color, ray_color(&ray, RT_MAX_DEPTH));
	}
	*color = divide(*color, SAMPLES_PER_PIXEL);
	return ;
}
