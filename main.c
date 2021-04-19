/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soekim <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:57:44 by soekim            #+#    #+#             */
/*   Updated: 2020/11/21 16:14:32 by soekim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	open_rtfile(char *name)
{
	char		*extension;
	int			fd;

	extension = name;
	while (*extension)
		++extension;
	extension -= 3;
	if (!ft_strcmp(extension, ".rt"))
	{
		fd = open(name, O_RDONLY);
		if (fd == ERROR)
			return (ERROR);
		else
			return (fd);
	}
	else
	{
		printf("Invalid file name\n");
		return (ERROR);
	}
}

static void	read_rtfile(char *path, t_info *info)
{
	int			rtfile;
	char		*line;

	rtfile = open_rtfile(path);
	if (rtfile == ERROR)
		info->err_exit = TRUE;
	else
	{
		line = NULL;
		while (get_next_line(rtfile, &line) > 0)
		{
			if (check_command(line, info) == CMD_ERROR)
			{
				info->err_exit = TRUE;
				free(line);
				exit_program(info);
			}
			free(line);
			line = NULL;
		}
		free(line);
	}
	return ;
}

static void	setup(char *path, t_info *info)
{
	t_mlx_vars	*mlx_vars;
	t_screen	*scr;
	t_img_data	*img_data;

	read_rtfile(path, info);
	scr = &info->setup.scr;
	mlx_vars = &info->setup.mlx_vars;
	mlx_vars->mlx = mlx_init();
	mlx_vars->win = \
	mlx_new_window(mlx_vars->mlx, \
					(int)scr->width, (int)scr->height, "miniRT");
	img_data = &info->setup.img_data;
	img_data->img = \
	mlx_new_image(mlx_vars->mlx, (int)scr->width, (int)scr->height);
	img_data->addr = \
	mlx_get_data_addr(img_data->img, &img_data->bpp, \
					&img_data->linelen, &img_data->endian);
	mlx_hook(mlx_vars->win, MLX_KEY_PRESS, 0, key_check, info);
	mlx_hook(mlx_vars->win, MLX_RED_CROSS, 0, \
			(int (*)())exit_program, &info);
	return ;
}

int			save_scene(char *path, t_info *info)
{
	t_bh	bh;

	set_bmpheader(&bh, &info->setup.scr);
	if (path)
		save_bmp(&info->setup.img_data, &info->setup.scr, bh, path);
	else
		save_bmp(&info->setup.img_data, &info->setup.scr, \
				bh, "./save/saved_scene.bmp");
	printf("scene saved\n");
	return (0);
}

int			main(int argc, char *argv[])
{
	t_info	info;

	ft_memset(&info, 0, sizeof(t_info));
	if (argc < 2 || argc > 4)
		return (0);
	setup(argv[1], &info);
	if (argc >= 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
			return (0);
	}
	render_img(&info.setup.img_data, &info.setup.scr, \
				info.caminfo.curr_camnode->cam);
	if (argc == 3)
		return (save_scene(NULL, &info));
	else if (argc == 4)
		return (save_scene(argv[3], &info));
	else
	{
		mlx_put_image_to_window(info.setup.mlx_vars.mlx, \
				info.setup.mlx_vars.win, info.setup.img_data.img, 0, 0);
		mlx_loop(info.setup.mlx_vars.mlx);
	}
	free_allocated(&info);
	return (0);
}
