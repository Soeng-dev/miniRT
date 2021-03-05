
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include "../includes/ray_tracing.h"

int main()
{
	t_vars	ex;
	t_data	img;
 
	//  make image with mlx
	ex.mlx = mlx_init();
 	ex.win = mlx_new_window(ex.mlx, 500, 500, "ex");
 	img.img = mlx_new_image(ex.mlx, 400, 225);
 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.linelen, &img.endian);

	//	ch 4
	//	image
	const double scrratio = 16.0/9.0;
	t_plane	scr;
	scr.width = 400;
	scr.height = scr.width / scrratio;

	//camera
	t_plane	view;
	view.height = 2.0;
	view.width = scrratio * view.height;
	double	focallen = 1.0;

	t_vec origin, horizontal, vertical, lowerleft;
	initvec(&origin, 0, 0, 0);
	initvec(&horizontal, view.width, 0, 0);
	initvec(&vertical, 0, view.height, 0);

	lowerleft = minus(origin, multi(add(horizontal, vertical), 0.5));
	lowerleft.z = origin.z - focallen;

	t_sp sp;
	initsp(&sp, getvec(0, 0, -1), 0.5);
	for (int j = scr.height - 1; j >= 0; --j)
	{
		for (int i = 0; i < scr.width; ++i)
		{
			t_ray ray;
			double u = (double)i / (scr.width - 1);
			double v = (double)j / (scr.height - 1);
			t_vec castdir = add(multi(horizontal, u), multi(vertical, v));
			initray(&ray, origin, minus(add(lowerleft, castdir), origin));
			int color = ray_color(&ray, &sp);
			pixput(&img, i, j, color);
		}
	}
	mlx_put_image_to_window(ex.mlx, ex.win, img.img, 0, 0);
	mlx_loop(ex.mlx);
}
