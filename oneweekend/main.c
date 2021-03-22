
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include "miniRT.h"

int main()
{
	t_vars	ex;
	t_data	img;
 
	//  make image with mlx
	ex.mlx = mlx_init();
 	ex.win = mlx_new_window(ex.mlx, 1500, 1000, "ex");
 	img.img = mlx_new_image(ex.mlx, 1500, 1000);
 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);

	//	ch 4
	//	image
	const double scrratio = 16.0/9.0;
	t_plane	scr;
	scr.width = 1000;
	scr.height = scr.width / scrratio;

	//camera
	t_plane	view;
	view.height = 2.0;
	view.width = scrratio * view.height;
	double	focallen = 1.0;
	t_vector	color;

	t_vector origin, horizontal, vertical, lowerleft;
	init_vector(&origin, 0, 0, 0);
	init_vector(&horizontal, view.width, 0, 0);
	init_vector(&vertical, 0, view.height, 0);

	lowerleft = minus(origin, multi(add(horizontal, vertical), 0.5));
	lowerleft.z = origin.z - focallen;

	// make figures
	t_material	mat_ground;
	t_material	mat_center;
	t_material	mat_left;
	t_material	mat_right;

	init_material(&mat_ground, get_vector(0.8, 0.8, 0), 0, metal);
	init_material(&mat_center, get_vector(0.7, 0.3, 0.3), 0, lambertian);
	init_material(&mat_left, get_vector(0.8, 0.8, 0.8), 0.8, metal);
	init_material(&mat_right, get_vector(0.8, 0.6, 0.2), 0.3, metal);

	make_sphere(get_vector(0, -100.5, -1), 100, &mat_ground);
	make_sphere(get_vector(0, 0, -1), 0.5, &mat_center);
	make_sphere(get_vector(-1, 0, -1), 0.5, &mat_left);
	make_sphere(get_vector(1.0, 0, -1), 0.5, &mat_right);

	for (int j = scr.height - 1; j >= 0; --j)
	{
		for (int i = 0; i < scr.width; ++i)
		{
			ft_memset(&color, 0, sizeof(t_vector));
			for (int s = 0; s < (int)SAMPLES_PER_PIXEL; ++s)
			{
				t_ray	ray;
				double u = ((double)i + ((double)s / SAMPLES_PER_PIXEL)) / (scr.width - 1);
				double v = ((double)j + ((double)s / SAMPLES_PER_PIXEL)) / (scr.height - 1);
				t_vector castdir = add(multi(horizontal, u), multi(vertical, v));
				init_ray(&ray, origin, minus(add(lowerleft, castdir), origin));
				color = add(color, ray_color(&ray, 20));
			}
			color = divide(color, SAMPLES_PER_PIXEL);
			pixput(&img, i, (scr.height - 1) - j, get_color(color, 2));
		}
	}
	//delete
	for (int i = 0; i < NUM_OF_FIGTYPES; ++i)
		ft_lstclear(&g_figures[i], free);
	mlx_put_image_to_window(ex.mlx, ex.win, img.img, 0, 0);
	mlx_loop(ex.mlx);
}
