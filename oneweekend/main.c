
#include <stdio.h>
#include <mlx.h>
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

int		main(int argc, char *argv[])
{
	t_info		info;
	char	*s;
	int		rtfile;
	t_camlist	*camlist;

	//ft_memset(&info, 0, sizeof(t_info));
	s = NULL;

	t_vector	color;
 
	//	image
	info.setup.scr.ratio = 16.0/9.0;
	info.setup.scr.width = 100;
	info.setup.scr.height = info.setup.scr.width / info.setup.scr.ratio;

//	//camera
//	t_campos	campos;
//	t_camview	camview;
//	t_camera	cam;
//
//	init_campos(&campos, get_vector(0, 0, 0), get_vector(0, 0, -1), get_vector(0, 1, 0));
//	init_camview(&camview, M_PI / 2, info.setup.scr.ratio, 1.0);
////	init_camera(&cam, &campos, &camview);
//	make_camera(&info.camlist, &campos, &camview);
//
//	// make figures
//	t_material	mat_ground;
//	t_material	mat_center;
//	t_material	mat_left;
//	t_material	mat_right;
//
//	init_material(&mat_ground, get_vector(0.8, 0.8, 0), 0, lambertian);
//	init_material(&mat_center, get_vector(0.7, 0.3, 0.3), 0, lambertian);
//	init_material(&mat_left, get_vector(0.8, 0, 0), 0.8, lambertian);
//	init_material(&mat_right, get_vector(0, 0, 0.8), 0.3, lambertian);
//
//	make_sphere(get_vector(0, -100.5, -1), 100, &mat_ground);
//	//make_sphere(get_vector(0, 0, -1), 0.5, &mat_center);
//	make_sphere(get_vector(-1, 0, -1), 0.5, &mat_left);
//	make_sphere(get_vector(1, 0, -1), 0.5, &mat_right);
//
//
//	// make lights
////	make_light(get_vector(0,0.4,-0.3), get_vector(0.8,0.8,0.8),0.9);
//	make_light(get_vector(-2,3,-0.3), get_vector(1,1,1),0.6);
////	make_light(get_vector(2,0.4,-0.3), get_vector(0.9,0.5,0.3),0.6);

	if (argc >= 2)
	{int k = 0;
		rtfile = open_rtfile(argv[1]);
		if (rtfile == ERROR)
		{
			printf("Error\n");
			return (0);
		}
		while (get_next_line(rtfile, &s) > 0)
		{//	printf("%d\n", ++k);
			command(s, &info); }
		free(s);
	}

		//  make image with mlx
	info.setup.mlx_vars.mlx = mlx_init();
 	info.setup.mlx_vars.win = mlx_new_window(info.setup.mlx_vars.mlx, (int)info.setup.scr.width + 1, (int)info.setup.scr.height + 1, "miniRT");
 	info.setup.img_data.img = mlx_new_image(info.setup.mlx_vars.mlx, (int)info.setup.scr.width + 1, (int)info.setup.scr.height + 1);
 	info.setup.img_data.addr = mlx_get_data_addr(info.setup.img_data.img, &info.setup.img_data.bpp, &info.setup.img_data.linelen, &info.setup.img_data.endian);

	//hook
	mlx_hook(info.setup.mlx_vars.win, MLX_KEY_PRESS, 0, key_check, &info.setup.mlx_vars.win);
	mlx_hook(info.setup.mlx_vars.win, MLX_BUTTON_PRESS, 0, mouse_check, &info.setup.mlx_vars.win);
	mlx_hook(info.setup.mlx_vars.win, MLX_RED_CROSS, 0, (int (*)())exit, &info.setup.mlx_vars.win);// need to change exit to memory managed exit function

	printf("before render\n");
	render_img(&info.setup.img_data, &info.setup.scr, info.camlist->cam, 1);
	//delete, need to add camera and camlist free
	for (int i = 0; i < NUM_OF_FIGTYPES; ++i)
		ft_lstclear(&g_figures[i], free);
	if (g_light_data.light_arr)
		free(g_light_data.light_arr);
	mlx_put_image_to_window(info.setup.mlx_vars.mlx, info.setup.mlx_vars.win, info.setup.img_data.img, 0, 0);
	mlx_loop(info.setup.mlx_vars.mlx);
}
