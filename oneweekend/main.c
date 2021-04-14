
#include "miniRT.h"

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
		return (ERROR);
}

int		save_bmp(t_img_data *img, const char *path)
{
	int		fd;

	fd = open(path, O_CREAT | O_TRUNC | O_WRONLY);
	

int		main(int argc, char *argv[])
{
	char		*line;
	int			rtfile;
	t_camlist	*camlist;
	t_vector	color;
	t_info		info;

	if (argc < 2)
		return (0);
	ft_memset(&info, 0, sizeof(t_info));
	rtfile = open_rtfile(argv[1]);
	if (rtfile == ERROR)
	{
		printf("Error\n");
		return (0);
	}
	line = NULL;
	while (get_next_line(rtfile, &line) > 0)
	{
		if (check_command(line, &info) == CMD_ERROR)
		;//free all malloc and return (0);
	}
	free(line);
	info.setup.mlx_vars.mlx = mlx_init();
 	info.setup.mlx_vars.win = mlx_new_window(info.setup.mlx_vars.mlx, (int)info.setup.scr.width + 1, (int)info.setup.scr.height + 1, "miniRT");
 	info.setup.img_data.img = mlx_new_image(info.setup.mlx_vars.mlx, (int)info.setup.scr.width + 1, (int)info.setup.scr.height + 1);
 	info.setup.img_data.addr = mlx_get_data_addr(info.setup.img_data.img, &info.setup.img_data.bpp, &info.setup.img_data.linelen, &info.setup.img_data.endian);

	//hook
	mlx_hook(info.setup.mlx_vars.win, MLX_KEY_PRESS, 0, key_check, &info);
	mlx_hook(info.setup.mlx_vars.win, MLX_BUTTON_PRESS, 0, mouse_check, &info.setup.mlx_vars.win);
	mlx_hook(info.setup.mlx_vars.win, MLX_RED_CROSS, 0, (int (*)())exit, &info.setup.mlx_vars.win);// need to change exit to memory managed exit function

	render_img(&info.setup.img_data, &info.setup.scr, info.camlist->cam);
	printf("print image done\n");

	//delete, need to add camera and camlist free
	for (int i = 0; i < NUM_OF_FIGTYPES; ++i)
		ft_lstclear(&g_figures[i], free);// need to change free to function which free material of figure also
	if (g_light_data.light_arr)
		free(g_light_data.light_arr);

	if (argc == 3)
		if (!ft_strcmp(argv[2], "--save"))
			save_bmp(img, "./scene/saved_scene");
	mlx_put_image_to_window(info.setup.mlx_vars.mlx, info.setup.mlx_vars.win, info.setup.img_data.img, 0, 0);
	mlx_loop(info.setup.mlx_vars.mlx);
}
