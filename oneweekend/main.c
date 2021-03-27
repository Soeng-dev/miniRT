
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include "miniRT.h"

int main()
{
	t_vars		ex;
	t_data		img;
	t_vector	color;
 

	//  make image with mlx
	ex.mlx = mlx_init();
 	ex.win = mlx_new_window(ex.mlx, 1500, 1000, "ex");
 	img.img = mlx_new_image(ex.mlx, 1500, 1000);
 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);


	//	image
	t_screen	scr;
	scr.ratio = 16.0/9.0;
	scr.width = 1000;
	scr.height = scr.width / scr.ratio;


	//camera
	t_campos	campos;
	t_camview	camview;
	t_camera	cam;

	init_campos(&campos, get_vector(0, 0, 0), get_vector(0, 0, -1), get_vector(0, 1, 0));
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
	make_sphere(get_vector(-2, 0, -1), 0.5, &mat_left);
	make_sphere(get_vector(2, 0, -1), 0.5, &mat_right);


	// make lights
//	make_light(get_vector(0,0.4,-0.3), get_vector(0.8,0.8,0.8),1);
	make_light(get_vector(0,0.4,-0.3), get_vector(0.8,0.8,0.8),0.8);
//	make_light(get_vector(0,0.4,-0.3), get_vector(0.8,0.8,0.8),0.8);
	for(int i = 0 ; i < g_light_data.count; ++i)
		printf("%lf %lf %lf\n", g_light_data.light_arr[i].pos.x, g_light_data.light_arr[i].pos.y, g_light_data.light_arr[i].pos.z);

	//calculate and print image
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
				t_vector offset = add(multi(cam.horizontal, u), multi(cam.vertical, v));
				init_ray(&ray, cam.origin, minus(add(cam.lowerleft, offset), cam.origin));
				color = add(color, ray_color(&ray, 1.0, 20));
			}
			color = divide(color, SAMPLES_PER_PIXEL);
			pixput(&img, i, (scr.height - 1) - j, get_color(color, 2));
		}
	}
	printf("print image done\n");
	//delete
	for (int i = 0; i < NUM_OF_FIGTYPES; ++i)
		ft_lstclear(&g_figures[i], free);
	free(g_light_data.light_arr);
	mlx_put_image_to_window(ex.mlx, ex.win, img.img, 0, 0);
	mlx_loop(ex.mlx);
}
