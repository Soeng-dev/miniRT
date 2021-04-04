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

# include "../miniRT.h"

void			pixput(const t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->linelen + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		get_color(t_vector colorvec, double gamma)
{
	int		color;

	colorvec = power(colorvec, 1.0 / gamma);
	colorvec = multi(colorvec, 255);
	color = (((int)colorvec.x << 16) | ((int)colorvec.y << 8) | ((int)colorvec.z));
	return (color);
}

int		key_check(int key)
{
	char	*s;

	printf("%d\n", key);
	if (key == KEY_ESC)
		exit(0);
	if (key == KEY_TAB)
	{
		get_next_line(STDIN, &s);
		//command(s);
		free(s);
		s = NULL;
	}
	return (0);
}

int		mouse_check(int button, int x, int y)
{
	char *str;

	str = NULL;
	printf("%d	%d	%d\n", button, x,y);
	return (0);
}

void	render_img(const t_img_data *img, const t_screen *scr, const t_camera *cam, double ambient) 
{
	t_vector	color;

	if (!img || !scr || !cam)
		return ;
	for (int j = scr->height - 1; j >= 0; --j)
	{
		ft_putnbr_fd(j, 1);
		write(1, "\n", 1);
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
				color = add(color, ray_color(&ray, ambient, 20));
			}
			color = divide(color, SAMPLES_PER_PIXEL);

			//no AA
//			t_ray	ray;
//			double u = (double)i / (scr->width - 1);
//			double v = (double)j / (scr->height - 1);
//			t_vector offset = add(multi(cam->horizontal, u), multi(cam->vertical, v));
//			init_ray(&ray, cam->origin, minus(add(cam->lowerleft, offset), cam->origin));
//			color = ray_color(&ray, ambient, 20);
		

			pixput(img, i, (scr->height - 1) - j, get_color(color, 2));
		}
	}
	printf("print image done\n");
}
