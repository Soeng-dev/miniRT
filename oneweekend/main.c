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

int		open_rtfile(char *name)
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

void	read_rtfile(char *path, t_info *info)
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
				info->err_exit = TRUE;
		}
		free(line);
	}
	return ;
}

int		main(int argc, char *argv[])
{
	t_info		info;

	if (argc < 2)
		return (0);
	ft_memset(&info, 0, sizeof(t_info));
	read_rtfile(argv[1], &info);
	if (info.err_exit)
		exit_program(&info);

	//init mlx_vars and img_data
	info.setup.mlx_vars.mlx = mlx_init();
 	info.setup.mlx_vars.win = mlx_new_window(info.setup.mlx_vars.mlx, (int)info.setup.scr.width, (int)info.setup.scr.height, "miniRT");
 	info.setup.img_data.img = mlx_new_image(info.setup.mlx_vars.mlx, (int)info.setup.scr.width, (int)info.setup.scr.height);
 	info.setup.img_data.addr = mlx_get_data_addr(info.setup.img_data.img, &info.setup.img_data.bpp, &info.setup.img_data.linelen, &info.setup.img_data.endian);

	//hook
	mlx_hook(info.setup.mlx_vars.win, MLX_KEY_PRESS, 0, key_check, &info);
	mlx_hook(info.setup.mlx_vars.win, MLX_RED_CROSS, 0, (int (*)())exit_program, &info);

	render_img(&info.setup.img_data, &info.setup.scr, info.caminfo.curr_camnode->cam);

	if (argc == 3)
	{
		if (!ft_strcmp(argv[2], "--save"))
		{
			t_bh	bh;

			set_bmpheader(&bh, &info.setup.scr);
			save_bmp(&info.setup.img_data, &info.setup.scr, bh, "./scenes/saved_scene.bmp");
			free_allocated(&info);
			return (0);
		}
	}
	mlx_put_image_to_window(info.setup.mlx_vars.mlx, info.setup.mlx_vars.win, info.setup.img_data.img, 0, 0);
	mlx_loop(info.setup.mlx_vars.mlx);
}
