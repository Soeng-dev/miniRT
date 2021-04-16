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

int		get_color(t_vector colorvec, double gamma)
{
	int		color;

	colorvec = power(colorvec, 1.0 / gamma);
	colorvec = multi(colorvec, 255);
	color = (((int)colorvec.x << 16) | ((int)colorvec.y << 8) | ((int)colorvec.z));
	return (color);
}

int		key_check(int key, t_info *info)
{
	char	*s;
	int		cmd_result;

	if (key == KEY_ESC)
		exit(0); //change to memory managed function
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
	else if (key == KEY_LEFT)
	{
		if (!info->caminfo.curr_camnode->prev)
			return (0);
		info->caminfo.curr_camnode = info->caminfo.curr_camnode->prev;
	}
	else if (key == KEY_RIGHT)
	{
		if (!info->caminfo.curr_camnode->next)
			return (0);
		info->caminfo.curr_camnode = info->caminfo.curr_camnode->next;
	}
	else
		return (0);
	render_img(&info->setup.img_data, &info->setup.scr, info->caminfo.curr_camnode->cam);
			mlx_put_image_to_window(info->setup.mlx_vars.mlx, info->setup.mlx_vars.win, info->setup.img_data.img, 0, 0);
			mlx_loop(info->setup.mlx_vars.mlx);
	return (0);
}

int		mouse_check(int button, int x, int y)
{
	char *str;

	str = NULL;
	return (0);
}

void	render_img(const t_img_data *img, const t_screen *scr, const t_camera *cam) 
{
	t_vector	color;

	if (!img || !scr || !cam)
		return ;
	printf("render img start\n");
	for (int j = scr->height - 1; j >= 0; --j)
	{
		printf("left	%.1f%%\n", (100.0 * (double)j) / scr->height);
		for (int i = 0; i < scr->width; ++i)
		{
			ft_memset(&color, 0, sizeof(t_vector));
			//anti alias
			for (int s = 0; s < (int)SAMPLES_PER_PIXEL; ++s)
			{
				t_ray	ray;
				double u = ((double)i + ((double)s / SAMPLES_PER_PIXEL)) / (scr->width - 1);
				double v = ((double)j + ((double)s / SAMPLES_PER_PIXEL)) / (scr->height - 1);
				t_vector offset = add(multi(cam->horizontal, u), multi(cam->vertical, v));
				init_ray(&ray, cam->origin, minus(add(cam->lowerleft, offset), cam->origin));
				color = add(color, ray_color(&ray, 20));
			}
			color = divide(color, SAMPLES_PER_PIXEL);
	
			//no AA
//			t_ray	ray;
//			double u = (double)i / (scr->width - 1);
//			double v = (double)j / (scr->height - 1);
//			t_vector offset = add(multi(cam->horizontal, u), multi(cam->vertical, v));
//			init_ray(&ray, cam->origin, minus(add(cam->lowerleft, offset), cam->origin));
//			color = ray_color(&ray, 70);
			
			pixput(img, i, (int)scr->height - 1 - j, get_color(color, 2)); 
		}
	}
	printf("render image done\n");
}

void			pixput(const t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
