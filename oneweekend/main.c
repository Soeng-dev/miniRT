
#include <stdio.h>
#include <mlx.h>
#include <stdio.h>
#include "miniRT.h"

int		open_rtfile(char *name)
{
	char	*extension;
	int		fd;

	extension = name;
	while (extension)
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
	int		rtfile;
	if (argc >= 2)
	{
		rtfile = open_rtfile(argv[1]);
		

	t_mlx_vars	minirt;
	t_mlx_data	img;
	t_vector	color;
 
	//	image
	t_screen	scr;
	scr.ratio = 16.0/9.0;
	scr.width = 1000;
	scr.height = scr.width / scr.ratio;

	//  make image with mlx
	minirt.mlx = mlx_init();
 	minirt.win = mlx_new_window(minirt.mlx, (int)scr.width + 1, (int)scr.height + 1, "miniRT");
 	img.img = mlx_new_image(minirt.mlx, (int)scr.width + 1, (int)scr.height + 1);
 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);

	//hook
	mlx_hook(minirt.win, MLX_KEY_PRESS, 0, key_check, &minirt);
	mlx_hook(minirt.win, MLX_BUTTON_PRESS, 0, mouse_check, &minirt);
	mlx_hook(minirt.win, MLX_RED_CROSS, 0, (int (*)())exit, &minirt);



	//camera
	t_campos	campos;
	t_camview	camview;
	t_camera	cam;

	init_campos(&campos, get_vector(0, 0, -0.7), get_vector(0, 0, -1), get_vector(0, 1, 0));
	init_camview(&camview, M_PI / 2, scr.ratio, 1.0);
	init_camera(&cam, &campos, &camview);

	// make figures
	t_material	mat_ground;
	t_material	mat_center;
	t_material	mat_left;
	t_material	mat_right;

	init_material(&mat_ground, get_vector(0.8, 0.8, 0), 0, lambertian);
	init_material(&mat_center, get_vector(0.7, 0.3, 0.3), 0, lambertian);
	init_material(&mat_left, get_vector(0.8, 0.8, 0.8), 0.8, lambertian);
	init_material(&mat_right, get_vector(0.8, 0.6, 0.2), 0.3, lambertian);

	make_sphere(get_vector(0, -100.5, -1), 100, &mat_ground);
	//make_sphere(get_vector(0, 0, -1), 0.5, &mat_center);
	make_sphere(get_vector(-1, 0, -1), 0.5, &mat_left);
	make_sphere(get_vector(1, 0, -1), 0.5, &mat_right);


	// make lights
//	make_light(get_vector(0,0.4,-0.3), get_vector(0.8,0.8,0.8),0.9);
	make_light(get_vector(-2,0.4,-0.3), get_vector(0.3,0.5,0.9),0.6);
//	make_light(get_vector(2,0.4,-0.3), get_vector(0.9,0.5,0.3),0.6);

	render_img(&img, &scr, &cam);
	//delete
	for (int i = 0; i < NUM_OF_FIGTYPES; ++i)
		ft_lstclear(&g_figures[i], free);
	free(g_light_data.light_arr);
	mlx_put_image_to_window(minirt.mlx, minirt.win, img.img, 0, 0);
	mlx_loop(minirt.mlx);
}
